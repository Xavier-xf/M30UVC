/* uvc_bmp.h  -  轻量级 32 位 BMP 图片写出工具 */
#ifndef UVC_BMP_H
#define UVC_BMP_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 成功返回 0，失败返回负的 errno 值 */
int uvc_bmp_write(const char *path, const void *bgra, int width, int height);

#ifdef __cplusplus
}
#endif
#endif
