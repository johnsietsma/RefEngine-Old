#include "Buffer.h"

#include <algorithm>

using namespace reng;

const std::vector<VertexAttribute> Buffer::Vec3VertexAttribute {
    VertexAttribute{ 3, sizeof(float), 0, GL_FLOAT }
};

const std::vector<VertexAttribute> Buffer::Vec4VertexAttribute{
    VertexAttribute{ 4, sizeof(float), 0, GL_FLOAT }
};


const std::vector<uint> Buffer::EmptyIndex;


int Buffer::CalculateNumberOfComponents(const std::vector<VertexAttribute>& vertexAttributes) {
    int numComponents = 0;
    std::for_each(vertexAttributes.begin(), vertexAttributes.end(), [&numComponents](const VertexAttribute& va) { numComponents += va.numComponents; });
    return numComponents;
}

int Buffer::CalculateVertexSize(const std::vector<VertexAttribute>& vertexAttributes) {
    int vertexSize = 0;
    std::for_each(vertexAttributes.begin(), vertexAttributes.end(), [&vertexSize](const VertexAttribute& va) { vertexSize += va.componentSize*va.numComponents; });
    return vertexSize;
}
