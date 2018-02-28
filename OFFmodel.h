#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Vector4.h"
using namespace std;

struct OFFmodel {
	OFFmodel(const char * fileName);
	string fileName;
	int vertexCount;
	int faceCount;
	int edgeCount;
	int *faceVertices;
	Vector4 *vertices;
	int **faces;
	int **edges;
	~OFFmodel();
};