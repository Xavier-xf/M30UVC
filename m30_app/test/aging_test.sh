#!/bin/bash
#
# aging_test.sh  -  M30 老化测试脚本
#
# 在 Ubuntu 下挂机运行，循环执行以下测试项：
#   1. 设备连接 / Ping / 断开重连
#   2. 读取设备信息 (版本/SN/型号/温度/sensor)
#   3. 保存 BMP 截图
#   4. 视频流拉帧 + 帧率/错误统计
#   5. 摄像头 RGB/IR 开关切换
#   6. 查询识别配置 / 底库数量
#   7. 断线重连测试
#
# 用法:
#   cd m30_app   (必须在 m30_app 目录下运行)
#   sudo ./test/aging_test.sh [循环次数] [每轮拉流秒数] [最低帧率]
#   默认: 无限循环, 每轮拉流 30 秒, 最低帧率 10fps
#
# 也可以通过 make aging 运行

# ---- 自动定位项目根目录(m30_app/) ----------------------------------------
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_DIR"

LOOPS=${1:-0}           # 0 = 无限循环
STREAM_SEC=${2:-30}     # 每轮拉流秒数
MIN_FPS=${3:-10}        # 最低可接受帧率
BIN="$PROJECT_DIR/build/m30_demo"
LOG_DIR="$PROJECT_DIR/test/aging_logs"
FRAME_DIR="$PROJECT_DIR/test/aging_frames"

# ---- 自动探测 SDK 库路径并设置 LD_LIBRARY_PATH ----------------------------
SDK_ROOT="$PROJECT_DIR/../Windows_Linux_armlinux_SDK_demo_v4.5.5"

find_sdk_lib_dir() {
    local base="$1"
    for arch in linux64_14 arm32_allwinner aarch64_allwinner arm32_pi4; do
        local arch_dir="$base/lib/$arch"
        for sub in libDebug release libRelease; do
            if [ -d "$arch_dir/$sub" ] && ls "$arch_dir/$sub"/libAICameraModule.so* >/dev/null 2>&1; then
                echo "$arch_dir/$sub"
                return 0
            fi
        done
        if [ -d "$arch_dir" ] && ls "$arch_dir"/libAICameraModule.so* >/dev/null 2>&1; then
            echo "$arch_dir"
            return 0
        fi
    done
    return 1
}

find_ffmpeg_lib_dir() {
    local base="$1"
    for arch in linux64_14 arm32_allwinner aarch64_allwinner arm32_pi4; do
        local dir="$base/ffmpeg/lib/$arch"
        if [ -d "$dir" ] && ls "$dir"/libavcodec.so* >/dev/null 2>&1; then
            echo "$dir"
            return 0
        fi
    done
    return 1
}

SDK_LIB_DIR=""
FFMPEG_LIB_DIR=""

if [ -d "$SDK_ROOT" ]; then
    SDK_LIB_DIR=$(find_sdk_lib_dir "$SDK_ROOT" 2>/dev/null || true)
    FFMPEG_LIB_DIR=$(find_ffmpeg_lib_dir "$SDK_ROOT" 2>/dev/null || true)
fi

if [ -n "$SDK_LIB_DIR" ]; then
    export LD_LIBRARY_PATH="${SDK_LIB_DIR}${FFMPEG_LIB_DIR:+:$FFMPEG_LIB_DIR}${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
fi

# ---- 检查二进制 -----------------------------------------------------------
if [ ! -f "$BIN" ]; then
    echo "ERROR: $BIN not found."
    echo "Run 'make' in $PROJECT_DIR first."
    exit 1
fi

if [ ! -x "$BIN" ]; then
    chmod +x "$BIN"
fi

mkdir -p "$LOG_DIR" "$FRAME_DIR"

TIMESTAMP=$(date +%Y%m%d_%H%M%S)
LOG_FILE="$LOG_DIR/aging_${TIMESTAMP}.log"

# ---- 日志函数 -------------------------------------------------------------
log() {
    local ts
    ts=$(date '+%Y-%m-%d %H:%M:%S')
    echo "[$ts] $*" | tee -a "$LOG_FILE"
}

