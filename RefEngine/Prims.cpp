#include "Prims.h"

const GLfloat Prims::Triangle_Vertices[] = {
	-1.f, -1.f, 0.f,
	1.f, -1.f, 0.f,
	0.f, 1.f, 0.f
};

const GLuint Prims::Triangle_NumberOfVerts = sizeof(Prims::Triangle_Vertices) / sizeof(GLfloat);

const GLfloat Prims::Cube_Vertices[] = {
	// front
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	-1.0, 1.0, -1.0,
};


const GLushort Prims::Cube_Indices[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	3, 2, 6,
	6, 7, 3,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// left
	4, 0, 3,
	3, 7, 4,
	// right
	1, 5, 6,
	6, 2, 1,
};

const GLfloat Prims::Cube_Colors[] = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
};

const GLuint Prims::Cube_NumberOfVerts = sizeof(Prims::Cube_Vertices) / sizeof(GLfloat);
const GLuint Prims::Cube_NumberOfIndices = sizeof(Prims::Cube_Indices) / sizeof(GLshort);
