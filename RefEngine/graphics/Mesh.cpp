#include "Mesh.h"

#include "utils/pow2assert.h"

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


std::shared_ptr<Mesh> Mesh::CreateMesh_Impl( const std::vector<Buffer>& buffers )
{
    auto buffer = buffers[0];

    // Check preconditions
	POW2_ASSERT(buffer.vertexSize > 0);
    POW2_ASSERT(buffer.numberOfVerts != 0 || buffer.numberOfVerts != (GLuint)-1);
    POW2_ASSERT(buffer.verts != nullptr);

    POW2_ASSERT(buffer.indexType != (GLenum)-1);
    POW2_ASSERT((((int)buffer.numberOfIndices) == -1 || buffer.numberOfIndices == 0) || buffer.indices != nullptr);
    POW2_ASSERT(buffer.indexType >= 0);

	VAOId vertexArrayObjectId = VAOId_Invalid;
	VBOId vertexBufferId = VBOId_Invalid;
	IBOId indexBufferObjectId = IBOId_Invalid;

    // Make the VAO
    glGenVertexArrays(1, &vertexArrayObjectId.Get());
	glBindVertexArray(vertexArrayObjectId.Value());

    // Make the VBO and upload data
    glGenBuffers(1, &vertexBufferId.Get());
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId.Value());
    glBufferData(GL_ARRAY_BUFFER, buffer.numberOfVerts*buffer.vertexSize, buffer.verts, GL_STATIC_DRAW);

    // Optionally make the IBO
    if (buffer.numberOfIndices > 0) {
		glGenBuffers(1, &indexBufferObjectId.Get());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectId.Value());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.numberOfIndices*sizeof(uint), buffer.indices, GL_STATIC_DRAW);
	}

    // Set up our vertex attributes
    for (uint i = 0; i < buffer.numberOfVertexAttributes; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, buffer.vertexAttributes[i].numComponents, buffer.vertexAttributes[i].type, GL_FALSE, buffer.vertexSize, ((char*)0) + buffer.vertexAttributes[i].offset);
    }

    // Clear the VAO binding
    glBindVertexArray(0);

    return std::make_shared<Mesh>(indexBufferObjectId, vertexArrayObjectId, vertexBufferId, buffer.numberOfVerts, buffer.numberOfIndices, buffer.indexType);
}