# ---- 统计变量 -------------------------------------------------------------
fail_count=0
pass_count=0
total_frames=0
total_errors=0
round=0
max_temp=0
min_fps_seen=9999
max_fps_seen=0
reconnect_count=0
fps_warn_count=0
stream_fail_count=0
bmp_fail_count=0

cleanup() {
    log "=== Aging test interrupted ==="
    print_summary
    exit 0
}
trap cleanup SIGINT SIGTERM

print_summary() {
    log "================================================================"
    log "  Rounds        : $round"
    log "  Pass / Fail   : $pass_count / $fail_count"
    log "  Total frames  : $total_frames"
    log "  Total errors  : $total_errors"
    log "  FPS range     : ${min_fps_seen} ~ ${max_fps_seen}"
    log "  FPS warnings  : $fps_warn_count (below ${MIN_FPS} fps)"
    log "  Stream fails  : $stream_fail_count"
    log "  BMP fails     : $bmp_fail_count"
    log "  Reconnects    : $reconnect_count"
    log "  Max CPU temp  : ${max_temp} C"
    log "================================================================"
}

log "=== M30 Aging Test Started ==="
log "Config: loops=${LOOPS} stream_sec=${STREAM_SEC} min_fps=${MIN_FPS}"
log "Binary: $BIN"
log "SDK lib: ${SDK_LIB_DIR:-not found}"
log "FFmpeg lib: ${FFMPEG_LIB_DIR:-not found}"
log "LD_LIBRARY_PATH: ${LD_LIBRARY_PATH:-not set}"
log "Log: $LOG_FILE"

# ---- 运行一轮命令测试 (设备信息 + Ping + 截图) ----------------------------
run_cmd_test() {
    local round_num=$1
    local round_pass=1
    local out_file
    out_file=$(mktemp /tmp/m30_aging_out_XXXXXX.txt)

    # 命令序列：
    #   0  -> Ping
    #   1  -> 设备信息
    #   2  -> 分辨率/帧率/光敏
    #   3  -> 保存单帧 BMP
    #   7  -> 查询摄像头状态
    #   23 -> 查询底库数量
    #   33 -> 查询识别状态
    #   99 -> 退出
    {
        echo "0"
        echo "1"
        echo "2"
        echo "3"
        echo "7"
        echo "23"
        echo "33"
        echo "99"
    } | timeout 60 "$BIN" > "$out_file" 2>&1
    local rc=$?

    if [ $rc -ne 0 ]; then
        if [ $rc -eq 124 ]; then
            log "  WARN: cmd test timed out (60s)"
        else
            log "  ERROR: cmd test exit code $rc"
        fi
        round_pass=0
    fi

    # 解析结果
    if grep -q "M30 connected" "$out_file"; then
        log "  connect: OK"
    else
        log "  connect: FAILED"
        round_pass=0
    fi

    if grep -q "\[PING\] ok" "$out_file"; then
        log "  ping: OK"
    else
        log "  ping: FAILED"
        round_pass=0
    fi

    # 提取温度
    local temp
    temp=$(grep -oP 'CPU Temp:\s*\K\d+' "$out_file" 2>/dev/null || echo "0")
    log "  cpu temp: ${temp} C"
    if [ "$temp" -gt "$max_temp" ] 2>/dev/null; then
        max_temp=$temp
    fi

    # 提取分辨率和帧率
    local res fps_val
    res=$(grep -oP 'Resolution:\s*\K\S+' "$out_file" 2>/dev/null || echo "N/A")
    fps_val=$(grep -oP 'Framerate\s*:\s*\K\d+' "$out_file" 2>/dev/null || echo "N/A")
    log "  resolution: $res  framerate: ${fps_val} fps"

    # 提取版本和SN
    local ver sn
    ver=$(grep -oP 'Version\s*:\s*\K.*' "$out_file" 2>/dev/null | head -1 || echo "N/A")
    sn=$(grep -oP 'PCB SN\s*:\s*\K.*' "$out_file" 2>/dev/null || echo "N/A")
    log "  version: $ver  SN: $sn"

    # 摄像头状态
    local cam_state
    cam_state=$(grep -oP 'RGB:\s*\S+\s*\|\s*IR:\s*\S+' "$out_file" 2>/dev/null || echo "N/A")
    log "  camera: $cam_state"

    # BMP 保存
    if grep -q "saved frame.bmp" "$out_file"; then
        local dst="$FRAME_DIR/frame_round${round_num}_$(date +%H%M%S).bmp"
        [ -f "$PROJECT_DIR/frame.bmp" ] && mv "$PROJECT_DIR/frame.bmp" "$dst"
        local fsize=0
        [ -f "$dst" ] && fsize=$(stat -c%s "$dst" 2>/dev/null || echo "0")
        log "  frame save: OK -> $(basename "$dst") (${fsize} bytes)"
    else
        log "  frame save: FAILED"
        bmp_fail_count=$((bmp_fail_count + 1))
        round_pass=0
    fi

    # 底库数量
    local face_cnt
    face_cnt=$(grep -oP 'Face count:\s*\K\d+' "$out_file" 2>/dev/null || echo "N/A")
    log "  face db count: $face_cnt"

    # 识别状态
    local rec_state
    rec_state=$(grep -oP 'Recognition:\s*\K\S+' "$out_file" 2>/dev/null || echo "N/A")
    log "  recognition: $rec_state"

    rm -f "$out_file"

    if [ $round_pass -eq 1 ]; then
        return 0
    else
        return 1
    fi
}

