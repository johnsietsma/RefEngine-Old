#include "OpenGLTypes.h"

std::shared_ptr<Buffer> VBO::Create(GLuint bufferSize, GLuint numberOfVerts, const GLfloat verts[])
{
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return std::shared_ptr<Buffer>((Buffer*)new VBO(GL_ARRAY_BUFFER, vertexBufferId, numberOfVerts));
}
