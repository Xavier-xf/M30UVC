# ============================================================================
#  Makefile  -  M30 UVC 应用层封装（纯 C）
#
#  本机编译（x86_64 主机自测/语法检查）:
#      make TARGET_ARCH=linux64_14
#
#  交叉编译（目标 arm-openwrt 平台，默认使用 arm32_allwinner 库路径）:
#      make CROSS_COMPILE=arm-openwrt-linux-muslgnueabi- TARGET_ARCH=arm32_allwinner
#  SDK 支持的其他目标平台目录（位于 lib/ 下）:
#      arm32_allwinner  arm32_pi4  aarch64_allwinner  aarch64_skyj
#      aarch64_tk2s     imx6ull    linux64_14
#
#  libAICameraModule.so 使用 libstdc++ 构建，因此链接时需显式拉入 -lstdc++，
#  确保纯 C 二进制也能正确链接。
# ============================================================================

PROJECT       := m30_demo
BUILD_DIR     := build
BIN           := $(BUILD_DIR)/$(PROJECT)

# ---- 工具链配置 -----------------------------------------------------------
CROSS_COMPILE ?=
CC            := $(CROSS_COMPILE)gcc
AR            := $(CROSS_COMPILE)ar
STRIP         := $(CROSS_COMPILE)strip

# ---- 厂商 SDK 路径 -------------------------------------------------------
SDK_ROOT      ?= ../Windows_Linux_armlinux_SDK_demo_v4.5.5
TARGET_ARCH   ?= arm32_allwinner

# 自动探测 SDK 库子目录：不同平台目录名不统一（release / libRelease / libDebug）
# 优先选 libDebug（版本更新，含 MirrorCamRgbIr 等新接口），其次 release / libRelease
SDK_LIB_BASE  := $(SDK_ROOT)/lib/$(TARGET_ARCH)
SDK_LIB_DIR   := $(if $(wildcard $(SDK_LIB_BASE)/libDebug),$(SDK_LIB_BASE)/libDebug,\
                 $(if $(wildcard $(SDK_LIB_BASE)/release),$(SDK_LIB_BASE)/release,\
                 $(if $(wildcard $(SDK_LIB_BASE)/libRelease),$(SDK_LIB_BASE)/libRelease,\
                 $(SDK_LIB_BASE))))

# FFmpeg 库路径（libAICameraModule.so 依赖 ffmpeg）
FFMPEG_LIB_DIR := $(SDK_ROOT)/ffmpeg/lib/$(TARGET_ARCH)

# ---- 源文件 --------------------------------------------------------------
SRC_WRAPPER   := src/uvc_m30.c src/uvc_bmp.c
SRC_MAIN      := example/main.c
SRCS          := $(SRC_WRAPPER) $(SRC_MAIN)
OBJS          := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS          := $(OBJS:.o=.d)

# ---- 编译选项 -------------------------------------------------------------
CFLAGS   ?= -O2 -g -std=gnu11 -fPIC -pthread \
            -Wall -Wextra -Wshadow -Wformat=2 -Wcast-align \
            -Wpointer-arith -Wuninitialized -Wstrict-prototypes \
            -Wmissing-prototypes -Wno-unused-parameter \
            -fstack-protector-strong -D_FORTIFY_SOURCE=2
CPPFLAGS += -Iinclude -Isrc -MMD -MP

LDFLAGS  += -L$(SDK_LIB_DIR) -L$(FFMPEG_LIB_DIR) \
            -Wl,-rpath,'$$ORIGIN' \
            -Wl,-rpath,$(SDK_LIB_DIR) \
            -Wl,-rpath,$(FFMPEG_LIB_DIR)
LDLIBS   += -lAICameraModule \
            -lavutil -lavcodec -lswscale -lavformat -lavdevice -lswresample \
            -lpthread -ldl -lm -lstdc++

# ---- 构建规则 -------------------------------------------------------------
.PHONY: all clean install strip print-config run aging

all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
	@echo "[链接] $@"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "[编译] $<"

strip: $(BIN)
	$(STRIP) --strip-unneeded $(BIN)

install: $(BIN)
	install -d $(DESTDIR)/usr/local/bin
	install -m 0755 $(BIN) $(DESTDIR)/usr/local/bin/
	install -d $(DESTDIR)/usr/local/lib
	install -m 0644 $(SDK_LIB_DIR)/libAICameraModule.so* \
	        $(DESTDIR)/usr/local/lib/ 2>/dev/null || true
	install -m 0644 $(FFMPEG_LIB_DIR)/lib*.so* \
	        $(DESTDIR)/usr/local/lib/ 2>/dev/null || true

print-config:
	@echo "CC             = $(CC)"
	@echo "TARGET_ARCH    = $(TARGET_ARCH)"
	@echo "SDK_LIB_DIR    = $(SDK_LIB_DIR)"
	@echo "FFMPEG_LIB_DIR = $(FFMPEG_LIB_DIR)"
	@ls $(SDK_LIB_DIR)/libAICameraModule.so* 2>/dev/null || echo "WARNING: libAICameraModule.so not found in SDK_LIB_DIR"
	@ls $(FFMPEG_LIB_DIR)/libavcodec.so* 2>/dev/null || echo "WARNING: ffmpeg libs not found in FFMPEG_LIB_DIR"

run: $(BIN)
	LD_LIBRARY_PATH=$(SDK_LIB_DIR):$(FFMPEG_LIB_DIR) $(BIN)

aging: $(BIN)
	chmod +x test/aging_test.sh
	LD_LIBRARY_PATH=$(SDK_LIB_DIR):$(FFMPEG_LIB_DIR) test/aging_test.sh

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
