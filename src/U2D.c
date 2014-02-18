#include <stdio.h>
#include <stdlib.h>
#include "U2D.h"
#include "Raster.h"
#include "RAW.h"

void invalid(char* reason){
	printf("Not valid u2d file: %s\n", reason);
}

TriangleListRef scanGeometry(FILE* f){
	char name[256];
	int scanned = fscanf(f, "%s\n", name);
	if( scanned != 1 ){
		invalid("filename invalid");
		return NULL;
	}
	TriangleListRef list  = RAW_load(name);
	return list;
}

void scanColors(FILE* f, Color* c1, Color* c2, Color* c3){
	int scanned = fscanf(f, "%f %f %f %f %f %f %f %f %f\n", &c1->r, &c1->g, &c1->b, &c2->r, &c2->g, &c2->b, &c3->r, &c3->g, &c3->b );
	if( scanned != 9 ){
		invalid("invalid color line");
	}
}

void scanTranslation(FILE* f, Matrix3* matrix){
	float tx, ty;
	int scanned = fscanf(f, "%f %f\n", &tx, &ty);

	if( scanned != 2 ){
		invalid("invalid scale line");
		return;
	}

	Matrix3 trans = Matrix3_makeTranslation(tx, ty);
	*matrix = Matrix3_multiply(*matrix, trans);
}

void scanRotation(FILE* f, Matrix3* matrix){
	float theta;
	int scanned = fscanf(f, "%f\n", &theta);

	if( scanned != 1 ){
		invalid("invalid rotation line");
		return;
	}

	Matrix3 rot = Matrix3_makeRotation(theta);
	*matrix = Matrix3_multiply(*matrix, rot);
}

void scanScale(FILE* f, Matrix3* matrix){
	float sx, sy;
	int scanned = fscanf(f, "%f %f\n", &sx, &sy);

	if( scanned != 2 ){
		invalid("invalid scale line");
		return;
	}

	Matrix3 scale = Matrix3_makeScale(sx, sy);
	*matrix = Matrix3_multiply(*matrix, scale);
}

void U2D_runFile(char* file){
	FILE* f = fopen(file, "r");

	//Test the magic number
	char c1, c2;
	int scanned = fscanf(f, "%c%c\n", &c1, &c2);
	if( scanned != 2 ){
		invalid("doesnt read the magic number");
		return;
	}

	if( c1 != 'U' || c2 != '2' ){
		invalid("chars are not U2");
		return;
	}

	//get the width and height
	int width, height;
	scanned = fscanf(f, "%i %i\n", &width, &height);
	if( scanned != 2 ){
		invalid("doesnt read the dimension");
		return;
	}

	if( width <=  0 || height <= 0 ){
		invalid("invalid dimension");
		return;
	}

	//get the bounds
	float minX, minY, maxX, maxY;
	scanned = fscanf(f, "%f %f %f %f\n", &minX, &minY, &maxX, &maxY);
	if( scanned != 4 ){
		invalid("doesnt read the bounds");
		return;
	}

	//Calculate the initial transform
	//Scale in x axis (view 2 screen)
	float sx = (float)width / abs(maxX - minX);
	float sy = (float)height / abs(maxY - minY);
	Matrix3 sInit = Matrix3_makeScale(sx, sy);

	//Translate.
	float tx = -minX;
	float ty = -minY;
	Matrix3 tInit = Matrix3_makeTranslation(tx, ty);

	//View2Screen Matrix
	Matrix3 view2Screen = Matrix3_multiply(sInit, tInit);

	TriangleListRef geometry = NULL;
	Matrix3 transform = MATRIX3_IDENTITY;
	Color color1, color2, color3;

	color1.a = color2.a = color3.a = 1.0;

	printf("Scanning file...\n");

	char reading = 1;
	char onError = 0;
	do{
		char op = -1;
		scanned = fscanf(f, "%c ", &op);
		if( scanned == EOF ){
			reading = 0;
			break;
		}

		switch(op){
			case 'g':
				geometry = scanGeometry(f);
				if( geometry == NULL )
					reading = 0;
				break;
			case 'c':
				scanColors(f, &color1, &color2, &color3);
				break;
			case 't':
				scanTranslation(f, &transform);
				break;
			case 'r':
				scanRotation(f, &transform);
				break;
			case 's':
				scanScale(f, &transform);
				break;
			default:
				invalid("Invalid opcode");
				onError = 1;
				break;
		}
	}while(reading && !onError);

	fclose(f);

	if( geometry == NULL )
		return;
	else if (onError){
		TriangleList_delete(geometry);
		return;
	}

	printf("Applying Transformations...\n");
	transform = Matrix3_multiply(view2Screen, transform);
	TriangleList_applyTransform(geometry, transform);

	//Create the raster.
	RasterRef raster = Raster_new(width, height);

	printf("Rendering triangles...\n");
	Raster_fillTriangleList(raster, geometry, color1, color2, color3);

	printf("Writing files...\n");
	Raster_saveToTGA(raster, "out.tga");
	Raster_saveToBMP(raster, "out.bmp");

	printf("Cleaning up...\n");
	//Kill the raster
	Raster_delete(raster);

	//Kill Geometry
	TriangleList_delete(geometry);

	printf("Successful Execution!\n");
}
