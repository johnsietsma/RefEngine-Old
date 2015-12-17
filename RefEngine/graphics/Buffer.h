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


/**
 * A buffer is a data blob that contains vertex data and a collection of vertex attributes that 
 *   define how the vertex dataa is layed out.
 * This class does not own any data, make sure the data passed in has approariate lifetime.
 */
struct Buffer
{
    // The default vertex attribute for vertex data that simply contains vec3 float data.
    static const std::vector<VertexAttribute> Vec3VertexAttribute;

    static const std::vector<VertexAttribute> Vec4VertexAttribute;

    // The default, empty index buffer
    static const std::vector<uint> EmptyIndex;

    // Create a buffer
    template<typename VertT>
    static Buffer Create(
        const std::vector<VertT>& vertices,
        const std::vector<VertexAttribute>& vertexAttributes = Buffer::Vec3VertexAttribute // Vert postions only by default
        )
    {
        // Assume each vert is stored on a single structure.
        uint numComponents = 1;
        uint vertexSize = sizeof(VertT);

        if (std::is_arithmetic<VertT>()) {
            // Calculate the buffer size using the vertex attributes.
            // Assume the buffer is made up individual compoents, for example floats for the position
            //   rather then being made up of structures that contain all the components such as FBXVertex.
            vertexSize = CalculateVertexSize(vertexAttributes);

            // Use the provided vertex attributes to calculate the number components in the vertex. 
            // A component is a single data element such as a float.
            numComponents = CalculateNumberOfComponents(vertexAttributes);
        }

        return Buffer{
            vertexSize,
            (uint)(vertices.size() / numComponents),
            vertices.data(),
            vertexAttributes.size(), vertexAttributes.data()
        };
    }

    const size_t vertexSize;  // The size of a vertex in bytes
    const uint numberOfVerts; // The number of verts in the buffer
    const void* verts;        // The vertex data

    const size_t numberOfVertexAttributes;
    const VertexAttribute* vertexAttributes;

    // Calculate the number of vertex components by adding up all components of each attribute.
    // For example a vertex with position and UV information may have 5 components, 3 for pos and 2 for uv.
    static int CalculateNumberOfComponents(const std::vector<VertexAttribute>& vertexAttributes);

    // Calculate the size of a vertex by adding up all it's components.
    static int CalculateVertexSize(const std::vector<VertexAttribute>& vertexAttributes);
};

}