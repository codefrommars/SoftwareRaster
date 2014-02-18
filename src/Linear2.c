
#include "Linear2.h"
#include <math.h>

Vector2 Vector2_new(Scalar x, Scalar y){
	Vector2 v = {x , y};
	return v;
}

Vector2 Vector2_add(Vector2 v1, Vector2 v2){
	Vector2 v = { v1.x + v2.x , v1.y + v2.y };
	return v;
}

Vector2 Vector2_scale(Vector2 v, Scalar s){
	v.x *= s;
	v.y *= s;
	return v;
}

Matrix3 Matrix3_new(Scalar m11, Scalar m21, Scalar m31,
		Scalar m12, Scalar m22, Scalar m32,
		Scalar m13, Scalar m23, Scalar m33){
	Matrix3 m = {m11, m21, m31,
			m12, m22, m32,
			m13, m23, m33};
	return m;
}

Matrix3 Matrix3_makeRotation(Scalar radians){

	Scalar cos = cosf(radians);
	Scalar sin = sinf(radians);

	Matrix3 m = {
			cos, 	-sin, 	0,
			sin, 	cos,	0,
			0, 		0, 		1
	};

	return m;
}
Matrix3 Matrix3_makeTranslation(Scalar tx, Scalar ty){

	Matrix3 m = {
			1, 	0, 	tx,
			0, 	1,	ty,
			0, 	0, 	1
	};

	return m;
}
Matrix3 Matrix3_makeScale(Scalar sx, Scalar sy){
	Matrix3 m = {
			sx, 0, 	0,
			0, 	sy,	0,
			0, 	0, 	1
	};

	return m;
}

Matrix3 Matrix3_multiply(Matrix3 a, Matrix3 b){
	Scalar m11 = a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
	Scalar m21 = a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
	Scalar m31 = a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;

	Scalar m12 = a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
	Scalar m22 = a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
	Scalar m32 = a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;

	Scalar m13 = a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
	Scalar m23 = a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
	Scalar m33 = a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;

	return Matrix3_new(m11, m21, m31, m12, m22, m32, m13, m23, m33);

}
Vector2 Matrix3_transform(Matrix3 a, Vector2 v){
	Scalar x = a.m11 * v.x + a.m21 * v.y + a.m31;
	Scalar y = a.m12 * v.x + a.m22 * v.y + a.m32;

	return Vector2_new(x, y);
}
