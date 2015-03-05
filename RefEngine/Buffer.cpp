#include "Buffer.h"

#include <memory>

std::shared_ptr<Buffer> VBO::Create(GLuint bufferSize, GLuint numberOfVerts, const GLfloat verts[])
{
	GLuint vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return std::shared_ptr<Buffer>((Buffer*)new VBO(GL_ARRAY_BUFFER, vertexArrayObject, vertexBufferId, numberOfVerts));
}

void VBO::Destroy(VAOId vaoId, VBOId vboId)
{
	glDeleteBuffers(1, &vboId.Value());
	glDeleteVertexArrays(1, &vaoId.Value());
}


void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId.Value());
	glBindVertexArray(m_vaoId.Value());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void VBO::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3 * m_numberOfVerts);
	glDisableVertexAttribArray(0);
}
