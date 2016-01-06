#pragma once

#include "OpenGLTypes.h"
#include "types.h"

#include <array>
#include <type_traits>
#include <vector>

namespace reng {

// Based loosely on https://github.com/KhronosGroup/glTF/

// Nothing here owns data and is copyable.

// A buffer is simply a pointer some data and its size.
struct Buffer 
{
    const void* data; // no ownership implied, may be null
    size_t size; // byte size

    Buffer() :
        data(nullptr),
        size(0)
    {}

    Buffer(const void* a_data, size_t a_size) :
        data(a_data),
        size(a_size)
    {}
};

// An accessor is used to access typed data in a buffer.
struct BufferAccessor
{
    static const BufferAccessor Empty;

    BufferAccessor() :
        byteOffset(0),
        byteStride(0),
        type(0),
        count(0)
    {}

    // Create a new BufferAccessor without a Buffer bound to it. Useful to describe data before it's available.
    BufferAccessor(size_t a_byteOffset, size_t a_byteStride, GLenum a_type, int a_count) :
        byteOffset(a_byteOffset),
        byteStride(a_byteStride),
        type(a_type),
        count(a_count)
    {}

    BufferAccessor(const Buffer& a_buffer, size_t a_byteOffset, size_t a_byteStride, GLenum a_type, int a_count) :
        buffer(a_buffer),
        byteOffset(a_byteOffset),
        byteStride(a_byteStride),
        type(a_type),
        count(a_count)
    {}

    // A helpful constructor that make a BufferAccessor from an std::array.
    template<typename T, size_t N>
    BufferAccessor(const std::array<T, N>& arrayBuffer, int elementsPerComponent) :
        BufferAccessor(
            Buffer(arrayBuffer.data(), arrayBuffer.size() * sizeof(T)), 
            0, // Assume no offset
            sizeof(T) * elementsPerComponent, // The stride is the number of elements * the size of each element
            GLEnum<T>::value, // Lookup the GLenum equiv of the type held in the std::array
            arrayBuffer.size()/elementsPerComponent // Calc the number of components
            )
        {}

    // A helpful constructor that make a BufferAccessor from an std::vector.
    template<typename T>
    BufferAccessor(const std::vector<T>& vectorBuffer, int elementsPerComponent) :
        BufferAccessor(
            Buffer(vectorBuffer.data(), vectorBuffer.size() * sizeof(T)),
            0,
            sizeof(T) * elementsPerComponent,
            GLEnum<T>::value,
            vectorBuffer.size() / elementsPerComponent
        )
    {}

    Buffer buffer;
    size_t byteOffset;  // Offset into the buffer
    size_t byteStride;  // Stride of the component in the buffer, eg VEC3 may have a stride of 4*3=12 bytes
    GLenum type;        // The type of data stored in the buffer, eg GL_FLOAT.
    int count; // num of attributes, not bytes
};

// Defines a vertex attribute such as position or texcoord. It's a simple wrapper around a BufferAccessor.
struct VertexAttribute 
{
    BufferAccessor accessor;

    template<class T>
    static VertexAttribute Create(size_t offset, size_t numComponents)
    {
        return VertexAttribute(offset, sizeof(T), GLEnum<T>::value, numComponents);
    }

    VertexAttribute(size_t offset, size_t stride, GLenum type, size_t numComponents) :
        accessor( offset, stride, type, numComponents )
    {}
};


// A Primitive wraps a VBO, its associated buffer and vertex attributes.
struct Primitive
{
    static const std::vector<VertexAttribute> Vec3VertexAttribute;
    static const std::vector<VertexAttribute> Vec4VertexAttribute;
    static const std::vector<VertexAttribute> VertexPositionAndNormalsAttribute;

    // The default, empty index buffer
    static const std::vector<uint> EmptyIndex;

    Primitive(
        const BufferAccessor& a_accessor,
        const std::vector<VertexAttribute>& a_vertexAttributes,
        bool a_isStatic = true
        ) :
        vboId(VBOId_Invalid),
        accessor(a_accessor),
        vertexAttributes(a_vertexAttributes),
        isStatic(a_isStatic)
    {}

    // Reupload VBO data.
    void UpdateBuffer();

    VBOId vboId;
    BufferAccessor accessor;
    const std::vector<VertexAttribute> vertexAttributes;
    const bool isStatic;
};

}