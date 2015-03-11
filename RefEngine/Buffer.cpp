#include "Buffer.h"

#include <memory>

#include "pow2assert.h"

VertexBuffer::VertexBuffer(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType) :
m_vboId(vboId),
m_vaoId(vaoId),
m_iboId(iboId),
m_indexType(indexType),
m_numberOfVerts(numberOfVerts),
m_numberOfIndices(numberOfIndices)
{
}

VertexBuffer::~VertexBuffer()
{
	// Cleanup
	glDeleteBuffers(1, &m_vboId.Value());
	glDeleteVertexArrays(1, &m_vaoId.Value());
}

// Element array creator
Buffer* VertexBuffer::Create(
	size_t vertexSize, uint numberOfVerts, const void* verts, 
	size_t indexSize, GLenum indexType, uint numberOfIndices, const void* indices, 
	size_t numberOfVertexAttributes, const VertexAttribute vertexAttributes[]
	)
{
	POW2_ASSERT(vertexSize > 0);
	POW2_ASSERT(numberOfVerts != 0 || numberOfVerts != (GLuint)-1);
	POW2_ASSERT(verts != nullptr);

	POW2_ASSERT((indexSize<=0&&indices==nullptr) || indexSize > 0);
	POW2_ASSERT(indexType != (GLenum)-1);
	POW2_ASSERT((((int)numberOfIndices) == -1 || numberOfIndices == 0) || indices != nullptr);
 	POW2_ASSERT(indexType >= 0);

	VAOId vertexArrayObjectId = VAOId_Invalid;
	VBOId vertexBufferId = VBOId_Invalid;
	IBOId indexBufferObjectId = IBOId_Invalid;

	glGenVertexArrays(1, &vertexArrayObjectId.Get());
	glGenBuffers(1, &vertexBufferId.Get());

	glBindVertexArray(vertexArrayObjectId.Value());
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId.Value());
	glBufferData(GL_ARRAY_BUFFER, numberOfVerts*vertexSize, verts, GL_STATIC_DRAW);

	if (numberOfIndices > 0) {
		glGenBuffers(1, &indexBufferObjectId.Get());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectId.Value());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices*indexSize, indices, GL_STATIC_DRAW);
	}


	if (numberOfVertexAttributes == 0) {
		// Assume a float position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	else {
		for (uint i = 0; i < numberOfVertexAttributes; i++) {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, vertexAttributes[i].size, vertexAttributes[i].type, GL_FALSE, vertexSize, ((char*)0) + vertexAttributes[i].offset);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return new VertexBuffer(indexBufferObjectId, vertexArrayObjectId, vertexBufferId, numberOfVerts, numberOfIndices, indexType);
}


void VertexBuffer::Bind()
{
	glBindVertexArray(m_vaoId.Value());

	if (m_iboId == IBOId_Invalid) {
		glBindBuffer(GL_ARRAY_BUFFER, m_vboId.Value());
	}
	else {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId.Value());
	}
}

void VertexBuffer::Draw()
{
	if (m_iboId == IBOId_Invalid) {
		glDrawArrays(GL_TRIANGLES, 0, 3 * m_numberOfVerts);
	}
	else {
		glDrawElements(GL_TRIANGLES, m_numberOfIndices, m_indexType, 0);
	}
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
