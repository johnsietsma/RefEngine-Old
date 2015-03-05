#include "Buffer.h"

#include <memory>

#include "pow2assert.h"

VertexBuffer::VertexBuffer(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices) :
m_vaoId(vaoId),
m_vboId(vboId),
m_iboId(iboId),
m_numberOfVerts(numberOfVerts) ,
m_numberOfIndices(numberOfIndices)
{
}

VertexBuffer::~VertexBuffer()
{
	// Cleanup
	glDeleteBuffers(1, &m_vboId.Value());
	glDeleteVertexArrays(1, &m_vaoId.Value());
}

// Array object creator
Buffer* VertexBuffer::Create(size_t vertexSize, GLuint numberOfVerts, const GLfloat verts[])
{
	return Create(vertexSize, numberOfVerts, verts, 0, nullptr);
}

// Indexed array creator
Buffer* VertexBuffer::Create(size_t vertexSize, GLuint numberOfVerts, const GLfloat verts[], GLuint numberOfIndices, const GLushort indices[])
{
	POW2_ASSERT(vertexSize != 0 || vertexSize != (size_t)-1);
	POW2_ASSERT(numberOfVerts != 0 || numberOfVerts != (GLuint)-1);
	POW2_ASSERT(verts != nullptr);
	POW2_ASSERT(numberOfIndices<=0 || indices!= nullptr);

	VAOId vertexArrayObjectId = VAOId_Invalid;
	VBOId vertexBufferId = VBOId_Invalid;
	IBOId indexBufferObjectId = IBOId_Invalid;

	glGenVertexArrays(1, &vertexArrayObjectId.Get());
	glGenBuffers(1, &vertexBufferId.Get());

	glBindVertexArray(vertexArrayObjectId.Value());
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId.Value());
	glBufferData(GL_ARRAY_BUFFER, numberOfVerts*vertexSize, verts, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (numberOfIndices > 0) {
		glGenBuffers(1, &indexBufferObjectId.Get());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectId.Value());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices*sizeof(GLushort), indices, GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	return new VertexBuffer(indexBufferObjectId, vertexArrayObjectId, vertexBufferId, numberOfVerts, numberOfIndices);
}


void VertexBuffer::Bind()
{
	glBindVertexArray(m_vaoId.Value());

	if (m_iboId == IBOId_Invalid) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId.Value());
	}
}

void VertexBuffer::Draw()
{
	if (m_iboId == IBOId_Invalid) {
		glDrawArrays(GL_TRIANGLES, 0, 3 * m_numberOfVerts);
	}
	else {
		glDrawElements(GL_TRIANGLES, m_numberOfIndices, GL_UNSIGNED_SHORT, 0);
	}
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}