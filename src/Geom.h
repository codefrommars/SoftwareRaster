
#ifndef GEOM_H_
#define GEOM_H_

#include "Linear2.h"

typedef struct{
	Vector2 a, b, c;
} Triangle2;

Triangle2 Triangle2_new(Vector2 a, Vector2 b, Vector2 c);

void Triangle2_barCoord(Triangle2 t, float x, float y, float* l1, float* l2, float* l3);
Triangle2 Triangle2_applyTransform(Triangle2 t, Matrix3 matrix);


typedef struct TriangleList* TriangleListRef;

TriangleListRef TriangleList_new();
void TriangleList_delete(TriangleListRef l);

void TriangleList_add(TriangleListRef l, Triangle2 t);

char TriangleList_hasNext(TriangleListRef l);
Triangle2 TriangleList_next(TriangleListRef l);

void TriangleList_begin(TriangleListRef l);

void TriangleList_applyTransform(TriangleListRef l, Matrix3 matrix);

#endif /* GEOM_H_ */
