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
};

class VBO : public Buffer {
public:
	VBO(GLenum bufferType, VAOId vaoId, VBOId vboId, GLuint numberOfVerts) : m_bufferType(bufferType), m_vaoId(vaoId), m_vboId(vboId), m_numberOfVerts(numberOfVerts) {}

	static std::shared_ptr<Buffer> Create(GLuint bufferSize, GLuint numberOfVerts, const GLfloat verts[]);
	static void Destroy(VAOId vaoId, VBOId vboId);

	GLenum GetBufferType() const { return m_bufferType; }
	VBOId GetBufferId() { return m_vboId; }

	void Bind();
	void Draw();

private:
	GLenum m_bufferType;
	VBOId m_vboId;
	VAOId m_vaoId;
	GLuint m_numberOfVerts;
};
