#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// BMP文件头结构
#pragma pack(2)
typedef struct {
    uint16_t type;           // 文件类型，"BM"表示BMP文件
    uint32_t size;           // 文件大小
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;         // 数据偏移量
} BMPHeader;
#pragma pack()

// BMP信息头结构
#pragma pack(2)
typedef struct {
    uint32_t size;           // 信息头大小
    int32_t  width;          // 图像宽度
    int32_t  height;         // 图像高度
    uint16_t planes;         // 颜色平面数，始终为1
    uint16_t bit_count;      // 位深度，这里设为32表示每个像素占32位
    uint32_t compression;    // 压缩类型，0表示不压缩
    uint32_t size_image;     // 图像大小，可以为0
    int32_t  x_pixels_per_meter;
    int32_t  y_pixels_per_meter;
    uint32_t colors_used;    // 使用的颜色数，0表示使用所有颜色
    uint32_t colors_important;
} BMPInfoHeader;
#pragma pack()

extern void writeBMP(const char *filename, uint32_t *data, int width, int height);
