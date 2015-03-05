#pragma once

#include "gl_core_4_4.h"

class Prims
{
public:
	Prims() = delete;

	static const GLfloat Triangle_Vertices[];
	static const GLuint Triangle_NumberOfVerts;

	static const GLfloat Cube_Vertices[];
	static const GLushort Cube_Indices[];
	static const GLfloat Cube_Colors[];
	static const GLuint Cube_NumberOfVerts;
	static const GLuint Cube_NumberOfIndices;
};

