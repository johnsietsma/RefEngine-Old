#include "graphics/Primitive.h"

#include <algorithm>

using namespace reng;

const std::vector<VertexAttribute> Primitive::Vec3VertexAttribute {
    VertexAttribute{ 0,  sizeof(float), GL_FLOAT, 3 }
};

const std::vector<VertexAttribute> Primitive::Vec4VertexAttribute{
    VertexAttribute{ 0, sizeof(float), GL_FLOAT, 4 }
};


const std::vector<uint> Primitive::EmptyIndex;

void Primitive::UpdateBuffer(const Buffer& buffer)
{
    GLenum usage = isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    glBindBuffer(GL_ARRAY_BUFFER, vboId.Value());
    glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, usage);
}
