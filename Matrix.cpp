#include "Matrix.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

Matrix::Matrix(float s) { // s = 1 by default
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = i == j ? s : 0;
		}
	}
	m[3][3] = 1;
}

Matrix::Matrix(float d[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = d[i][j];
		}
	}
}

Matrix::Matrix(Matrix& rhs) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = rhs[i][j];
		}
	}
}

Matrix Matrix::scale(float x, float y, float z, float w) {
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	return this->clone();
}

Matrix Matrix::translate(float x, float y, float z) {
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
	return this->clone();
}

Matrix Matrix::bank(float angle) { //same as roll
	float radians = degToRad(angle);
	float coseno = round(cos(radians) * 1000000) / 1000000;
	float seno = round(sin(radians) * 1000000) / 1000000;
	m[0][0] = coseno;
	m[0][1] = seno;
	m[1][0] = -seno;
	m[1][1] = coseno;
	return this->clone();
}

Matrix Matrix::pitch(float angle) {
	float radians = degToRad(angle);
	float coseno = round(cos(radians) * 1000000) / 1000000;
	float seno = round(sin(radians) * 1000000) / 1000000;
	m[1][1] = coseno;
	m[1][2] = seno;
	m[2][1] = -seno;
	m[2][2] = coseno;
	return this->clone();
}

Matrix Matrix::head(float angle) { //same as yaw
	float radians = degToRad(angle);
	float coseno = round(cos(radians) * 1000000) / 1000000;
	float seno = round(sin(radians) * 1000000) / 1000000;
	m[0][0] = coseno;
	m[0][2] = -seno;
	m[2][0] = seno;
	m[2][2] = coseno;
	return this->clone();
}

Matrix Matrix::rotate(Vector4 n, float angle) {
	float rad = degToRad(angle);
	n.normalize();
	float coseno = round(cos(rad) * 1000000) / 1000000;
	float seno = round(sin(rad) * 1000000) / 1000000;

	m[0][0] = n.x * n.x * (1 - coseno) + coseno;
	m[0][1] = n.x * n.y * (1 - coseno) + n.z * seno;
	m[0][2] = n.x * n.z * (1 - coseno) - n.y * seno;

	m[1][0] = n.x * n.y * (1 - coseno) - n.z * seno;
	m[1][1] = n.y * n.y * (1 - coseno) + coseno;
	m[1][2] = n.y * n.z * (1 - coseno) + n.x * seno;

	m[2][0] = n.x * n.z * (1 - coseno) + n.y * seno;
	m[2][1] = n.y * n.z * (1 - coseno) - n.x * seno;
	m[2][2] = n.z * n.z * (1 - coseno) + coseno;
	return this->clone();
}

Matrix Matrix::rotateAlter(Vector4 n, float angle) { //works but models start to look smaller with each rotation
	float pitchAngle, headAngle;
	pitchAngle = radToDeg(atan2(n.y,n.z));
	headAngle = radToDeg(atan2(n.x, n.z));
	return Matrix().pitch(-pitchAngle) * Matrix().head(-headAngle) * Matrix().bank(angle) * Matrix().head(headAngle) * Matrix().pitch(pitchAngle);
}

Matrix Matrix::lookAt(Vector4 camPosition, Vector4 lookPosition) { //not working yet
	Vector4 lookDirection = lookPosition - camPosition;
	float pitchAngle, headAngle;
	pitchAngle = radToDeg(asinf(lookDirection.y / hypotf(lookDirection.y, lookDirection.z)));
	headAngle = radToDeg(atan2f(lookDirection.x, lookDirection.z));
	std::cout << "pitch: " << pitchAngle << "\n";
	std::cout << "head: " << headAngle << "\n";
	return Matrix().pitch(pitchAngle) * Matrix().head(-headAngle) * Matrix().translate(-camPosition.x, -camPosition.y, -camPosition.z);
}

Matrix Matrix::operator*(Matrix rhs) {
	Matrix result(0.);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++) {
				result[i][j] += m[i][k] * rhs[k][j];
			}
		}
	}
	return result;
}

Matrix Matrix::clone() {
	Matrix ret(*this);
	return ret;
}

void Matrix::print(const Matrix& m, std::ostream& out) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out << m[i][j] << ", ";
		}
		out << '\n';
	}
}