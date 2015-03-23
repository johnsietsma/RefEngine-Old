#include "Mesh.h"

#include "pow2assert.h"

using namespace reng;

Mesh::Mesh(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType) :
vboId(vboId),
vaoId(vaoId),
iboId(iboId),
indexType(indexType),
numberOfVerts(numberOfVerts),
numberOfIndices(numberOfIndices)
{
}


Mesh* Mesh::CreateMesh(
	size_t vertexSize, uint numberOfVerts, const void* verts,
	size_t indexSize, GLenum indexType, uint numberOfIndices, const void* indices,
	size_t numberOfVertexAttributes, const VertexAttribute vertexAttributes[]
	)
{
	POW2_ASSERT(vertexSize > 0);
	POW2_ASSERT(numberOfVerts != 0 || numberOfVerts != (GLuint)-1);
	POW2_ASSERT(verts != nullptr);

	POW2_ASSERT((indexSize <= 0 && indices == nullptr) || indexSize > 0);
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

	return new Mesh(indexBufferObjectId, vertexArrayObjectId, vertexBufferId, numberOfVerts, numberOfIndices, indexType);
}