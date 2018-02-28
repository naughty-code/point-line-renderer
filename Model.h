#pragma once
#include <iostream>
#include "Vector4.h"
#include "Matrix.h"
#include "OFFmodel.h"

struct Model
{
	Vector4* vertices;
	//Vector4 orientation[3];
	int **faces;
	int vertexCount;
	int faceCount;
	int *faceVertices;
	Model();
	Model(Model &rhs);
	Model(OFFmodel& m);
	Model(Model && rhs);
	Model(Model models[], int modelCount);
	Model transform(Matrix m);
	Model operator*(Matrix m);
	~Model();
};

