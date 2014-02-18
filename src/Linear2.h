
#ifndef LINEAR2_H_
#define LINEAR2_H_

typedef float Scalar;

typedef struct{
	Scalar x, y;
} Vector2;

Vector2 Vector2_new(Scalar x, Scalar y);
Vector2 Vector2_add(Vector2 v1, Vector2 v2);
Vector2 Vector2_scale(Vector2 v, Scalar s);

typedef struct{
	Scalar 	m11, m21, m31,
			m12, m22, m32,
			m13, m23, m33;
} Matrix3;

Matrix3 Matrix3_new(Scalar m11, Scalar m21, Scalar m31,
		Scalar m12, Scalar m22, Scalar m32,
		Scalar m13, Scalar m23, Scalar m33);

Matrix3 Matrix3_makeRotation(Scalar radians);
Matrix3 Matrix3_makeTranslation(Scalar tx, Scalar ty);
Matrix3 Matrix3_makeScale(Scalar sx, Scalar sy);

Matrix3 Matrix3_multiply(Matrix3 a, Matrix3 b);
Vector2 Matrix3_transform(Matrix3 a, Vector2 v);

#define MATRIX3_IDENTITY Matrix3_new(1, 0, 0, 0, 1, 0, 0, 0, 1)

#endif /* LINEAR2_H_ */
