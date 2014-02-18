#include <stdio.h>
#include "RAW.h"

TriangleListRef RAW_load(char* filename){
	FILE* f = fopen(filename, "r");

	TriangleListRef list = TriangleList_new();

	Vector2 a, b, c;
	float ign;
	int r = 0;
	do{
		r = fscanf(f, "%f %f %f %f %f %f %f %f %f",
				&a.x, &a.y, &ign,
				&b.x, &b.y, &ign,
				&c.x, &c.y, &ign);

		//Compare or something.
		if( r < 9 && r != EOF ){
			printf("Malformed RAW.\n");
			TriangleList_delete(list);
			return NULL;
		}

		Triangle2 t = Triangle2_new(a, b, c);
		TriangleList_add(list, t);
	}while( r == 9 );

	return list;

}
