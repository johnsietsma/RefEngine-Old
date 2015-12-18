#include "graphics/VertexBufferInfo.h"

#include <algorithm>

using namespace reng;

const std::vector<VertexAttribute> VertexBufferInfo::Vec3VertexAttribute{
    VertexAttribute{ 3, sizeof(float), 0, GL_FLOAT }
};

const std::vector<VertexAttribute> VertexBufferInfo::Vec4VertexAttribute{
    VertexAttribute{ 4, sizeof(float), 0, GL_FLOAT }
};


const std::vector<uint> VertexBufferInfo::EmptyIndex;


int VertexBufferInfo::CalculateNumberOfComponents(const std::vector<VertexAttribute>& vertexAttributes) {
    int numComponents = 0;
    std::for_each(vertexAttributes.begin(), vertexAttributes.end(), [&numComponents](const VertexAttribute& va) { numComponents += va.numComponents; });
    return numComponents;
}

int VertexBufferInfo::CalculateVertexSize(const std::vector<VertexAttribute>& vertexAttributes) {
    int vertexSize = 0;
    std::for_each(vertexAttributes.begin(), vertexAttributes.end(), [&vertexSize](const VertexAttribute& va) { vertexSize += va.componentSize*va.numComponents; });
    return vertexSize;
}
