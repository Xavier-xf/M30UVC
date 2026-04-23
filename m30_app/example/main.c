/*
 * main.c  -  M30 交互式测试程序
 *
 *   覆盖全部封装层 API，通过菜单驱动。
 *   设计为 ssh / 串口控制台环境，无需图形界面。
 */

#include "uvc_m30.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

static volatile sig_atomic_t g_quit = 0;
static volatile sig_atomic_t g_stop = 0;
static m30_ctx_t            *g_ctx  = NULL;

static void on_signal(int sig)
{
    (void)sig;
    g_quit = 1;
    g_stop = 1;
}

static int read_line(char *buf, size_t len)
{
    if (!fgets(buf, (int)len, stdin)) return -1;
    size_t n = strlen(buf);
    while (n > 0 && (buf[n - 1] == '\n' || buf[n - 1] == '\r')) buf[--n] = 0;
    return 0;
}

static long long now_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/* -------------------- 连续拉流 --------------------- */

static void stream_loop(m30_ctx_t *ctx)
{
    printf("streaming (BGRA), saving one BMP per second, Ctrl+C to stop...\n\n");

    g_stop = 0;
    m30_frame_t fr;
    int err;
    unsigned long frame_cnt = 0, total_frames = 0, err_cnt = 0;
    unsigned int  save_idx = 0;
    long long t_start = now_ms(), t_last = t_start, t_last_save = t_start;

    while (!g_stop) {
        err = m30_get_frame(ctx, &fr);
        if (err == M30_OK) {
            frame_cnt++;
            total_frames++;

            long long t_now = now_ms();
            if (t_now - t_last_save >= 1000) {
                char path[64];
                snprintf(path, sizeof(path), "./stream_%04u.bmp", save_idx++);
                if (m30_save_frame_bmp(ctx, path) == M30_OK)
                    printf("\n  [saved] %s (%dx%d)\n", path, fr.width, fr.height);
                t_last_save = t_now;
            }
        } else {
            err_cnt++;
            if (err_cnt <= 3)
                printf("  get frame failed: %s\n", m30_strerror(err));
        }

        long long t_now = now_ms();
        long long elapsed = t_now - t_last;
        if (elapsed >= 1000) {
            double fps = frame_cnt * 1000.0 / elapsed;
            double avg = total_frames * 1000.0 / (t_now - t_start);
            printf("\r  frames: %lu | %.1f fps | avg %.1f fps | saved %u | err: %lu    ",
                   total_frames, fps, avg, save_idx, err_cnt);
            fflush(stdout);
            frame_cnt = 0;
            t_last = t_now;
        }
    }

    long long t_total = now_ms() - t_start;
    printf("\n\nstream done: %lu frames, %.1f sec, avg %.1f fps, err %lu\n",
           total_frames, t_total / 1000.0,
           t_total > 0 ? total_frames * 1000.0 / t_total : 0.0, err_cnt);

    g_stop = 0;
    g_quit = 0;
}

/* -------------------- 无显示拉流基准 (老化脚本用) --------------------- */

static void stream_bench(m30_ctx_t *ctx)
{
    printf("headless stream benchmark (no display, no save), Ctrl+C to stop...\n\n");

    g_stop = 0;
    m30_frame_t fr;
    int err;
    unsigned long frame_cnt = 0, total_frames = 0, err_cnt = 0;
    double fps_min = 1e9, fps_max = 0.0;
    long long t_start = now_ms(), t_last = t_start;

    while (!g_stop) {
        err = m30_get_frame(ctx, &fr);
        if (err == M30_OK) {
            frame_cnt++;
            total_frames++;
        } else {
            err_cnt++;
            if (err_cnt <= 3)
                printf("  get frame failed: %s\n", m30_strerror(err));
        }

        long long t_now = now_ms();
        long long elapsed = t_now - t_last;
        if (elapsed >= 1000) {
            double fps = frame_cnt * 1000.0 / elapsed;
            if (fps < fps_min) fps_min = fps;
            if (fps > fps_max) fps_max = fps;
            double avg = total_frames * 1000.0 / (t_now - t_start);
            printf("\r  frames: %lu | %.1f fps | avg %.1f fps | err: %lu    ",
                   total_frames, fps, avg, err_cnt);
            fflush(stdout);
            frame_cnt = 0;
            t_last = t_now;
        }
    }

    long long t_total = now_ms() - t_start;
    double avg = t_total > 0 ? total_frames * 1000.0 / t_total : 0.0;
    /* 未采样到窗口时把 min 归零，避免输出 1e9 */
    if (fps_min > 1e8) fps_min = 0.0;
    printf("\n\nbench done: %lu frames, %.1f sec, avg %.1f fps, min %.1f, max %.1f, err %lu\n",
           total_frames, t_total / 1000.0, avg, fps_min, fps_max, err_cnt);

    g_stop = 0;
    g_quit = 0;
}

