# CLAUDE.md


具体的API查看SenseEngine AI柬얾친莉Win&Linux역랙쌈왯賈痰匡도.md文档，没有的应该就是没有，对应功能也要仔细看，现在是框架差不多，就按照现在的框架，但是相应的API的注释要有，可以简要，然后函数名可以用M30不然分不清是什么UVC，注释是中文，打印信息是英语，根据这些要求完善一下当前框架添加其他的api，最好是有一个在ubuntu下的老化测试脚本，要挂机进行老化测试。
要求1：添加一个按钮专门用于播放视频，原先的保存图片保留，测试脚本功能要更完善，
/*
 * uvc_m30.c  -  M30 UVC 封装层实现
 *
 *   覆盖 SDK 全部功能分区。线程安全：每上下文递归互斥锁。
 *   注释用中文，打印信息用英文。
 */

#include "uvc_m30.h"
#include "uvc_log.h"
#include "uvc_bmp.h"
#include "m30_sdk.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/* ------------------------------------------------------------------------ */
/*  可调参数                                                                 */
/* ------------------------------------------------------------------------ */
#define PING_PAYLOAD              "ping"
#define FRAME_WAIT_MS             20
#define FRAME_MAX_RETRIES         25
#define FRAME_VALID_RETRIES       30
#define FRAME_VALID_CHECK_ROWS    8
#define VIDEO_NODES_MAX           8

/* ------------------------------------------------------------------------ */
/*  上下文结构体                                                             */
/* ------------------------------------------------------------------------ */
struct m30_ctx {
    void            *sdk_dev;
    pthread_mutex_t  lock;
    m30_config_t     cfg;

    char             video_nodes[VIDEO_NODES_MAX][128];
    int              video_node_count;
    char             video_node[128];
    char             serial_node[128];

    int              sdk_inited;
    int              serial_up;
    int              camera_up;

    /* 内部帧缓冲区，随分辨率自动扩展 */
    unsigned char   *frame_buf;
    size_t           frame_buf_size;
};

/* ------------------------------------------------------------------------ */
/*  错误码映射                                                               */
/* ------------------------------------------------------------------------ */
static int map_sdk_err(int rc)
{
    if (rc == AC_ERR_SUCCESS) return M30_OK;
    switch (rc) {
    case AC_ERR_NOT_INIT:
    case AC_ERR_ALREADY_INIT:              return M30_ERR_STATE;
    case AC_ERR_INIT_FAIL:                 return M30_ERR_SDK_INIT;
    case AC_ERR_INPUT_ARG:
    case AC_ERR_OUTPUT_ARG:                return M30_ERR_INVAL;
    case AC_ERR_COM_TIMEOUT:               return M30_ERR_TIMEOUT;
    case AC_ERR_UVC_CONNECT:
    case AC_ERR_UVC_NEWFRAME_UNARRIVE:     return M30_ERR_CAMERA;
    case AC_ERR_SERIAL_CONNECT:            return M30_ERR_SERIAL;
    case AC_ERR_CALLBACK_REGISTERED:       return M30_ERR_BUSY;
    default:                               return M30_ERR_SDK_CALL;
    }
}

const char *m30_strerror(int err)
{
    switch (err) {
    case M30_OK:                 return "success";
    case M30_ERR_INVAL:          return "invalid argument";
    case M30_ERR_NOMEM:          return "out of memory";
    case M30_ERR_STATE:          return "invalid state";
    case M30_ERR_NO_DEVICE:      return "device not found";
    case M30_ERR_MULTI_DEVICE:   return "multiple devices detected";
    case M30_ERR_SDK_INIT:       return "SDK init failed";
    case M30_ERR_SDK_CALL:       return "SDK call failed";
    case M30_ERR_SERIAL:         return "serial link error";
    case M30_ERR_CAMERA:         return "UVC link error";
    case M30_ERR_TIMEOUT:        return "communication timeout";
    case M30_ERR_IO:             return "I/O error";
    case M30_ERR_BUSY:           return "resource busy";
    default:                     return "unknown error";
    }
}

/* ------------------------------------------------------------------------ */
/*  加锁辅助宏                                                               */
/* ------------------------------------------------------------------------ */
#define LOCK(c)    pthread_mutex_lock  (&(c)->lock)
#define UNLOCK(c)  pthread_mutex_unlock(&(c)->lock)

#define RETURN_UNLOCK(c, v) \
    do { int _r = (v); UNLOCK(c); return _r; } while (0)

