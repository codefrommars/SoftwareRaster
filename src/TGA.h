#ifndef TGA_H_
#define TGA_H_

#include <inttypes.h>

#pragma pack(1)

typedef struct{
	uint8_t id_len;//1 byte	ID length	Length of the image ID field
	uint8_t color_map_type;//1 byte	Color map type	Whether a color map is included
	uint8_t image_type;//1 byte	Image type	Compression and color types

	//	5 bytes	Color map specification	Describes the color map
	uint16_t color_map_offset; //(2 bytes): offset into the color map table
	uint16_t color_map_lenght; //(2 bytes): number of entries
	uint8_t color_map_bits_per_pixel; //(1 byte): number of bits per pixel

	//	10 bytes	Image specification	Image dimensions and format
	uint16_t image_lower_left; //(2 bytes): absolute coordinate of lower-left corner for displays where origin is at the lower left
	uint16_t image_y_origin; //Y-origin (2 bytes): as for X-origin
	uint16_t image_width; //Image width (2 bytes): width in pixels
	uint16_t image_height; //Image height (2 bytes): height in pixels
	uint8_t image_bits_per_pixel; //Pixel depth (1 byte): bits per pixel
	uint8_t image_descriptor; //Image descriptor (1 byte): bits 3-0 give the alpha channel depth, bits 5-4 give direction
} TGA_HEADER;

#pragma pack()

#define COLOR_MAP_TYPE_NO_COLOR_MAP 	0
#define COLOR_MAP_TYPE_USE_COLOR_MAP	1

#define IMAGE_TYPE_NO_IMAGE				0
#define IMAGE_TYPE_COLOR_MAPPED			1
#define IMAGE_TYPE_TRUE_COLOR			2
#define IMAGE_TYPE_GRAYSCALE			3
#define IMAGE_TYPE_ENCODED_COLOR_MAPPED	9
#define IMAGE_TYPE_ENCODED_TRUE_COLOR	10
#define IMAGE_TYPE_ENCODED_GRAYSCALE	11

#define IMAGE_DESC_ALPHA_BITS(x) 	x
#define IMAGE_DESC_INVERT_X			16
#define IMAGE_DESC_INVERT_Y			32

TGA_HEADER TGA_new();

#endif /* TGA_H_ */
