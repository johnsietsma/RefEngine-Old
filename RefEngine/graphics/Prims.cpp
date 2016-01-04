#include "Prims.h"

const std::array<float,20> Prims::Quad_VerticesAndUVs {
    // Vert, UV
    -1.f, -1.f, 0.f,    0.f, 0.f,
    -1.f,  1.f, 0.f,    0.f, 1.f,
     1.f,  1.f, 0.f,    1.f, 1.f,
     1.f, -1.f, 0.f,    1.f, 0.f,
};

const std::array<uint,6> Prims::Quad_Indices{
    0, 1, 2,
    0, 2, 3
};

const  std::array<float,9> Prims::Triangle_Vertices {
	-1.f, -1.f, 0.f,
	1.f, -1.f, 0.f,
	0.f, 1.f, 0.f
};

const std::array<float,24> Prims::Cube_Vertices {
	// front
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	// back
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
};

const std::array<uint,36> Prims::Cube_Indices {
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

const std::array<float,32> Prims::Cube_Colors {
	// front colors
	1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
	// back colors
    1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
};
