#include "Model.h"

Model::Model() {
	vertexCount = 0;
	vertices = nullptr;
	faces = nullptr;
	faceVertices = nullptr;
	//orientation[0].x = 1;
	//orientation[1].y = 1;
	//orientation[3].z = 1;
}

Model::Model(Model &rhs) {
		vertexCount = rhs.vertexCount;
		faceCount = rhs.faceCount;
		vertices = new Vector4[vertexCount];
		for (int i = 0; i < vertexCount; i++)
		{
			vertices[i] = rhs.vertices[i];
		}
		faces = new int*[faceCount];
		faceVertices = new int[faceCount];
		for (int i = 0; i < rhs.faceCount; i++) {
			faceVertices[i] = rhs.faceVertices[i];
			faces[i] = new int[faceVertices[i]];
			for (int j = 0; j < rhs.faceVertices[i]; j++) {
				faces[i][j] = rhs.faces[i][j];
			}
		}
}

Model::Model(OFFmodel& m)
{
	vertexCount = m.vertexCount;
	faceCount = m.faceCount;
	vertices = new Vector4[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		vertices[i] = m.vertices[i];
	}
	faces = new int*[faceCount];
	faceVertices = new int[faceCount];
	for (int i = 0; i < m.faceCount; i++) {
		faceVertices[i] = m.faceVertices[i];
		faces[i] = new int[faceVertices[i]];
		for (int j = 0; j < m.faceVertices[i]; j++) {
			faces[i][j] = m.faces[i][j];
		}
	}
}

Model::Model(Model&& rhs) {
	vertexCount = rhs.vertexCount;
	faceCount = rhs.faceCount;

	vertices = rhs.vertices;
	faceVertices = rhs.faceVertices;
	faces = rhs.faces;
	
	rhs.vertices = nullptr;
	rhs.faces = nullptr;
	rhs.faceVertices = nullptr;
}

Model::Model(Model models[], int modelCount) {
	vertexCount = 0;
	faceCount = 0;
	vertices = nullptr;
	faces = nullptr;
	if (modelCount == 0) {
		std::cout << "Error: called Model with model list constructor with model Count 0" << std::endl;
		return;
	}
	for (int i = 0; i < modelCount; i++) { 
		vertexCount += models[i].vertexCount;
		faceCount += models[i].faceCount;
	}

	vertices = new Vector4[vertexCount];
	faces = new int*[faceCount];
	faceVertices = new int[faceCount];

	int addedVertices = 0;
	int addedFaces = 0;
	for (int i = 0; i < modelCount; i++) {
		for (int j = 0; j < models[i].vertexCount; j++) vertices[addedVertices + j] = models[i].vertices[j];
		for (int j = 0; j < models[i].faceCount; j++) {
			faceVertices[addedFaces + j] = models[i].faceVertices[j];
			faces[addedFaces + j] = new int[models[i].faceVertices[j]];
			for (int k = 0; k < models[i].faceVertices[j]; k++) faces[addedFaces + j][k] = models[i].faces[j][k] + addedVertices;
		}
		addedVertices += models[i].vertexCount;
		addedFaces += models[i].faceCount;
	}
}

Model Model::transform(Matrix m) {
	Model newModel = *this;
	for (int i = 0; i < vertexCount; i++) {
		newModel.vertices[i] = newModel.vertices[i] * m;
	}
	return newModel;
}

Model Model::operator*(Matrix m) {
	Model r = *this;
	for (int i = 0; i < r.vertexCount; i++)
	{
		r.vertices[i] = r.vertices[i] * m;
	}
	return r;
}

Model::~Model()
{
	if(vertices) delete[] vertices;
	if (faces) {
		for (int i = 0; i < faceCount; i++)
		{
			if(faces[i]) delete[] faces[i];
		}
		delete[] faces;
	}
	if(faceVertices) delete[] faceVertices;
}
