#include "Vector4.h"
#include "Matrix.h"
#include <cmath>


Vector4 Vector4::normalize() {
	float xn, yn, zn;
	xn = x / magnitude();
	yn = y / magnitude();
	zn = z / magnitude();
	x = xn;
	y = yn;
	z = zn;
	return *this;
}

float Vector4::magnitude() {
	return sqrtf(x*x + y*y + z*z);
}

Vector4 Vector4::operator*(Matrix &m) {
	Vector4 v;
	v.x += x * m[0][0];
	v.x += y * m[1][0];
	v.x += z * m[2][0];
	v.x += w * m[3][0];

	v.y += x * m[0][1];
	v.y += y * m[1][1];
	v.y += z * m[2][1];
	v.y += w * m[3][1];

	v.z += x * m[0][2];
	v.z += y * m[1][2];
	v.z += z * m[2][2];
	v.z += w * m[3][2];

	v.w += x * m[0][3];
	v.w += y * m[1][3];
	v.w += z * m[2][3];
	v.w += w * m[3][3];
	return v;
}

Vector4 Vector4::operator+(Vector4 &rhs) {
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector4 Vector4::operator-() {
	return Vector4(-x, -y, -z);
}

Vector4 Vector4::operator-(Vector4& rhs) {
	return *this + (-rhs);
}