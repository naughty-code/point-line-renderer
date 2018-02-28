#pragma once
struct Matrix;
struct Vector4
{
	Vector4(float x0 = 0, float y0 = 0, float z0 = 0, float w0 = 1) : x(x0), y(y0), z(z0), w(w0) {};
	float x, y, z, w;
	Vector4 normalize();
	float magnitude();
	Vector4 operator*(Matrix &m);
	Vector4 operator+(Vector4 & rhs);
	Vector4 operator-();
	Vector4 operator-(Vector4 & rhs);
};

