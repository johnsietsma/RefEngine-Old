#include "Buffer.h"

#include <memory>

VertexBuffer::VertexBuffer(GLenum bufferType, VAOId vaoId, VBOId vboId, GLuint numberOfVerts)
: m_bufferType(bufferType)
, m_vaoId(vaoId)
, m_vboId(vboId)
, m_numberOfVerts(numberOfVerts) 
{
}

VertexBuffer::~VertexBuffer()
{
	// Cleanup
	glDeleteBuffers(1, &m_vboId.Value());
	glDeleteVertexArrays(1, &m_vaoId.Value());
}

// Creation must happen through the factory, keeps buffer ownership internal
Buffer* VertexBuffer::Create(GLuint bufferSize, GLuint numberOfVerts, const GLfloat verts[])
{
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return new VertexBuffer(GL_ARRAY_BUFFER, vertexArrayObject, vertexBufferId, numberOfVerts);
}

void VertexBuffer::Bind()
{
	glBindVertexArray(m_vaoId.Value());
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId.Value());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void VertexBuffer::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3 * m_numberOfVerts);
	glDisableVertexAttribArray(0);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}