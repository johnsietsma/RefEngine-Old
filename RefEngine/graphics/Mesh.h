#pragma once

#include "OpenGlTypes.h"
#include "types.h"

#include <algorithm>
#include <memory>
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

static const std::vector<uint> EmptyIndex;


class Mesh {
public:
	VBOId vboId;
	VAOId vaoId;
	IBOId iboId;
	GLenum indexType;
    GLuint numberOfVerts;
    GLuint numberOfIndices;

    Mesh(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType);

    /**
     * Create a mesh from vertex data.
     * Optionally pass in index data to create an indexed mesh.
     * Optionall pass in vertex attributes to use more then just vertex position data.
     */
    template<typename VertT>
    static std::shared_ptr<Mesh> Create( 
        const std::vector<VertT>& vertices,
        const std::vector<uint>& indices = EmptyIndex, // No indices by default
        const std::vector<VertexAttribute>& vertexAttributes = PositionVertexAttribute // Vert postions only by default
    )
    {
        // Use the provided vertex attributes to calculate the number components in the vertex. 
        // A component is a single data element such as a float.
        uint numComponents = CalculateNumberOfComponents(vertexAttributes);
        uint vertexSize = CalculateVertexSize(vertexAttributes);
        return CreateMesh_Impl(
            vertexSize,                         // The size of a vertex in bytes
            vertices.size() / numComponents,    // The number of vertices
            vertices.data(),                    // The vertex data
            GL_UNSIGNED_INT, indices.size(), indices.data(),
            vertexAttributes.size(), vertexAttributes.data()
            );
    }

private:
	static std::shared_ptr<Mesh> CreateMesh_Impl(
		size_t vertexSize, uint numberOfVerts, const void* verts,
        GLenum indexType, uint numberOfIndices, const void* indices,
		size_t numberOfVertexAttributes, const VertexAttribute vertexAttributes[]
		);

    // Calculate the number of vertex components by adding up all components of each attribute.
    // For example a vertex with position and UV information may have 5 components, 3 for pos and 2 for uv.
    static int CalculateNumberOfComponents(const std::vector<VertexAttribute>& vertexAttributes);

    // Calculate the size of a vertex by adding up all it's components.
    static int CalculateVertexSize(const std::vector<VertexAttribute>& vertexAttributes);

    // The default vertex attribute for vertex data that simply contains vec3 position data.
    static const std::vector<VertexAttribute> PositionVertexAttribute;
};

}
