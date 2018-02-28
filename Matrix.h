#pragma once
#include "Vector4.h"
#include <iostream>
struct Matrix
{
	float m[4][4];
	Matrix(float = 1);
	Matrix(float d[4][4]);
	Matrix(Matrix & rhs);
	Matrix scale(float, float, float, float = 1);
	Matrix translate(float x, float y, float z);
	Matrix bank(float angle); // roll
	Matrix pitch(float angle); 
	Matrix rotate(Vector4 n, float angle);
	Matrix rotateAlter(Vector4 n, float angle);
	Matrix lookAt(Vector4 camPosition, Vector4 lookPosition);
	Matrix head(float angle); // yawn
	float* operator[](int i) { return m[i]; };
	const float* operator[](int i) const { return m[i]; };
	Matrix operator*(Matrix rhs);
	Matrix clone();
	void print(const Matrix & m, std::ostream & out);
};

