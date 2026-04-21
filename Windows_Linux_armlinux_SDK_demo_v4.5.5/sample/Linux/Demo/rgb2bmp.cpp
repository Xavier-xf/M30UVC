#include "rgb2bmp.h"

// 将BGRA数据写入BMP文件
void writeBMP(const char *filename, uint32_t *data, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // BMP文件头
    BMPHeader header = {
        .type = 0x4D42,       // "BM"
        .size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + width * height * sizeof(uint32_t),
        .reserved1 = 0,
        .reserved2 = 0,
        .offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader)
    };
    fwrite(&header, sizeof(BMPHeader), 1, file);

    // BMP信息头
    BMPInfoHeader infoHeader = {
        .size = sizeof(BMPInfoHeader),
        .width = width,
        .height = height,
        .planes = 1,
        .bit_count = 32,
        .compression = 0,
        .size_image = 0,
        .x_pixels_per_meter = 0,
        .y_pixels_per_meter = 0,
        .colors_used = 0,
        .colors_important = 0
    };
    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // 写入像素数据
    fwrite(data, sizeof(uint32_t), width * height, file);
	fflush(file);
    fclose(file);
}
