
#include <malloc.h>
#include <stdio.h>
#include "Raster.h"
#include "Color.h"
#include "BMP.h"
#include "TGA.h"

struct Raster{
	int width, height;
	ARGBColor* pixels;
};

typedef struct Raster Raster;

RasterRef Raster_new(int width, int height){
	RasterRef raster = (RasterRef)malloc(sizeof(Raster));
	raster->width = width;
	raster->height = height;
	raster->pixels = (ARGBColor*)malloc(sizeof(ARGBColor) * width * height);

	//Set it to clear !
	for(int i = 0; i < width * height; i++)
		raster->pixels[i] = 0x00000000;

	return raster;
}

void Raster_delete(RasterRef raster){
	free(raster->pixels);
	free(raster);
}

#define RASTER_INDEX(r, x, y) (x + r->width * y)

void Raster_fillTriangle(RasterRef raster, Triangle2 t, Color c1, Color c2, Color c3){

	for(int y = 0; y < raster->height; y++){
		for(int x = 0; x < raster->width; x++){
			float l1, l2, l3;

			//Get Barycentric coords
			Triangle2_barCoord(t, x, y, &l1, &l2, &l3);

			//Check if they are inside the triangle.
			if( l1 >= 0 && l2 >= 0 && l3 >= 0 ){
				//Interpolate the color.
				Color c = Color_add(Color_add(Color_scale(c1, l1), Color_scale(c2, l2)), Color_scale(c3, l3));

				//Put the color
				raster->pixels[raster->width * y + x] = color_toARGB(c);
			}
		}
	}
}

void Raster_saveToPPM(RasterRef raster, char* path){

}

void Raster_putPixel(RasterRef raster, int x, int y, ARGBColor c){
	raster->pixels[x + y * raster->width] = c;
}

void WriteByte(FILE *file, unsigned char b) {
  fwrite((void*)&b,sizeof(unsigned char),1,file);
}

void Raster_saveToTGA(RasterRef raster, char* filename){
	FILE *file = fopen(filename, "wb");

	TGA_HEADER tga = TGA_new();
	tga.image_type = IMAGE_TYPE_TRUE_COLOR;
	tga.image_width = raster->width;
	tga.image_height = raster->height;
	tga.image_bits_per_pixel = 32;
	tga.image_descriptor = IMAGE_DESC_ALPHA_BITS(8);

	fwrite(&tga, sizeof(tga), 1, file);
	fwrite(raster->pixels, sizeof(ARGBColor), raster->width * raster->height, file);

	fclose(file);
}

void Raster_saveToBMP(RasterRef raster, char* path){
	BMP_HEADER bmp = BMP_new();
	bmp.offset_data = 54;
	bmp.width = raster->width;
	bmp.height = raster->height;
	bmp.bits_per_pixel = 32;
	bmp.image_size = raster->width * raster->height * bmp.bits_per_pixel / 8;
	bmp.hRes = 2835;
	bmp.vRes = 2835;
	bmp.file_size = 54 + bmp.image_size;

	FILE* f = fopen(path, "wb");
	if (f == NULL )
		return;

	fwrite(&bmp, sizeof(bmp), 1, f);
	fwrite(raster->pixels, sizeof(ARGBColor), bmp.width * bmp.height, f);

	fclose(f);
}

void Raster_fillTriangleList(RasterRef raster, TriangleListRef list, Color c1, Color c2, Color c3){
	TriangleList_begin(list);
	while( TriangleList_hasNext(list) ){
		Triangle2 t = TriangleList_next(list);
		Raster_fillTriangle(raster, t, c1, c2, c3);
	}
}
