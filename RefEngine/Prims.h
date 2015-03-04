#pragma once

#include "gl_core_4_4.h"

class Prims
{
public:
	static const GLfloat Triangle[];
	static const size_t TriangleSize;

	static const GLfloat Cube_Vertices[];
	static const size_t Cube_BufferSize;
	static const size_t Cube_NumberOfVerts;

	static const GLfloat CubeColors[];

private:
	Prims(); // Abstract class
};