# ---- 视频流测试 (使用菜单16无显示基准模式) --------------------------------
# 注意：老化场景下不能用菜单 15 (video_play/ffplay)，ffplay 需要 X11 display，
# headless/SSH 环境会直接失败。菜单 16 (stream_bench) 是纯拉帧统计，无显示、无写盘。
run_stream_test() {
    local round_num=$1
    local duration=$2
    log "  stream test: ${duration}s ..."

    local out_file
    out_file=$(mktemp /tmp/m30_stream_out_XXXXXX.txt)

    # "16" 进入 headless 基准模式, timeout 后 SIGINT 触发退出
    echo "16" | timeout --signal=SIGINT "$duration" "$BIN" > "$out_file" 2>&1 || true

    # 解析输出：bench done / stream done / video done 三种格式都支持
    # 用 ${var:-0} 兜底，避免 "grep | tail || echo 0" 这种 pipeline 里 || 不触发导致的空串
    local frames avg_fps min_f max_f errs
    frames=$(grep -oP '(?:bench|stream|video) done:\s*\K\d+' "$out_file" 2>/dev/null | tail -1)
    avg_fps=$(grep -oP 'avg\s+\K[0-9.]+(?=\s*fps)' "$out_file" 2>/dev/null | tail -1)
    min_f=$(grep -oP 'min\s+\K[0-9.]+' "$out_file" 2>/dev/null | tail -1)
    max_f=$(grep -oP 'max\s+\K[0-9.]+' "$out_file" 2>/dev/null | tail -1)
    errs=$(grep -oP 'err\s+\K\d+' "$out_file" 2>/dev/null | tail -1)

    # 回退：bench/stream/video done 都没打出来时，从实时刷新行里捞末次 frames/avg
    if [ -z "$frames" ]; then
        frames=$(grep -oP 'frames:\s*\K\d+' "$out_file" 2>/dev/null | tail -1)
        if [ -z "$avg_fps" ]; then
            avg_fps=$(grep -oP 'avg\s+\K[0-9.]+' "$out_file" 2>/dev/null | tail -1)
        fi
    fi

    # 统一兜底为 0，保证后续算术比较不会炸
    frames=${frames:-0}
    avg_fps=${avg_fps:-0}
    min_f=${min_f:-0}
    max_f=${max_f:-0}
    errs=${errs:-0}

    total_frames=$((total_frames + frames))
    total_errors=$((total_errors + errs))
    log "  stream: ${frames} frames, avg ${avg_fps} fps, min ${min_f}, max ${max_f}, err ${errs}"

    # 帧率检查
    if [ "$avg_fps" != "0" ]; then
        local avg_int=${avg_fps%%.*}
        if [ "$avg_int" -lt "$MIN_FPS" ] 2>/dev/null; then
            log "  WARN: avg fps ${avg_fps} below threshold ${MIN_FPS}"
            fps_warn_count=$((fps_warn_count + 1))
        fi
        # 更新全局 min/max fps
        if [ "$min_f" != "0" ]; then
            local min_int=${min_f%%.*}
            if [ "$min_int" -lt "$min_fps_seen" ] 2>/dev/null; then
                min_fps_seen=$min_int
            fi
        fi
        if [ "$max_f" != "0" ]; then
            local max_int=${max_f%%.*}
            if [ "$max_int" -gt "$max_fps_seen" ] 2>/dev/null; then
                max_fps_seen=$max_int
            fi
        fi
    fi

    rm -f "$out_file"

    if [ "${frames:-0}" -gt 0 ]; then
        log "  stream test: OK"
        return 0
    else
        log "  stream test: FAILED (0 frames)"
        stream_fail_count=$((stream_fail_count + 1))
        return 1
    fi
}

