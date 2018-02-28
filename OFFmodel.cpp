#include "OFFmodel.h"

using namespace std;

OFFmodel::OFFmodel(const char * fileName) : fileName(fileName) {

	FILE *file = fopen(fileName, "r");
	char buff[4];
	bool ok = true;
	float x, y, z;
	if (file && fgets(buff, 4, file)) {
		
		fscanf(file, "%d %d %d", &vertexCount, &faceCount, &edgeCount);
		vertices = new Vector4[vertexCount]();

		for (int i = 0; i < vertexCount; i++) {
			fscanf(file, "%f %f %f", &x, &y, &z);
			vertices[i] = Vector4(x, y, z, 1);
		}
		faces = new int*[faceCount];
		faceVertices = new int[faceCount];
		for (int i = 0; i < faceCount; i++) {
			fscanf(file, "%d", &faceVertices[i]);
			faces[i] = new int[faceVertices[i]];
			for (int j = 0; j < faceVertices[i]; j++) {
				fscanf(file, "%d", &faces[i][j]);
			}
		}
	}
	else {
		cout << "error: file not found or not OFF format" << '\n';
	}
}

OFFmodel::~OFFmodel() {

	delete[] vertices;
	for(int i = 0; i < faceCount; i++){
		delete[] faces[i];
	}
	delete[] faceVertices;
	delete[] faces;
}