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

	// Factory method
	static std::shared_ptr<Buffer> Create(GLuint bufferSize, GLuint numberOfVerts, const GLfloat verts[]);

	GLenum GetBufferType() const { return m_bufferType; }
	VBOId GetBufferId() { return m_vboId; }

	void Bind();
	void Draw();
	void Unbind();

private:
	// Takes ownership of the buffers
	VertexBuffer(GLenum bufferType, VAOId vaoId, VBOId vboId, GLuint numberOfVerts);

	GLenum m_bufferType;
	VBOId m_vboId;
	VAOId m_vaoId;
	GLuint m_numberOfVerts;
};