#define REQUIRE_OPEN_UNLOCK(c) \
    do { if (!m30_is_open(c)) { UNLOCK(c); return M30_ERR_STATE; } } while (0)

/* SDK 简单调用宏：参数校验 + 加锁 + 调用 + 解锁返回 */
#define SDK_CALL(ctx, expr) \
    do { \
        if (!(ctx)) return M30_ERR_INVAL; \
        LOCK(ctx); \
        REQUIRE_OPEN_UNLOCK(ctx); \
        int _rc = (expr); \
        RETURN_UNLOCK(ctx, map_sdk_err(_rc)); \
    } while (0)

/* SDK 调用宏(仅需串口, 不需要 camera_up) */
#define SDK_CALL_SERIAL(ctx, expr) \
    do { \
        if (!(ctx)) return M30_ERR_INVAL; \
        LOCK(ctx); \
        if (!(ctx)->sdk_inited || !(ctx)->serial_up) { \
            UNLOCK(ctx); return M30_ERR_STATE; \
        } \
        int _rc = (expr); \
        RETURN_UNLOCK(ctx, map_sdk_err(_rc)); \
    } while (0)

/* ------------------------------------------------------------------------ */
/*  默认配置                                                                 */
/* ------------------------------------------------------------------------ */
void m30_default_config(m30_config_t *cfg)
{
    if (!cfg) return;
    cfg->log_level          = 2;
    cfg->log_target         = 2;
    cfg->connect_timeout_ms = 3000;
}

/* ------------------------------------------------------------------------ */
/*  生命周期                                                                 */
/* ------------------------------------------------------------------------ */

m30_ctx_t *m30_create(const m30_config_t *cfg)
{
    m30_ctx_t *c = (m30_ctx_t *)calloc(1, sizeof(*c));
    if (!c) return NULL;

    if (cfg) c->cfg = *cfg;
    else     m30_default_config(&c->cfg);

    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0) { free(c); return NULL; }
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    if (pthread_mutex_init(&c->lock, &attr) != 0) {
        pthread_mutexattr_destroy(&attr);
        free(c); return NULL;
    }
    pthread_mutexattr_destroy(&attr);

    int rc = SetLogConfig(c->cfg.log_level, c->cfg.log_target);
    if (rc != 0)
        UVC_LOGW("SetLogConfig(level=%d,target=%d) rc=%d",
                 c->cfg.log_level, c->cfg.log_target, rc);

    UVC_LOGI("M30 context created");
    return c;
}

void m30_destroy(m30_ctx_t *ctx)
{
    if (!ctx) return;
    (void)m30_close(ctx);
    pthread_mutex_destroy(&ctx->lock);
    free(ctx->frame_buf);
    free(ctx);
}

int m30_is_open(const m30_ctx_t *ctx)
{
    return ctx && ctx->sdk_inited && ctx->serial_up && ctx->camera_up;
}

static int split_nodes(const char *list, char out[][128], int max)
{
    int count = 0;
    const char *p = list;
    while (*p && count < max) {
        const char *sep = strchr(p, '|');
        size_t n = sep ? (size_t)(sep - p) : strlen(p);
        if (n > 0 && n < 128) {
            memcpy(out[count], p, n);
            out[count][n] = '\0';
            count++;
        }
        if (!sep) break;
        p = sep + 1;
    }
    return count;
}

static int enumerate_single(m30_ctx_t *ctx)
{
    char vid[1024], ser[1024];
    vid[0] = ser[0] = '\0';

    int rc = EnumDevice(vid, (int)sizeof(vid), ser, (int)sizeof(ser));
    if (rc != 0) {
        UVC_LOGE("EnumDevice failed rc=%d", rc);
        return M30_ERR_SDK_CALL;
    }
    if (vid[0] == '\0' || ser[0] == '\0') {
        UVC_LOGE("no M30 device found");
        return M30_ERR_NO_DEVICE;
    }
    if (strchr(ser, '|')) {
        UVC_LOGE("multiple M30 devices: serial=%s", ser);
        return M30_ERR_MULTI_DEVICE;
    }

    ctx->video_node_count = split_nodes(vid, ctx->video_nodes, VIDEO_NODES_MAX);
    if (ctx->video_node_count == 0) {
        UVC_LOGE("no valid video nodes parsed");
        return M30_ERR_NO_DEVICE;
    }
    snprintf(ctx->serial_node, sizeof(ctx->serial_node), "%s", ser);

    UVC_LOGI("M30 enumerated serial=%s video_candidates=%d: %s",
             ctx->serial_node, ctx->video_node_count, vid);
    return M30_OK;
}

