#include "tgaimage.h"
#include "OFFmodel.h"
#include "Model.h"
#include "Matrix.h"
#include <cmath>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void print(const Model&, std::ostream&);
void print(const Matrix& m, std::ostream& out);
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color);

int main(int argc, char** argv) {
	char garbage;
	int width = 1000;
	int height = 1000;
	int centerX = width / 2;
	int centerY = height / 2;
	TGAImage image(width, height, TGAImage::RGB); //initializing image to write
	// extracted OFF models from files
	OFFmodel offCochino("cochino.off");
	OFFmodel offCamello("camello.off");
	OFFmodel offDilo("dilo.off");
	OFFmodel offDino("dinosaurio.off");
	OFFmodel offVaca("vaca.off");

	// Models stored in a structure for transformations
	Model cochino = offCochino;
	Model camello = offCamello;
	Model dilo = offDilo;
	Model dino = offDino;
	Model vaca = offVaca;
	//
	Model tcochino = cochino * (Matrix(1.5) * Matrix().bank(180) * Matrix().head(20) * Matrix().pitch(-10) * Matrix().translate(-1,0,0.5));
	Model tcamello = camello * (Matrix().head(-45) * Matrix().translate(1, .1, 1));
	Model tdilo = dilo * (Matrix(2) * Matrix().bank(180) * Matrix().head(180) * Matrix().translate(-0.3,0,1));
	Model tdino = dino * (Matrix(1.5) * Matrix().pitch(-5) * Matrix().head(45) *  Matrix().translate(-1, .1, -0.5));
	Model tvaca = vaca * (Matrix(0.8) * Matrix().head(30) * Matrix().translate(0.7, .1, -0.5));

	// World model, all models in a single structure

	Model models[5] = { tcochino, tcamello, tdilo, tdino, tvaca };
	Model world(models, 5);

	//Camera transforms
	//Matrix().rotateAlter(Vector4(1, 1, 1), 45) * Matrix().translate(0,0,0.5)
	//
	Model camSpace = world * (Matrix().lookAt(Vector4(1, 0, 0), Vector4()));

	Model screenSpace = camSpace * (Matrix().scale(1, -1, 1));

	Model target = screenSpace;
	float d = 1; //distance of the plane from the origin(center of projection)
	    //point rendering
		for (int j = 0; j < target.vertexCount; j++) { //for every vertex in model (world)
			float x = target.vertices[j].x;
			float y = target.vertices[j].y;
			float z = target.vertices[j].z;
			//frontal clipping plane
			if (z < d) continue;
			//perspective projection
			x = d * x / z;
			y = d * y / z;
			//screen projection
			x = (x + 1.) * width / 2.;
			y = (y + 1.) * height / 2.;
			image.set(x, y, white);
		}

	/*
	//triangle mesh rendering
	for (int i = 0; i < camSpace.faceCount; i++) {
		for (int j = 0; j < camSpace.faceVertices[i]; j++) {
			Vector4 p0 = camSpace.vertices[camSpace.faces[i][j]];
			Vector4 p1 = camSpace.vertices[camSpace.faces[i][(j + 1) % camSpace.faceVertices[i]]];
			float x0 = (p0.x / p0.z + 1.) * width / 2.;
			float y0 = (p0.y / p0.z + 1.) * width / 2.;
			float x1 = (p1.x / p1.z + 1.) * height / 2.;
			float y1 = (p1.y / p1.z + 1.) * height / 2.;
			line(x0, y0, x1, y1, image, white);
		}
	}
	*/
	//image.flip_vertically();
	image.write_tga_file("output.tga");
	
	cin >> garbage;
	return 0;
}

void print(const Model& m, std::ostream& out) {
	for (int i = 0; i < m.vertexCount; i++)
	{
		out << "x: " << m.vertices[i].x << ", y:" << m.vertices[i].y << ", z:" << m.vertices[i].z << ", w:" << m.vertices[i].w << "\n";
	}
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (std::abs(x0 - x1)<std::abs(y0 - y1)) { // if the line is steep, we transpose the image 
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0>x1) { // make it left-to-right 
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	for (int x = x0; x <= x1; x++) {
		float t = (x - x0) / (float)(x1 - x0);
		int y = y0*(1. - t) + y1*t;
		if (steep) {
			image.set(y, x, color); // if transposed, de-transpose 
		}
		else {
			image.set(x, y, color);
		}
	}
}