/* -------------------- 视频播放 (ffplay 窗口) --------------------- */

static void video_play(m30_ctx_t *ctx)
{
    int w = 0, h = 0;
    int err = m30_get_resolution(ctx, &w, &h);
    if (err != M30_OK || w <= 0 || h <= 0) {
        printf("get resolution failed: %s\n", m30_strerror(err));
        return;
    }

    char cmd[256];
    snprintf(cmd, sizeof(cmd),
             "ffplay -f rawvideo -pixel_format bgra -video_size %dx%d "
             "-framerate 25 -window_title \"M30 Live (%dx%d)\" -i pipe:0 "
             "-loglevel quiet 2>/dev/null",
             w, h, w, h);

    FILE *fp = popen(cmd, "w");
    if (!fp) {
        printf("failed to start ffplay, make sure ffmpeg is installed\n");
        return;
    }

    printf("video playing %dx%d, Ctrl+C to stop...\n", w, h);
    g_stop = 0;

    m30_frame_t fr;
    unsigned long total_frames = 0, err_cnt = 0;
    long long t_start = now_ms();

    while (!g_stop) {
        err = m30_get_frame(ctx, &fr);
        if (err == M30_OK) {
            if (fwrite(fr.data, fr.size, 1, fp) != 1) break;
            total_frames++;
        } else {
            err_cnt++;
            if (err_cnt <= 3)
                printf("  get frame failed: %s\n", m30_strerror(err));
        }
    }

    pclose(fp);

    long long t_total = now_ms() - t_start;
    printf("\nvideo done: %lu frames, %.1f sec, avg %.1f fps, err %lu\n",
           total_frames, t_total / 1000.0,
           t_total > 0 ? total_frames * 1000.0 / t_total : 0.0, err_cnt);

    g_stop = 0;
    g_quit = 0;
}

/* -------------------- 菜单 --------------------- */

static void show_menu(void)
{
    puts("");
    puts("==================== M30 Test Menu ====================");
    puts("--- Basic ---");
    puts("  0) Ping");
    puts("  1) Device info (version/SN/model/temp/sensor/HW ver)");
    puts("  2) Query resolution / framerate / light sensitivity");
    puts("  3) Save single frame BMP");
    puts("  4) Stream loop + save BMP (Ctrl+C to stop)");
    puts("  15) Video play - ffplay window (Ctrl+C to stop)");
    puts("  16) Stream benchmark - headless, no display/save (for aging test)");
    puts("--- Camera Control ---");
    puts("  5) UVC output switch (1=on 0=off)");
    puts("  6) Camera stream on/off (RGB/IR)");
    puts("  7) Query camera state");
    puts("  8) Switch camera (RGB/IR)");
    puts("  9) Mirror camera");
    puts("--- Video Settings ---");
    puts(" 10) Set resolution (0=720x1280 1=360x640 2=720x720 3=720x640)");
    puts(" 11) Set framerate (10~25)");
    puts(" 12) Get/Set anti-flicker");
    puts(" 13) Get/Set IR light");
    puts("--- AI Face DB ---");
    puts(" 20) Add face (capture)");
    puts(" 21) Delete face (all or by ID)");
    puts(" 22) Query face ID");
    puts(" 23) Get face count");
    puts(" 24) Get face ID list");
    puts("--- AI Recognition ---");
    puts(" 30) Start 1:N recognition");
    puts(" 31) Resume recognition");
    puts(" 32) Pause recognition");
    puts(" 33) Query recognition state");
    puts(" 34) Get single recognize result");
    puts(" 35) Get/Set recognize count");
    puts(" 36) Get/Set template update");
    puts(" 37) Get/Set rec config (json)");
    puts("--- AI Upload ---");
    puts(" 40) Open frame face info");
    puts(" 41) Close frame face info");
    puts(" 42) Open AI upload");
    puts(" 43) Close AI upload");
    puts("--- Device Name ---");
    puts(" 50) Get device name");
    puts(" 51) Set device name");
    puts("--- QR Code ---");
    puts(" 55) Set QR code switch");
    puts("--- System ---");
    puts(" 60) Recovery (factory reset)");
    puts(" 61) Reset (reboot)");
    puts(" 62) Get/Set SDK log config");
    puts(" 99) Exit");
    printf(" > ");
    fflush(stdout);
}

