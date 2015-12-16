#pragma once

#include "OpenGLTypes.h"
#include "types.h"

#include <type_traits>
#include <vector>

namespace reng {


struct VertexAttribute {
    size_t numComponents;
    size_t componentSize; // in bytes
    size_t offset; // offset within a struct this attribute is within
    GLenum type;

    template<class T>
    static VertexAttribute Create(size_t numComponents, size_t offset) {
        return VertexAttribute{ numComponents, sizeof(T), offset, GLEnumValue<T>::value };
    }
};


struct Buffer
{
    // The default vertex attribute for vertex data that simply contains vec3 position data.
    static const std::vector<VertexAttribute> PositionVertexAttribute;
    static const std::vector<uint> EmptyIndex;

    Buffer() = default;
    
    template<typename VertT>
    static Buffer Create(
        const std::vector<VertT>& vertices,
        const std::vector<uint>& indices = Buffer::EmptyIndex, // No indices by default
        const std::vector<VertexAttribute>& vertexAttributes = Buffer::PositionVertexAttribute // Vert postions only by default
        )
    {
        // Use the provided vertex attributes to calculate the number components in the vertex. 
        // A component is a single data element such as a float.
        uint numComponents = CalculateNumberOfComponents(vertexAttributes);

        uint vertexSize = sizeof(VertT);

        if (std::is_arithmetic<VertT>()) {
            // Calculate the buffer size using the vertex attributes.
            // Assume the buffer is made up individual compoents, for example floats for the position
            //   rather then being made up of structures that contain all the components such as FBXVertex.
            vertexSize = CalculateVertexSize(vertexAttributes);
        }

        return CreateBuffer_Impl(vertices, indices, vertexAttributes, numComponents, vertexSize);
    }

    const size_t vertexSize;
    const uint numberOfVerts;
    const void* verts;

    const GLenum indexType;
    const uint numberOfIndices;
    const void* indices;

    const size_t numberOfVertexAttributes;
    const VertexAttribute* vertexAttributes;

    // Calculate the number of vertex components by adding up all components of each attribute.
    // For example a vertex with position and UV information may have 5 components, 3 for pos and 2 for uv.
    static int CalculateNumberOfComponents(const std::vector<VertexAttribute>& vertexAttributes);

    // Calculate the size of a vertex by adding up all it's components.
    static int CalculateVertexSize(const std::vector<VertexAttribute>& vertexAttributes);

private:
    template<typename VertT>
    static Buffer CreateBuffer_Impl(
        const std::vector<VertT>& vertices,
        const std::vector<uint>& indices,
        const std::vector<VertexAttribute>& vertexAttributes,
        uint numComponents, 
        uint vertexSize
        )
    {
        return Buffer{
            vertexSize,                         // The size of a vertex in bytes
            vertices.size() / numComponents,    // The number of vertices
            vertices.data(),                    // The vertex data
            GL_UNSIGNED_INT, indices.size(), indices.data(),
            vertexAttributes.size(), vertexAttributes.data()
        };
    }
};

}