int m30_open(m30_ctx_t *ctx)
{
    if (!ctx) return M30_ERR_INVAL;
    LOCK(ctx);
    if (m30_is_open(ctx)) RETURN_UNLOCK(ctx, M30_OK);

    int err = enumerate_single(ctx);
    if (err != M30_OK) RETURN_UNLOCK(ctx, err);

    /* 第1阶段：SDK 初始化 */
    ctx->sdk_dev = Init();
    if (!ctx->sdk_dev) {
        UVC_LOGE("SDK Init() returned NULL");
        RETURN_UNLOCK(ctx, M30_ERR_SDK_INIT);
    }
    ctx->sdk_inited = 1;

    /* 第2阶段：连接串口 */
    int rc = ConnectSerial(ctx->sdk_dev, ctx->serial_node);
    if (rc != 0) {
        UVC_LOGE("ConnectSerial(%s) failed rc=%d", ctx->serial_node, rc);
        err = map_sdk_err(rc);
        goto rollback_sdk;
    }
    ctx->serial_up = 1;

    /* 第3阶段：连接 UVC 摄像头（逐一尝试候选节点） */
    {
        int cam_ok = 0;
        for (int i = 0; i < ctx->video_node_count; ++i) {
            rc = ConnectCamera(ctx->sdk_dev, ctx->video_nodes[i]);
            if (rc == 0) {
                snprintf(ctx->video_node, sizeof(ctx->video_node),
                         "%s", ctx->video_nodes[i]);
                UVC_LOGI("ConnectCamera(%s) ok (%d/%d)",
                         ctx->video_node, i + 1, ctx->video_node_count);
                cam_ok = 1;
                break;
            }
            UVC_LOGW("ConnectCamera(%s) failed rc=%d, trying next",
                     ctx->video_nodes[i], rc);
        }
        if (!cam_ok) {
            UVC_LOGE("all video node candidates failed");
            err = M30_ERR_CAMERA;
            goto rollback_serial;
        }
    }
    ctx->camera_up = 1;

    /* 第4阶段：Ping 链路探活 */
    rc = Ping(ctx->sdk_dev, PING_PAYLOAD, (unsigned int)strlen(PING_PAYLOAD));
    if (rc != 0) {
        UVC_LOGE("Ping failed rc=%d", rc);
        err = M30_ERR_TIMEOUT;
        goto rollback_camera;
    }

    UVC_LOGI("m30_open succeeded");
    RETURN_UNLOCK(ctx, M30_OK);

rollback_camera:
    (void)DisconnectCamera(ctx->sdk_dev);
    ctx->camera_up = 0;
rollback_serial:
    (void)DisconnectSerial(ctx->sdk_dev);
    ctx->serial_up = 0;
rollback_sdk:
    (void)DeInit(ctx->sdk_dev);
    ctx->sdk_dev    = NULL;
    ctx->sdk_inited = 0;
    RETURN_UNLOCK(ctx, err);
}

int m30_close(m30_ctx_t *ctx)
{
    if (!ctx) return M30_ERR_INVAL;
    LOCK(ctx);

    int first_err = M30_OK;

    if (ctx->camera_up) {
        int rc = DisconnectCamera(ctx->sdk_dev);
        if (rc != 0 && first_err == M30_OK) first_err = map_sdk_err(rc);
        ctx->camera_up = 0;
    }
    if (ctx->serial_up) {
        int rc = DisconnectSerial(ctx->sdk_dev);
        if (rc != 0 && first_err == M30_OK) first_err = map_sdk_err(rc);
        ctx->serial_up = 0;
    }
    if (ctx->sdk_inited) {
        int rc = DeInit(ctx->sdk_dev);
        if (rc != 0 && first_err == M30_OK) first_err = map_sdk_err(rc);
        ctx->sdk_dev    = NULL;
        ctx->sdk_inited = 0;
    }

    if (first_err == M30_OK) UVC_LOGI("m30_close done");
    else                     UVC_LOGW("m30_close with error rc=%d (%s)",
                                      first_err, m30_strerror(first_err));
    RETURN_UNLOCK(ctx, first_err);
}

void m30_shutdown_hook(m30_ctx_t *ctx)
{
    if (!ctx) return;
    (void)m30_close(ctx);
}

/* ======================================================================== */
/*  设备信息查询                                                             */
/* ======================================================================== */

