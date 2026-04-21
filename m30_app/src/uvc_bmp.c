/*
 * uvc_bmp.c  -  轻量级 32 位 BMP 写出实现
 *
 *   写出 top-down BI_RGB 位图，使用负值 height 使输入 BGRA 缓冲区的
 *   第 0 行出现在文件顶部，与厂商 UVC 帧的行序一致。
 */
#include "uvc_bmp.h"
#include "uvc_log.h"

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#pragma pack(push, 1)
struct bmp_file_header {
    uint16_t type;          /* 'BM' 魔术字节              */
    uint32_t size;          /* 文件总大小（字节）          */
    uint16_t r1;            /* 保留字段 1                  */
    uint16_t r2;            /* 保留字段 2                  */
    uint32_t offset;        /* 像素数据起始偏移            */
};
struct bmp_info_header {
    uint32_t size;          /* 本结构体大小                */
    int32_t  width;         /* 图像宽度（像素）            */
    int32_t  height;        /* 图像高度（负值 = 自顶向下） */
    uint16_t planes;        /* 颜色平面数，固定为 1        */
    uint16_t bit_count;     /* 每像素位数                  */
    uint32_t compression;   /* 压缩方式，0 = 无压缩       */
    uint32_t size_image;    /* 图像数据大小（字节）        */
    int32_t  xppm;          /* 水平分辨率（像素/米）       */
    int32_t  yppm;          /* 垂直分辨率（像素/米）       */
    uint32_t colors_used;   /* 调色板颜色数                */
    uint32_t colors_important; /* 重要颜色数               */
};
#pragma pack(pop)

int uvc_bmp_write(const char *path, const void *bgra, int width, int height)
{
    if (!path || !bgra || width <= 0 || height <= 0)
        return -EINVAL;

    const size_t row_bytes = (size_t)width * 4u;
    const size_t img_bytes = row_bytes * (size_t)height;
    const size_t hdr_bytes = sizeof(struct bmp_file_header) +
                             sizeof(struct bmp_info_header);

    struct bmp_file_header fh;
    struct bmp_info_header ih;
    memset(&fh, 0, sizeof(fh));
    memset(&ih, 0, sizeof(ih));

    fh.type   = 0x4D42;                          /* 'BM' */
    fh.size   = (uint32_t)(hdr_bytes + img_bytes);
    fh.offset = (uint32_t)hdr_bytes;

    ih.size        = sizeof(ih);
    ih.width       = width;
    ih.height      = -height;                    /* 负值表示自顶向下 */
    ih.planes      = 1;
    ih.bit_count   = 32;
    ih.compression = 0;
    ih.size_image  = (uint32_t)img_bytes;

    FILE *fp = fopen(path, "wb");
    if (!fp) {
        UVC_LOGE("fopen(%s) failed: %s", path, strerror(errno));
        return -errno;
    }

    int rc = 0;
    if (fwrite(&fh,   sizeof(fh), 1, fp) != 1 ||
        fwrite(&ih,   sizeof(ih), 1, fp) != 1 ||
        fwrite(bgra,  img_bytes,  1, fp) != 1) {
        UVC_LOGE("BMP write failed: %s", strerror(errno));
        rc = -EIO;
    }

    if (fclose(fp) != 0 && rc == 0) {
        UVC_LOGE("fclose(%s) failed: %s", path, strerror(errno));
        rc = -errno;
    }
    return rc;
}