int main(void)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = on_signal;
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    m30_config_t cfg;
    m30_default_config(&cfg);
    cfg.log_level = 1;

    g_ctx = m30_create(&cfg);
    if (!g_ctx) { fprintf(stderr, "m30_create failed\n"); return 1; }

    int err = m30_open(g_ctx);
    if (err != M30_OK) {
        fprintf(stderr, "m30_open failed: %s (%d)\n", m30_strerror(err), err);
        m30_destroy(g_ctx);
        return 2;
    }
    printf("M30 connected.\n");

    char line[1024];
    while (!g_quit) {
        show_menu();
        if (read_line(line, sizeof(line)) != 0) break;
        int ch = atoi(line);

        switch (ch) {
        case 0:
            err = m30_ping(g_ctx);
            printf("[PING] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 1: {
            char ver[128] = {0}, sn_pcb[128] = {0}, sn_dev[128] = {0};
            char model[128] = {0}, hw_ver[128] = {0};
            unsigned int tc = 0, sensor = 0;
            (void)m30_get_version(g_ctx, ver, sizeof(ver));
            (void)m30_get_sn(g_ctx, 0, sn_pcb, sizeof(sn_pcb));
            (void)m30_get_sn(g_ctx, 1, sn_dev, sizeof(sn_dev));
            (void)m30_get_model(g_ctx, model, sizeof(model));
            (void)m30_get_cpu_temp(g_ctx, &tc);
            (void)m30_get_sensor_model(g_ctx, &sensor);
            (void)m30_get_hw_version(g_ctx, hw_ver, sizeof(hw_ver));
            printf("Version : %s\n", ver);
            printf("PCB SN  : %s\n", sn_pcb);
            printf("Dev SN  : %s\n", sn_dev);
            printf("Model   : %s\n", model);
            printf("CPU Temp: %u C\n", tc);
            printf("Sensor  : 0x%04X\n", sensor);
            printf("HW Ver  : %s\n", hw_ver);
            break;
        }

        case 2: {
            int w = 0, h = 0;
            unsigned int fps = 0, lux = 0;
            if (m30_get_resolution(g_ctx, &w, &h) == M30_OK)
                printf("Resolution: %dx%d\n", w, h);
            if (m30_get_framerate(g_ctx, &fps) == M30_OK)
                printf("Framerate : %u fps\n", fps);
            if (m30_get_light_sensitivity(g_ctx, &lux) == M30_OK)
                printf("Light Sens: %u\n", lux);
            break;
        }

        case 3:
            err = m30_save_frame_bmp(g_ctx, "./frame.bmp");
            printf("[BMP] %s\n",
                   err == M30_OK ? "saved frame.bmp" : m30_strerror(err));
            break;

        case 4:
            stream_loop(g_ctx);
            break;

        case 15:
            video_play(g_ctx);
            break;

        case 16:
            stream_bench(g_ctx);
            break;

        case 5:
            printf("UVC output (1=on 0=off): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_set_uvc_output(g_ctx, atoi(line));
            printf("[UVC] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 6: {
            printf("Camera (0=RGB 1=IR): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            int cam = atoi(line);
            printf("Action (1=open 0=close): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_set_camera_stream(g_ctx, (m30_cam_t)cam, atoi(line));
            printf("[CAM] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;
        }

        case 7: {
            int rgb = 0, ir = 0;
            int r1 = m30_get_camera_stream(g_ctx, M30_CAM_RGB, &rgb);
            int r2 = m30_get_camera_stream(g_ctx, M30_CAM_IR,  &ir);
            if (r1 == M30_OK && r2 == M30_OK)
                printf("RGB: %s | IR: %s\n",
                       rgb ? "on" : "off", ir ? "on" : "off");
            else
                printf("query failed\n");
            break;
        }

        case 8:
            printf("Switch to (0=RGB 1=IR): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_switch_cam(g_ctx, (m30_cam_t)atoi(line));
            printf("[SWITCH] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 9: {
            printf("Camera (0=RGB 1=IR): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            int cam = atoi(line);
            printf("Mirror (1=yes 0=no): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_mirror_cam(g_ctx, (m30_cam_t)cam, atoi(line));
            printf("[MIRROR] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;
        }

        case 10:
            printf("Resolution mode (0=720x1280 1=360x640 2=720x720 3=720x640): ");
            fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_set_resolution(g_ctx, (m30_resolution_t)atoi(line));
            printf("[RES] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 11:
            printf("Framerate (10~25): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_set_framerate(g_ctx, atoi(line));
            printf("[FPS] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 12: {
            unsigned char hz = 0, en = 0;
            printf("Camera ID (0/1): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            int cam_id = atoi(line);
            err = m30_get_no_flicker(g_ctx, cam_id, &hz, &en);
            if (err == M30_OK)
                printf("Anti-flicker: %s, %s\n",
                       hz ? "60Hz" : "50Hz", en ? "enabled" : "disabled");
            printf("Set? (y/n): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            if (line[0] == 'y' || line[0] == 'Y') {
                printf("Hz (0=50 1=60): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                int nhz = atoi(line);
                printf("Enable (0/1): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                err = m30_set_no_flicker(g_ctx, cam_id, nhz, atoi(line));
                printf("[FLICKER] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            }
            break;
        }

        case 13: {
            unsigned char lum = 0, ct = 0;
            err = m30_get_ir_light(g_ctx, &lum, &ct);
            if (err == M30_OK)
                printf("IR light: luminance=%u, close_time=%u sec\n", lum, ct);
            printf("Set? (y/n): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            if (line[0] == 'y' || line[0] == 'Y') {
                printf("Luminance (0~200): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                unsigned char nl = (unsigned char)atoi(line);
                printf("Close time (0~120 sec): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                err = m30_set_ir_light(g_ctx, nl, (unsigned char)atoi(line));
                printf("[IR] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            }
            break;
        }

        case 20:
            printf("Face ID: "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_face_add(g_ctx, line, (unsigned int)strlen(line));
            printf("[ADD FACE] rc=%d %s\n", err, m30_strerror(err));
            break;

        case 21: {
            printf("Mode (0=delete all, 1=by ID): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            int mode = atoi(line);
            char id[256] = {0};
            unsigned int id_len = 0;
            if (mode == 1) {
                printf("Face ID: "); fflush(stdout);
                if (read_line(id, sizeof(id))) break;
                id_len = (unsigned int)strlen(id);
            }
            err = m30_face_delete(g_ctx, (m30_del_mode_t)mode, id, id_len);
            printf("[DELETE] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;
        }

        case 22:
            printf("Face ID to query: "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_face_query(g_ctx, line, (unsigned int)strlen(line));
            printf("[QUERY] %s\n",
                   err == M30_OK ? "ID exists" : m30_strerror(err));
            break;

        case 23: {
            unsigned int count = 0;
            err = m30_face_get_count(g_ctx, &count);
            if (err == M30_OK)
                printf("Face count: %u\n", count);
            else
                printf("query failed: %s\n", m30_strerror(err));
            break;
        }

        case 24: {
            char id_buf[4096] = {0};
            err = m30_face_get_id_list(g_ctx, id_buf, sizeof(id_buf));
            if (err == M30_OK)
                printf("ID list:\n%s\n", id_buf);
            else
                printf("query failed: %s\n", m30_strerror(err));
            break;
        }

        case 30: {
            printf("Rec mode (0=recognition only, 1=liveness+recognition): ");
            fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            int rec = atoi(line);
            printf("Face mode (0=single, 1=multi): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_recognize_start_1n(g_ctx, (m30_rec_mode_t)rec,
                                         (m30_face_mode_t)atoi(line));
            printf("[1:N] %s\n", err == M30_OK ? "started" : m30_strerror(err));
            break;
        }

        case 31:
            err = m30_recognize_resume(g_ctx);
            printf("[RESUME] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 32:
            err = m30_recognize_pause(g_ctx);
            printf("[PAUSE] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 33: {
            int running = 0;
            err = m30_recognize_query(g_ctx, &running);
            if (err == M30_OK)
                printf("Recognition: %s\n", running ? "running" : "stopped");
            else
                printf("query failed: %s\n", m30_strerror(err));
            break;
        }

        case 34: {
            char result[1024] = {0};
            err = m30_get_single_recognize(g_ctx, result, sizeof(result));
            if (err == M30_OK)
                printf("Result: %s\n", result[0] ? result : "(empty)");
            else
                printf("failed: %s\n", m30_strerror(err));
            break;
        }

        case 35: {
            unsigned char rc_cnt = 0, lv_cnt = 0;
            err = m30_get_recognize_count(g_ctx, &rc_cnt, &lv_cnt);
            if (err == M30_OK)
                printf("Rec count: %u, Living count: %u\n", rc_cnt, lv_cnt);
            printf("Set? (y/n): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            if (line[0] == 'y' || line[0] == 'Y') {
                printf("Rec count (1~10): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                unsigned char nr = (unsigned char)atoi(line);
                printf("Living count (1~10): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                err = m30_set_recognize_count(g_ctx, nr,
                                              (unsigned char)atoi(line));
                printf("[SET] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            }
            break;
        }

        case 36: {
            int enabled = 0;
            err = m30_get_template_update(g_ctx, &enabled);
            if (err == M30_OK)
                printf("Template update: %s\n", enabled ? "on" : "off");
            printf("Set? (y/n): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            if (line[0] == 'y' || line[0] == 'Y') {
                printf("Enable (0/1): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                err = m30_set_template_update(g_ctx, atoi(line));
                printf("[SET] %s (reboot required)\n",
                       err == M30_OK ? "ok" : m30_strerror(err));
            }
            break;
        }

        case 37: {
            char config[4096] = {0};
            err = m30_get_rec_config(g_ctx, config, sizeof(config));
            if (err == M30_OK)
                printf("Config:\n%s\n", config);
            else
                printf("get failed: %s\n", m30_strerror(err));
            break;
        }

        case 40:
            err = m30_open_frame_face_info(g_ctx);
            printf("[FRAME INFO] %s\n", err == M30_OK ? "opened" : m30_strerror(err));
            break;

        case 41:
            err = m30_close_frame_face_info(g_ctx);
            printf("[FRAME INFO] %s\n", err == M30_OK ? "closed" : m30_strerror(err));
            break;

        case 42: {
            printf("Upload mode (0=all 2=img+reco 3=feat+reco 4=reco only): ");
            fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            int um = atoi(line);
            printf("Image mode (0~7): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_open_ai_upload(g_ctx, (m30_upload_mode_t)um,
                                     (m30_image_mode_t)atoi(line));
            printf("[AI UPLOAD] %s\n", err == M30_OK ? "opened" : m30_strerror(err));
            break;
        }

        case 43:
            err = m30_close_ai_upload(g_ctx);
            printf("[AI UPLOAD] %s\n", err == M30_OK ? "closed" : m30_strerror(err));
            break;

        case 50: {
            char name[256] = {0};
            err = m30_get_device_name(g_ctx, name, sizeof(name));
            if (err == M30_OK)
                printf("Device name: %s\n", name);
            else
                printf("failed: %s\n", m30_strerror(err));
            break;
        }

        case 51:
            printf("New name (<50 chars): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_set_device_name(g_ctx, line, strlen(line));
            printf("[NAME] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 55: {
            printf("QR code (1=on 0=off): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            int qr_on = atoi(line);
            printf("Report interval (sec, default 5): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_set_qrcode(g_ctx, qr_on, (unsigned char)atoi(line));
            printf("[QR] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;
        }

        case 60:
            printf("Keep user config? (1=yes 0=no): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            err = m30_recovery(g_ctx, atoi(line));
            printf("[RECOVERY] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 61:
            err = m30_reset(g_ctx);
            printf("[RESET] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            break;

        case 62: {
            int level = 0, target = 0;
            err = m30_get_log_config(g_ctx, &level, &target);
            if (err == M30_OK)
                printf("Log level=%d target=%d\n", level, target);
            printf("Set? (y/n): "); fflush(stdout);
            if (read_line(line, sizeof(line))) break;
            if (line[0] == 'y' || line[0] == 'Y') {
                printf("Level (0~6): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                int nl = atoi(line);
                printf("Target (0=console 1=file 2=both): "); fflush(stdout);
                if (read_line(line, sizeof(line))) break;
                err = m30_set_log_config(g_ctx, nl, atoi(line));
                printf("[LOG] %s\n", err == M30_OK ? "ok" : m30_strerror(err));
            }
            break;
        }

        case 99:
            g_quit = 1;
            break;

        default:
            puts("invalid option");
        }
    }

    printf("\nclosing connection...\n");
    m30_shutdown_hook(g_ctx);
    m30_destroy(g_ctx);
    return 0;
}
