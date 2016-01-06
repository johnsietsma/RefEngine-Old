#include "graphics/Primitive.h"

#include <algorithm>

using namespace reng;

const BufferAccessor BufferAccessor::Empty;


const std::vector<VertexAttribute> Primitive::Vec3VertexAttribute {
    VertexAttribute{ 0,  sizeof(float), GL_FLOAT, 3 }
};

const std::vector<VertexAttribute> Primitive::Vec4VertexAttribute {
    VertexAttribute{ 0, sizeof(float), GL_FLOAT, 4 }
};

const std::vector<VertexAttribute> Primitive::VertexPositionAndNormalsAttribute {
    VertexAttribute{ 0, sizeof(float), GL_FLOAT, 3 },
    VertexAttribute{ 0, sizeof(float), GL_FLOAT, 3 }
};

const std::vector<uint> Primitive::EmptyIndex;

void Primitive::UpdateBuffer()
{
    GLenum usage = isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
    auto& buffer = accessor.buffer;
    glBindBuffer(GL_ARRAY_BUFFER, vboId.Value());
    glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, usage);
}
