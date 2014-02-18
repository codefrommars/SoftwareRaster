#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BMP.h"
#include "TGA.h"
#include "RAW.h"
#include "Raster.h"
#include "U2D.h"

void testScene(){
	Vector2 a = Vector2_new(128, 76);
	Vector2 b = Vector2_new(200, 200);
	Vector2 c = Vector2_new(50, 150);

	Triangle2 t = Triangle2_new( a, c, b);

	Color red = COLOR_RED;
	Color blue = COLOR_BLUE;


	int n = 250;
	RasterRef r = Raster_new(n, n);
	Raster_fillTriangle(r, t, COLOR_WHITE, red, blue);

	Raster_saveToBMP(r, "image.bmp");
	Raster_saveToTGA(r, "render.tga");
	Raster_delete(r);
}

void testRaw(){
	TriangleListRef list = RAW_load("rocket.raw");

	if( list == NULL )
		return;

	TriangleList_begin(list);

	while( TriangleList_hasNext(list) ){
		Triangle2 t = TriangleList_next(list);
		printf("%f %f %f %f %f %f\n", t.a.x, t.a.y, t.b.x, t.b.y,t.c.x, t.c.y );
	}
	TriangleList_delete(list);
}

void testU2D(){
	U2D_runFile("scene3.u2d");
}

int main(void) {
	testU2D();
	return EXIT_SUCCESS;
}
