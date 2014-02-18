#include "Geom.h"
#include <stdlib.h> //For NULL definition


Triangle2 Triangle2_new(Vector2 a, Vector2 b, Vector2 c){
	Triangle2 t = {a, b, c};
	return t;
}

void Triangle2_barCoord(Triangle2 t, float x, float y, float* l1, float* l2, float* l3){
	float y2y3 = t.b.y - t.c.y;
	float xx3 = x - t.c.x;
	float x3x2 = t.c.x - t.b.x;
	float yy3 = y - t.c.y;
	float x1x3 = t.a.x - t.c.x;
	float y1y3 = t.a.y - t.c.y;
	float y3y1 = -1 * y1y3;

	float numL1 = y2y3 * xx3 + x3x2 * yy3;
	float numL2 = y3y1 * xx3 + x1x3 * yy3;

	float denom = y2y3 * x1x3 + x3x2 * y1y3;

	float tL1 = numL1 / denom;
	float tL2 = numL2 / denom;

	if( l1 != NULL )
		*l1 = tL1;

	if( l2 != NULL)
		*l2 = tL2;

	if( l3 != NULL)
		*l3 = 1 - tL1 - tL2;
}

Triangle2 Triangle2_applyTransform(Triangle2 t, Matrix3 matrix){

	Triangle2 out;
	out.a = Matrix3_transform(matrix, t.a);
	out.b = Matrix3_transform(matrix, t.b);
	out.c = Matrix3_transform(matrix, t.c);

	return out;
}

struct TriangleNode{
	Triangle2 triangle;
	struct TriangleNode* next;
};

typedef struct TriangleNode TriangleNode;

typedef struct TriangleList{
	TriangleNode* iterPtr;
	TriangleNode* first;
} TriangleList;


TriangleNode* TriangleNode_new(){
	TriangleNode* n = (TriangleNode* )malloc(sizeof(TriangleNode));
	n->next = NULL;
	return n;
}

TriangleListRef TriangleList_new(){
	TriangleListRef ref = (TriangleListRef)malloc(sizeof(TriangleList));
	ref->iterPtr = NULL;
	ref->first = NULL;
	//ref->head = TriangleNode_new();
	return ref;
}
void TriangleList_delete(TriangleListRef l){
	//Iterate through all the nodes (even head)
	TriangleNode* p = NULL;
	TriangleNode* c = l->first;
	while( c != NULL ){
		p = c;
		c = c->next;
		free( p );
	}

	//Delete the list
	free( l );
}

void TriangleList_add(TriangleListRef l, Triangle2 t){
	TriangleNode* node = TriangleNode_new();
	node->triangle = t;

	//Empty list
	if( l->first == NULL ){
		l->first = node;
		return;
	}

	//Go to the lastvalid node
	TriangleNode* p = NULL;
	TriangleNode* c = l->first;
	while( c != NULL ){
		p = c;
		c = c->next;
	}

	//Link at p
	p->next = node;
}

char TriangleList_hasNext(TriangleListRef l){
	if( l->first == NULL )
		return 0;

	if( l->iterPtr == NULL )
		return 0;

	return (l->iterPtr->next != NULL);
}
Triangle2 TriangleList_next(TriangleListRef l){
	Triangle2 t = l->iterPtr->triangle;
	l->iterPtr = l->iterPtr->next;
	return t;
}

void TriangleList_begin(TriangleListRef l){
	l->iterPtr = l->first;
}

void TriangleList_applyTransform(TriangleListRef list, Matrix3 matrix){
	TriangleNode* c = list->first;
	while( c != NULL ){
		c->triangle = Triangle2_applyTransform(c->triangle, matrix);
		c = c->next;
	}
}