# ---- 摄像头开关测试 -------------------------------------------------------
run_camera_switch_test() {
    local round_num=$1
    local out_file
    out_file=$(mktemp /tmp/m30_cam_out_XXXXXX.txt)

    # 命令序列: 查状态 -> 切IR -> 查状态 -> 切回RGB -> 查状态 -> 退出
    {
        echo "7"
        echo "8"
        echo "1"
        sleep 1
        echo "7"
        echo "8"
        echo "0"
        sleep 1
        echo "7"
        echo "99"
    } | timeout 30 "$BIN" > "$out_file" 2>&1 || true

    if grep -q "M30 connected" "$out_file"; then
        log "  camera switch test: OK"
    else
        log "  camera switch test: FAILED"
    fi

    rm -f "$out_file"
}

# ---- 断线重连测试 ---------------------------------------------------------
run_reconnect_test() {
    local round_num=$1
    local out_file
    out_file=$(mktemp /tmp/m30_reconn_out_XXXXXX.txt)

    # 连接 -> Ping -> 退出, 验证设备仍可正常连接
    {
        echo "0"
        echo "99"
    } | timeout 30 "$BIN" > "$out_file" 2>&1
    local rc=$?

    if [ $rc -eq 0 ] && grep -q "\[PING\] ok" "$out_file"; then
        log "  reconnect test: OK"
    else
        log "  reconnect test: FAILED (rc=$rc)"
        reconnect_count=$((reconnect_count + 1))
    fi

    rm -f "$out_file"
}

# ---- 主循环 ---------------------------------------------------------------
while true; do
    round=$((round + 1))
    log "========== Round $round start =========="

    # 1. 命令测试 (设备信息 + Ping + 截图 + 状态查询)
    if run_cmd_test "$round"; then
        pass_count=$((pass_count + 1))
    else
        fail_count=$((fail_count + 1))
        log "--- Round $round cmd test FAILED ---"
    fi

    sleep 2

    # 2. 视频流测试 (纯播放模式, 统计帧率)
    if ! run_stream_test "$round" "$STREAM_SEC"; then
        log "  WARN: stream test failed this round"
    fi

    sleep 2

    # 3. 断线重连测试 (每 10 轮做一次)
    if [ $((round % 10)) -eq 0 ]; then
        run_reconnect_test "$round"
        sleep 2
    fi

    # 4. 摄像头切换测试 (每 5 轮做一次)
    if [ $((round % 5)) -eq 0 ]; then
        run_camera_switch_test "$round"
        sleep 2
    fi

    log "========== Round $round done =========="
    log "Progress: round=$round pass=$pass_count fail=$fail_count frames=$total_frames fps_range=${min_fps_seen}~${max_fps_seen} max_temp=${max_temp}C"
    log ""

    # 每 50 轮输出一次完整摘要
    if [ $((round % 50)) -eq 0 ]; then
        print_summary
    fi

    # 轮间间隔
    sleep 3

    # 检查是否达到目标循环次数
    if [ "$LOOPS" -gt 0 ] && [ "$round" -ge "$LOOPS" ]; then
        log "=== Target $LOOPS rounds reached ==="
        break
    fi
done

log "=== Aging test completed ==="
print_summary
