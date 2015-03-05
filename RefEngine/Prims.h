#pragma once

#include "gl_core_4_4.h"
#include "types.h"
class Prims
{
public:
	Prims() = delete;

	static const float Triangle_Vertices[];
	static const uint Triangle_NumberOfVerts;

	static const float Cube_Vertices[];
	static const uint Cube_Indices[];
	static const float Cube_Colors[];
	static const uint Cube_NumberOfVerts;
	static const uint Cube_NumberOfIndices;
};

