#ifndef BMP_H_
#define BMP_H_

#include <inttypes.h>
#include <stdio.h>

#pragma pack(1)

typedef struct{
	uint16_t id;
	uint32_t file_size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offset_data;
	uint32_t header_size;
	int32_t width;
	int32_t height;
	uint16_t color_planes;
	uint16_t bits_per_pixel;
	uint32_t compression;
	uint32_t image_size;
	uint32_t hRes;
	uint32_t vRes;
	uint32_t palette_size;
	uint32_t important_colors;
} BMP_HEADER;

#pragma pack()

BMP_HEADER BMP_new();

#endif /* BMP_H_ */
