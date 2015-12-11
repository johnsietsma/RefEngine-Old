#pragma once

#include "types.h"

#include <vector>

class Prims
{
public:
	Prims() = delete;

    static const std::vector<float> Quad_VerticesAndUVs;
    static const std::vector<float> Quad_Indices;

    static const std::vector<float> Triangle_Vertices;
    static const std::vector<float> Cube_Vertices;

    static const std::vector<uint> Cube_Indices;
	static const std::vector<float> Cube_Colors;
};
