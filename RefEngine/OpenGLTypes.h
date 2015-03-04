#pragma once

#include "StronglyTyped.h"
#include "gl_core_4_4.h"
#include "Prims.h"

#include <memory>

struct VBOType {};
typedef StronglyTyped<GLuint, VBOType> VBOId;

struct ProgramType {};
typedef StronglyTyped<GLuint, ProgramType> ProgramId;

struct UniformLocationType {};
typedef StronglyTyped<GLuint, UniformLocationType> UniformLocationId;

class Buffer {
public:
	virtual GLenum GetBufferType() const = 0;
	virtual VBOId GetBufferId() = 0;

    virtual void Bind() = 0;
    virtual void Draw() = 0;
};

class VBO : public Buffer {
public:
	VBO(GLenum bufferType, VBOId vboId, GLuint numberOfVerts) : m_bufferType(bufferType), m_vboId(vboId), m_numberOfVerts(numberOfVerts) {}

	static std::shared_ptr<Buffer> Create(GLuint bufferSize, GLuint numberOfVerts, const GLfloat verts[]);
    static void Destroy(VBOId);

	GLenum GetBufferType() const { return m_bufferType; }
	VBOId GetBufferId() { return m_vboId; }

    void Bind();
    void Draw();

private:
	GLenum m_bufferType;
	VBOId m_vboId;
	GLuint m_numberOfVerts;
};
