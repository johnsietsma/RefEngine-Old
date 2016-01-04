#pragma once

#include "types.h"

#include <array>

class Prims
{
public:
	Prims() = delete;

    static const std::array<float,20> Quad_VerticesAndUVs;
    static const std::array<uint,6> Quad_Indices;

    static const std::array<float,9> Triangle_Vertices;
    static const std::array<float,24> Cube_Vertices;

    static const std::array<uint,36> Cube_Indices;
	static const std::array<float,32> Cube_Colors;
};
