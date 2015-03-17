#pragma once

#include "gl_core_4_1.h"
#include "OpenGlTypes.h"
#include "types.h"


#include <memory>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

struct VertexAttribute {
	size_t size;
	size_t offset;
	GLenum type;

	template<typename T>
	static VertexAttribute Create(size_t size, size_t offset, GLenum type) {
		return VertexAttribute { size, offset, type };
	}
};

class Buffer {
public:
	virtual GLenum GetBufferType() const = 0;
	virtual VBOId GetBufferId() = 0;

	virtual void Bind() = 0;
	virtual void Draw() = 0;
	virtual void Unbind() = 0;
};

class VertexBuffer : public Buffer {
public:
	~VertexBuffer();

	// Factory methods
	// Creation must happen through the factory, keeps buffer ownership internal

	// Create vertex only buffers
	template<typename VertT>
	static Buffer* Create(uint numberOfVerts, const VertT verts[]) {
		return Create(
			sizeof(VertT), numberOfVerts, verts, 
			0, 0, 0, nullptr, 
			0, nullptr
			);
	}

	// Create indexed vertex buffers, each vertex has a position attribute
	template<typename VertT, typename IndexT>
	static Buffer* Create(
		uint numberOfVerts, const VertT verts[], 
		uint numberOfIndices, const IndexT indices[]
		) {
		return Create(
			sizeof(VertT), numberOfVerts, verts, 
            sizeof(IndexT), reng::GLEnumValue<IndexT>::value, numberOfIndices, indices,
            0, nullptr
        );
	}

	// Create indexed vertex buffers, each vertex has a number of attributes.
	template<typename VertT, typename IndexT>
	static Buffer* Create(
		uint numberOfVerts, const VertT verts[], 
		uint numberOfIndices, const IndexT indices[], 
		size_t numberOfVertexAttributes, const VertexAttribute vertexAttributes[]
		) {
		return Create(
			sizeof(VertT), numberOfVerts, verts, 
            sizeof(IndexT), reng::GLEnumValue<IndexT>::value, numberOfIndices, indices,
			numberOfVertexAttributes, vertexAttributes 
        );
	}


	GLenum GetBufferType() const { return m_bufferType; }
	VBOId GetBufferId() { return m_vboId; }

	void Bind();
	void Draw();
	void Unbind();

private:
	// Takes ownership of the buffers
	VertexBuffer(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType);

	static Buffer* Create(
		size_t vertexSize, uint numberOfVerts, const void* verts, 
		size_t indexSize, GLenum indexType, uint numberOfIndices, const void* indices, 
		size_t numberOfVertexAttributes, const  VertexAttribute vertexAttributes[]
		);

	GLenum m_bufferType;
	VBOId m_vboId;
	VAOId m_vaoId;
	IBOId m_iboId;
	GLenum m_indexType;

	GLuint m_numberOfVerts;
	GLuint m_numberOfIndices;
};
