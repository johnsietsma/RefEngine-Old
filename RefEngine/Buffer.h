#pragma once

#include "gl_core_4_1.h"
#include "OpenGlTypes.h"

#include <memory>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

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

	static Buffer* Create(size_t vertexSize, GLuint numberOfVerts, const GLfloat verts[]);

	// Create indexed array object
	static Buffer* Create(size_t vertexSize, GLuint numberOfVerts, const GLfloat verts[], GLuint numIndices, const GLushort indices[]);


	GLenum GetBufferType() const { return m_bufferType; }
	VBOId GetBufferId() { return m_vboId; }

	void Bind();
	void Draw();
	void Unbind();

private:
	// Takes ownership of the buffers
	VertexBuffer(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices);

	GLenum m_bufferType;
	VBOId m_vboId;
	VAOId m_vaoId;
	IBOId m_iboId;

	GLuint m_numberOfVerts;
	GLuint m_numberOfIndices;
};