int m30_ping(m30_ctx_t *ctx)
{
    SDK_CALL(ctx, Ping(ctx->sdk_dev,
                       PING_PAYLOAD, (unsigned int)strlen(PING_PAYLOAD)));
}

int m30_get_version(m30_ctx_t *ctx, char *buf, size_t len)
{
    if (!ctx || !buf || !len) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    memset(buf, 0, len);
    int rc = GetDeviceVersion(ctx->sdk_dev, buf, (unsigned int)len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_get_sn(m30_ctx_t *ctx, int mode, char *buf, size_t len)
{
    if (!ctx || !buf || !len) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    memset(buf, 0, len);
    int rc = GetDevSn(ctx->sdk_dev, (char)mode, buf, (unsigned int)len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_get_model(m30_ctx_t *ctx, char *buf, size_t len)
{
    if (!ctx || !buf || !len) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    memset(buf, 0, len);
    int rc = GetDevModel(ctx->sdk_dev, buf, (unsigned int)len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_get_cpu_temp(m30_ctx_t *ctx, unsigned int *temp_c)
{
    if (!ctx || !temp_c) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    int rc = GetCpuTemperature(ctx->sdk_dev, temp_c);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_get_sensor_model(m30_ctx_t *ctx, unsigned int *sensor)
{
    if (!ctx || !sensor) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    int rc = GetAESensorModel(ctx->sdk_dev, sensor);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_get_hw_version(m30_ctx_t *ctx, char *buf, size_t len)
{
    if (!ctx || !buf || !len) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    memset(buf, 0, len);
    int rc = GetDevModelAppVer(ctx->sdk_dev, buf, (unsigned int)len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_get_device_name(m30_ctx_t *ctx, char *buf, size_t len)
{
    if (!ctx || !buf || !len) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    memset(buf, 0, len);
    int rc = GetDeviceName(ctx->sdk_dev, buf, (unsigned int)len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_device_name(m30_ctx_t *ctx, const char *name, size_t len)
{
    if (!ctx || !name || !len) return M30_ERR_INVAL;
    SDK_CALL(ctx, SetDeviceName(ctx->sdk_dev, name, (unsigned int)len));
}

int m30_get_log_config(m30_ctx_t *ctx, int *level, int *target)
{
    if (!ctx || !level || !target) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited) { UNLOCK(ctx); return M30_ERR_STATE; }
    int rc = GetLogConfig(level, target);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_log_config(m30_ctx_t *ctx, int level, int target)
{
    if (!ctx) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited) { UNLOCK(ctx); return M30_ERR_STATE; }
    int rc = SetLogConfig(level, target);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

/* ======================================================================== */
/*  视频流配置                                                               */
/* ======================================================================== */

int m30_get_resolution(m30_ctx_t *ctx, int *w, int *h)
{
    if (!ctx || !w || !h) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    *w = *h = 0;
    int rc = GetResolution(ctx->sdk_dev, w, h);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_resolution(m30_ctx_t *ctx, m30_resolution_t mode)
{
    SDK_CALL(ctx, SetResolution(ctx->sdk_dev, (char)mode));
}

int m30_get_framerate(m30_ctx_t *ctx, unsigned int *fps)
{
    if (!ctx || !fps) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    int rc = GetFrameRate(ctx->sdk_dev, fps);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_framerate(m30_ctx_t *ctx, int fps)
{
    SDK_CALL(ctx, SetFrameRate(ctx->sdk_dev, fps));
}

int m30_get_light_sensitivity(m30_ctx_t *ctx, unsigned int *threshold)
{
    if (!ctx || !threshold) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    int rc = GetLuminousSensitivityThreshold(ctx->sdk_dev, threshold);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

/* ======================================================================== */
/*  摄像头开关控制                                                           */
/* ======================================================================== */

/* SDK 语义反转：nMode=0 开启, nMode=1 关闭 */
int m30_set_uvc_output(m30_ctx_t *ctx, int on)
{
    SDK_CALL(ctx, SetUvcSwitch(ctx->sdk_dev, on ? 0 : 1));
}

int m30_set_camera_stream(m30_ctx_t *ctx, m30_cam_t cam, int on)
{
    SDK_CALL(ctx, SetCameraStream(ctx->sdk_dev, on ? 0 : 1, (char)cam));
}

int m30_get_camera_stream(m30_ctx_t *ctx, m30_cam_t cam, int *is_open)
{
    if (!ctx || !is_open) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    unsigned char state = 0;
    int rc = GetCameraStream(ctx->sdk_dev, (char)cam, &state);
    *is_open = state ? 1 : 0;
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_switch_cam(m30_ctx_t *ctx, m30_cam_t cam)
{
    SDK_CALL(ctx, SwitchCamRgbIr(ctx->sdk_dev, (char)cam));
}

int m30_mirror_cam(m30_ctx_t *ctx, m30_cam_t cam, int mirror)
{
    /* SDK: nMirror 0=镜像, 1=不镜像 */
    SDK_CALL(ctx, MirrorCamRgbIr(ctx->sdk_dev, (char)cam,
                                 mirror ? 0 : 1));
}

/* ======================================================================== */
/*  抗闪烁 / IR 灯                                                          */
/* ======================================================================== */

int m30_get_no_flicker(m30_ctx_t *ctx, int cam_id,
                       unsigned char *hz, unsigned char *enable)
{
    if (!ctx || !hz || !enable) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    int rc = GetDeviceNoFlickerHz(ctx->sdk_dev, (char)cam_id, hz, enable);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_no_flicker(m30_ctx_t *ctx, int cam_id, int hz, int enable)
{
    SDK_CALL(ctx, SetDeviceNoFlickerHz(ctx->sdk_dev,
                                       (char)cam_id, (char)hz, (char)enable));
}

int m30_get_ir_light(m30_ctx_t *ctx, unsigned char *luminance,
                     unsigned char *close_time)
{
    if (!ctx || !luminance || !close_time) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);
    int rc = GetIRlight(ctx->sdk_dev, luminance, close_time);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_ir_light(m30_ctx_t *ctx, unsigned char luminance,
                     unsigned char close_time)
{
    SDK_CALL(ctx, SetIRlight(ctx->sdk_dev, luminance, close_time));
}

/* ======================================================================== */
/*  视频帧捕获                                                               */
/* ======================================================================== */

/* 确保内部帧缓冲区足够大，需在持锁状态调用 */
static int ensure_frame_buf(m30_ctx_t *ctx, size_t need)
{
    if (ctx->frame_buf && ctx->frame_buf_size >= need) return 0;
    unsigned char *p = (unsigned char *)realloc(ctx->frame_buf, need);
    if (!p) return -1;
    ctx->frame_buf = p;
    ctx->frame_buf_size = need;
    return 0;
}

int m30_get_frame(m30_ctx_t *ctx, m30_frame_t *out)
{
    if (!ctx || !out) return M30_ERR_INVAL;
    LOCK(ctx); REQUIRE_OPEN_UNLOCK(ctx);

    int w = 0, h = 0;
    int rc = GetResolution(ctx->sdk_dev, &w, &h);
    if (rc != 0 || w <= 0 || h <= 0) {
        UVC_LOGE("GetResolution failed rc=%d w=%d h=%d", rc, w, h);
        RETURN_UNLOCK(ctx, map_sdk_err(rc ? rc : AC_ERR_OUTPUT_ARG));
    }

    const size_t need = (size_t)w * (size_t)h * 4u;
    if (ensure_frame_buf(ctx, need) != 0) {
        UVC_LOGE("frame buffer alloc failed: %zu bytes", need);
        RETURN_UNLOCK(ctx, M30_ERR_NOMEM);
    }

    memset(ctx->frame_buf, 0, need);
    memset(out->verify, 0, sizeof(out->verify));

    int attempts = 0;
    while (attempts++ < FRAME_MAX_RETRIES) {
        rc = GetFrame(ctx->sdk_dev, (char *)ctx->frame_buf, (int)need,
                      out->verify, (int)sizeof(out->verify));
        if (rc == AC_ERR_SUCCESS) break;
        if (rc != AC_ERR_UVC_NEWFRAME_UNARRIVE) {
            UVC_LOGE("GetFrame failed rc=%d", rc);
            RETURN_UNLOCK(ctx, map_sdk_err(rc));
        }
        usleep(FRAME_WAIT_MS * 1000);
    }
    if (rc != AC_ERR_SUCCESS) {
        UVC_LOGE("GetFrame timeout after %d retries", attempts);
        RETURN_UNLOCK(ctx, M30_ERR_TIMEOUT);
    }

    out->data   = ctx->frame_buf;
    out->size   = need;
    out->width  = w;
    out->height = h;
    RETURN_UNLOCK(ctx, M30_OK);
}

/* 检查帧底部是否为有效像素（非全零/非单色填充） */
static int frame_bottom_valid(const unsigned char *bgra, int w, int h)
{
    int check = FRAME_VALID_CHECK_ROWS;
    if (check > h / 2) check = h / 2;

    const size_t row_bytes = (size_t)w * 4u;
    for (int r = h - check; r < h; r++) {
        const unsigned char *row = bgra + (size_t)r * row_bytes;
        /* 取首像素值，看整行是否全部相同 */
        unsigned char b0 = row[0], g0 = row[1], r0 = row[2], a0 = row[3];
        int all_same = 1;
        for (int c = 1; c < w; c++) {
            const unsigned char *px = row + (size_t)c * 4u;
            if (px[0] != b0 || px[1] != g0 || px[2] != r0 || px[3] != a0) {
                all_same = 0;
                break;
            }
        }
        if (all_same) return 0;
    }
    return 1;
}

int m30_save_frame_bmp(m30_ctx_t *ctx, const char *path)
{
    if (!ctx || !path || !*path) return M30_ERR_INVAL;

    /* 反复取帧直到底部像素有效，避免保存解码不完整的画面 */
    m30_frame_t fr;
    int err, valid = 0;
    for (int try = 0; try < FRAME_VALID_RETRIES; try++) {
        err = m30_get_frame(ctx, &fr);
        if (err != M30_OK) return err;
        if (frame_bottom_valid(fr.data, fr.width, fr.height)) {
            valid = 1;
            break;
        }
        UVC_LOGD("frame %d/%d bottom invalid, retry", try + 1, FRAME_VALID_RETRIES);
        usleep(100 * 1000);
    }

    if (!valid)
        UVC_LOGW("frame bottom still invalid after %d retries, saving anyway",
                 FRAME_VALID_RETRIES);

    int rc = uvc_bmp_write(path, fr.data, fr.width, fr.height);
    if (rc != 0) {
        UVC_LOGE("BMP write failed rc=%d", rc);
        return M30_ERR_IO;
    }
    UVC_LOGI("frame saved: %s (%dx%d)%s", path, fr.width, fr.height,
             valid ? "" : " (possibly incomplete)");
    return M30_OK;
}

/* ======================================================================== */
/*  AI 人脸底库管理                                                          */
/* ======================================================================== */

int m30_face_add(m30_ctx_t *ctx, const char *id, unsigned int id_len)
{
    if (!ctx || !id || !id_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx, AddFace(ctx->sdk_dev, id, id_len));
}

int m30_face_add_by_image(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                          const void *img, unsigned int img_len)
{
    if (!ctx || !id || !id_len || !img || !img_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx, AddFaceByImage(ctx->sdk_dev, id, id_len, img, img_len));
}

int m30_face_add_return_image(m30_ctx_t *ctx, const char *id,
                              unsigned int id_len,
                              void **out_img, unsigned int *out_len)
{
    if (!ctx || !id || !id_len || !out_img || !out_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx,
        AddFaceReturnImage(ctx->sdk_dev, id, id_len, out_img, out_len));
}

int m30_face_add_slice(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                       unsigned int total_len, unsigned int pos,
                       int is_last, const void *slice, unsigned int slice_len)
{
    if (!ctx || !id || !id_len || !slice || !slice_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx,
        AddFaceSlice(ctx->sdk_dev, id, id_len,
                     total_len, pos, is_last, slice, slice_len));
}

int m30_face_delete(m30_ctx_t *ctx, m30_del_mode_t mode,
                    const char *id, unsigned int id_len)
{
    if (!ctx) return M30_ERR_INVAL;
    if (mode == M30_DEL_BY_ID && (!id || !id_len)) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx,
        DeleteFace(ctx->sdk_dev, (int)mode,
                   mode == M30_DEL_BY_ID ? id : NULL,
                   mode == M30_DEL_BY_ID ? id_len : 0));
}

int m30_face_query(m30_ctx_t *ctx, const char *id, unsigned int id_len)
{
    if (!ctx || !id || !id_len) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    int rc = QueryFace(ctx->sdk_dev, id, id_len, 0);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_face_get_id_list(m30_ctx_t *ctx, char *buf, unsigned int buf_len)
{
    if (!ctx || !buf || !buf_len) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    memset(buf, 0, buf_len);
    int rc = GetDeviceFaceID(ctx->sdk_dev, buf, buf_len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_face_get_count(m30_ctx_t *ctx, unsigned int *count)
{
    if (!ctx || !count) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    int rc = GetDeviceFaceLibraryNum(ctx->sdk_dev, count);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_feature_add(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                    const void *feat, unsigned int feat_len)
{
    if (!ctx || !id || !id_len || !feat || !feat_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx,
        AddFeature(ctx->sdk_dev, id, id_len, feat, feat_len));
}

int m30_feature_update(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                       const void *feat, unsigned int feat_len)
{
    if (!ctx || !id || !id_len || !feat || !feat_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx,
        UpdateFeature(ctx->sdk_dev, id, id_len, feat, feat_len));
}

int m30_feature_query(m30_ctx_t *ctx, const char *id, unsigned int id_len,
                      void *feat, unsigned int feat_len)
{
    if (!ctx || !id || !id_len || !feat || !feat_len) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    int rc = QueryFeature(ctx->sdk_dev, id, id_len, feat, feat_len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

/* ======================================================================== */
/*  AI 人脸识别控制                                                          */
/* ======================================================================== */

int m30_recognize_start_1n(m30_ctx_t *ctx, m30_rec_mode_t rec,
                           m30_face_mode_t face)
{
    SDK_CALL_SERIAL(ctx,
        StartOnetoNumRecognize(ctx->sdk_dev, (int)rec, (int)face));
}

int m30_recognize_start_11(m30_ctx_t *ctx, m30_rec_mode_t rec,
                           m30_face_mode_t face,
                           const void *img, unsigned int img_len)
{
    if (!ctx || !img || !img_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx,
        StartOnetoOneRecognize(ctx->sdk_dev, (int)rec, (int)face,
                               img, img_len));
}

int m30_recognize_start_11_feature(m30_ctx_t *ctx, m30_rec_mode_t rec,
                                   m30_face_mode_t face,
                                   const void *feat, unsigned int feat_len)
{
    if (!ctx || !feat || !feat_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx,
        StartOnetoOneRecognizeFeature(ctx->sdk_dev, (int)rec, (int)face,
                                      feat, feat_len));
}

int m30_recognize_resume(m30_ctx_t *ctx)
{
    SDK_CALL_SERIAL(ctx, ResumeRecognize(ctx->sdk_dev));
}

int m30_recognize_pause(m30_ctx_t *ctx)
{
    SDK_CALL_SERIAL(ctx, PauseRecognize(ctx->sdk_dev));
}

int m30_recognize_query(m30_ctx_t *ctx, int *running)
{
    if (!ctx || !running) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    int rc = QueryRecognize(ctx->sdk_dev);
    if (rc < 0) RETURN_UNLOCK(ctx, map_sdk_err(rc));
    /* SDK: 0=已开启 1=已关闭 */
    *running = (rc == 0) ? 1 : 0;
    RETURN_UNLOCK(ctx, M30_OK);
}

int m30_set_rec_config(m30_ctx_t *ctx, const char *json, unsigned int len)
{
    if (!ctx || !json || !len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx, SetRecConfig(ctx->sdk_dev, json, len, 0));
}

int m30_get_rec_config(m30_ctx_t *ctx, char *buf, unsigned int len)
{
    if (!ctx || !buf || !len) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    memset(buf, 0, len);
    int rc = GetRecConfig(ctx->sdk_dev, buf, len, 0);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_get_single_recognize(m30_ctx_t *ctx, char *buf, unsigned int len)
{
    if (!ctx || !buf || !len) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    memset(buf, 0, len);
    int rc = GetSingleRecognize(ctx->sdk_dev, buf, len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_recognize_count(m30_ctx_t *ctx, unsigned char rec_count,
                            unsigned char living_count)
{
    SDK_CALL_SERIAL(ctx,
        SetRecognizeCount(ctx->sdk_dev, rec_count, living_count));
}

int m30_get_recognize_count(m30_ctx_t *ctx, unsigned char *rec_count,
                            unsigned char *living_count)
{
    if (!ctx || !rec_count || !living_count) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    int rc = GetRecognizeCount(ctx->sdk_dev, rec_count, living_count);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_template_update(m30_ctx_t *ctx, int enable)
{
    SDK_CALL_SERIAL(ctx,
        SetTemplateUpdate(ctx->sdk_dev, enable ? 1 : 0));
}

int m30_get_template_update(m30_ctx_t *ctx, int *enabled)
{
    if (!ctx || !enabled) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    unsigned char val = 0;
    int rc = GetTemplateUpdate(ctx->sdk_dev, &val);
    *enabled = val ? 1 : 0;
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_set_qrcode(m30_ctx_t *ctx, int enable, unsigned char interval)
{
    SDK_CALL_SERIAL(ctx,
        SetQRCodeSwitch(ctx->sdk_dev, enable ? 1 : 0, interval));
}

int m30_static_compare(m30_ctx_t *ctx, void **result, unsigned int *result_len)
{
    if (!ctx || !result || !result_len) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    int rc = StaticFaceCompare(ctx->sdk_dev, result, result_len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

int m30_static_compare_image(m30_ctx_t *ctx, const void *img,
                             unsigned int img_len,
                             void **result, unsigned int *result_len)
{
    if (!ctx || !img || !img_len || !result || !result_len)
        return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    int rc = StaticFaceCompareReturnImage(ctx->sdk_dev, img, img_len,
                                          result, result_len);
    RETURN_UNLOCK(ctx, map_sdk_err(rc));
}

/* ======================================================================== */
/*  AI 数据上报                                                              */
/* ======================================================================== */

int m30_open_frame_face_info(m30_ctx_t *ctx)
{
    SDK_CALL_SERIAL(ctx, OpenAutoUploadFaceInfoInFrame(ctx->sdk_dev));
}

int m30_close_frame_face_info(m30_ctx_t *ctx)
{
    SDK_CALL_SERIAL(ctx, CloseAutoUploadFaceInfoInFrame(ctx->sdk_dev));
}

int m30_open_ai_upload(m30_ctx_t *ctx, m30_upload_mode_t upload,
                       m30_image_mode_t image)
{
    SDK_CALL_SERIAL(ctx,
        OpenAutoUploadAiInfo(ctx->sdk_dev, (char)upload, (char)image));
}

int m30_close_ai_upload(m30_ctx_t *ctx)
{
    SDK_CALL_SERIAL(ctx, CloseAutoUploadAiInfo(ctx->sdk_dev));
}

int m30_register_reco_cb(m30_ctx_t *ctx, m30_report_cb cb)
{
    if (!ctx || !cb) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    RegisterRecoReportCb(ctx->sdk_dev, cb);
    RETURN_UNLOCK(ctx, M30_OK);
}

int m30_register_track_cb(m30_ctx_t *ctx, m30_report_cb cb)
{
    if (!ctx || !cb) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    RegisterTrackReportCb(ctx->sdk_dev, cb);
    RETURN_UNLOCK(ctx, M30_OK);
}

int m30_register_image_cb(m30_ctx_t *ctx, m30_report_cb cb)
{
    if (!ctx || !cb) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    RegisterImageReportCb(ctx->sdk_dev, cb);
    RETURN_UNLOCK(ctx, M30_OK);
}

int m30_register_feature_cb(m30_ctx_t *ctx, m30_report_cb cb)
{
    if (!ctx || !cb) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    RegisterFeatureReportCb(ctx->sdk_dev, cb);
    RETURN_UNLOCK(ctx, M30_OK);
}

int m30_register_qrcode_cb(m30_ctx_t *ctx, m30_report_cb cb)
{
    if (!ctx || !cb) return M30_ERR_INVAL;
    LOCK(ctx);
    if (!ctx->sdk_inited || !ctx->serial_up) {
        UNLOCK(ctx); return M30_ERR_STATE;
    }
    RegisterQRCodeReportCb(ctx->sdk_dev, cb);
    RETURN_UNLOCK(ctx, M30_OK);
}

/* ======================================================================== */
/*  系统维护                                                                 */
/* ======================================================================== */

int m30_recovery(m30_ctx_t *ctx, int keep_user_config)
{
    SDK_CALL_SERIAL(ctx, Recovery(ctx->sdk_dev, keep_user_config ? 1 : 0));
}

int m30_reset(m30_ctx_t *ctx)
{
    SDK_CALL_SERIAL(ctx, Reset(ctx->sdk_dev));
}

int m30_upload_firmware_slice(m30_ctx_t *ctx, unsigned int pos,
                              const void *data, unsigned int len)
{
    if (!ctx || !data || !len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx, UploadPackageSlice(ctx->sdk_dev, pos, data, len));
}

int m30_apply_upgrade(m30_ctx_t *ctx, const char *md5, unsigned int md5_len)
{
    if (!ctx || !md5 || !md5_len) return M30_ERR_INVAL;
    SDK_CALL_SERIAL(ctx, ApplyUpgrade(ctx->sdk_dev, md5, md5_len));
}
