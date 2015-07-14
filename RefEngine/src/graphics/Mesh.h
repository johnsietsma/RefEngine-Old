#pragma once

#include "OpenGlTypes.h"
#include "types.h"

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
	static Mesh* Create(uint numberOfVerts, const VertT verts[]) {
		return CreateMesh(
			sizeof(VertT), numberOfVerts, verts,
			0, 0, 0, nullptr,
			0, nullptr
			);
	}

	// Create indexed vertex buffers, each vertex has a position attribute
	template<typename VertT, typename IndexT>
	static Mesh* Create(
		uint numberOfVerts, const VertT verts[],
		uint numberOfIndices, const IndexT indices[]
		) {
		return CreateMesh(
			sizeof(VertT), numberOfVerts, verts,
			sizeof(IndexT), reng::GLEnumValue<IndexT>::value, numberOfIndices, indices,
			0, nullptr
			);
	}

	// Create indexed vertex buffers, each vertex has a number of attributes.
	template<typename VertT, typename IndexT>
	static Mesh* Create(
		uint numberOfVerts, const VertT verts[],
		uint numberOfIndices, const IndexT indices[],
		size_t numberOfVertexAttributes, const VertexAttribute vertexAttributes[]
		) {
		return CreateMesh(
			sizeof(VertT), numberOfVerts, verts,
			sizeof(IndexT), reng::GLEnumValue<IndexT>::value, numberOfIndices, indices,
			numberOfVertexAttributes, vertexAttributes
			);
	}

private:
	Mesh(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType);

	static Mesh* CreateMesh(
		size_t vertexSize, uint numberOfVerts, const void* verts,
		size_t indexSize, GLenum indexType, uint numberOfIndices, const void* indices,
		size_t numberOfVertexAttributes, const VertexAttribute vertexAttributes[]
		);
};

}
