#ifndef RASTER_H_
#define RASTER_H_

#include "Geom.h"
#include "Color.h"

typedef struct Raster* RasterRef;

RasterRef Raster_new(int width, int height);
void Raster_delete(RasterRef raster);

void Raster_putPixel(RasterRef raster, int x, int y, ARGBColor c);
void Raster_fillTriangle(RasterRef raster, Triangle2 t, Color c1, Color c2, Color c3);
void Raster_fillTriangleList(RasterRef raster, TriangleListRef list, Color c1, Color c2, Color c3);
void Raster_saveToPPM(RasterRef raster, char* path);
void Raster_saveToBMP(RasterRef raster, char* path);
void Raster_saveToTGA(RasterRef raster, char* path);

#endif /* RASTER_H_ */
