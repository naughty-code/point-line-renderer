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

	v.x = x * m[0][0] + y * m[1][0] + z * m[2][0] + w * m[3][0];

	v.y += x * m[0][1] + y * m[1][1] + z * m[2][1] + w * m[3][1];
	
	v.z += x * m[0][2] + y * m[1][2] + z * m[2][2] + w * m[3][2];
	
	v.w += x * m[0][3] + y * m[1][3] + z * m[2][3] + w * m[3][3];
	
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

float dot(Vector4 v1, Vector4 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}