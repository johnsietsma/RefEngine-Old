#pragma once

#include "OpenGlTypes.h"
#include "types.h"

#include <memory>
#include <vector>

namespace reng {

struct VertexAttribute {
	size_t size;
	size_t offset;
	GLenum type;

	template<typename T>
	static VertexAttribute Create(size_t size, size_t offset, GLenum type) {
		return VertexAttribute{ size, offset, type };
	}
};


class Mesh {
public:
	VBOId vboId;
	VAOId vaoId;
	IBOId iboId;
	GLenum indexType;

	GLuint numberOfVerts;
	GLuint numberOfIndices;

	// Factory methods
	// Creation must happen through the factory, keeps buffer ownership internal

	// Create vertex only buffers
	template<typename VertT>
	static std::shared_ptr<Mesh> Create(const std::vector<VertT> verts) {

        // TODO: Get actual vert size from vertex attribute.

        return CreateMesh_Impl(
			sizeof(VertT), verts.size(), &(verts[0]), // vertex info
			0, 0, 0, nullptr // index info
			);
	}

    template<typename VertT>
    static std::shared_ptr<Mesh> Create(const std::vector<VertT> verts, const std::vector<VertexAttribute>& vertexAttributes) {
        return CreateMesh_Impl(
            sizeof(VertT), verts.size(), verts.data(), // vertex info
            0, 0, 0, nullptr, // index info
            vertexAttributes.size(), vertexAttributes.data()
            );
    }

	// Create indexed vertex buffers, each vertex has a position attribute
	template<typename VertT, typename IndexT>
	static std::shared_ptr<Mesh> Create(
		uint numberOfVerts, const VertT verts[],
		uint numberOfIndices, const IndexT indices[]
		) {
        return CreateMesh_Impl(
			sizeof(VertT), numberOfVerts, verts,
			sizeof(IndexT), reng::GLEnumValue<IndexT>::value, numberOfIndices, indices
			);
	}

	// Create indexed vertex buffers, each vertex has a number of attributes.
    template<typename VertT, typename IndexT>
    static std::shared_ptr<Mesh> Create(const std::vector<VertT>& vertices,
        const std::vector<IndexT>& indices )
    {
        return CreateMesh_Impl(
            sizeof(VertT), vertices.size(), vertices.data(),
            sizeof(IndexT), reng::GLEnumValue<IndexT>::value, indices.size(), &(indices[0])
            );
    }

    template<typename VertT, typename IndexT>
    static std::shared_ptr<Mesh> Create( const std::vector<VertT>& vertices,
        const std::vector<IndexT>& indices,
        const std::vector<VertexAttribute>& vertexAttributes )
    {
        return CreateMesh_Impl(
            sizeof(VertT), vertices.size(), vertices.data(),
            sizeof(IndexT), reng::GLEnumValue<IndexT>::value, indices.size(), &(indices[0]),
            vertexAttributes.size(), &(vertexAttributes[0])
            );
    }

    Mesh(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType);

private:
	static std::shared_ptr<Mesh> CreateMesh_Impl(
		size_t vertexSize, uint numberOfVerts, const void* verts,
		size_t indexSize, GLenum indexType, uint numberOfIndices, const void* indices,
		size_t numberOfVertexAttributes=0, const VertexAttribute vertexAttributes[]=nullptr
		);
};

}
