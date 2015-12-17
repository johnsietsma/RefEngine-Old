#include "Mesh.h"

#include "utils/pow2assert.h"

#include <algorithm>

using namespace reng;

Mesh::Mesh(VAOId a_vaoId, IBOId a_iboId, std::vector<VBOId> a_vboIds, GLenum a_indexType, GLuint a_numberOfIndices, GLuint a_numberOfVerts) :
    vaoId(a_vaoId),
    iboId(a_iboId),
    vboIds(a_vboIds),
    indexType(a_indexType),
    numberOfIndices(a_numberOfIndices),
    numberOfVerts(a_numberOfVerts)
{

}

std::shared_ptr<Mesh> Mesh::Create(std::vector<Buffer>& buffers, const std::vector<uint>& indices)
{
    VAOId vertexArrayObjectId = VAOId_Invalid;

    std::vector<VBOId> vboIds(buffers.size());
    IBOId iboId = IBOId_Invalid;

    uint numVerts = -1;
    uint numIndices = -1;

    // Make the VAO
    glGenVertexArrays(1, &vertexArrayObjectId.Get());
	glBindVertexArray(vertexArrayObjectId.Value());

    uint numberOfIndices = indices.size();
    uint numberOfVerts = -1;
    uint attribLocation = 0;

    // Optionally make the IBO
    if (numberOfIndices > 0) {
        glGenBuffers(1, &iboId.Get());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId.Value());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices*sizeof(uint), indices.data(), GL_STATIC_DRAW);
    }

    // Run through each buffer, create and upload it.
    for (uint i = 0; i < buffers.size(); i++)
    {
        auto& buffer = buffers[i];

        // Check preconditions
        POW2_ASSERT(buffer.vertexSize > 0);
        POW2_ASSERT(buffer.numberOfVerts != 0 || buffer.numberOfVerts != (GLuint)-1);
        POW2_ASSERT(buffer.verts != nullptr);

        POW2_ASSERT(numberOfVerts == -1 || numberOfVerts == buffer.numberOfVerts);
        numberOfVerts = buffer.numberOfVerts;

        GLenum usage = buffer.isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

        // Make the VBO and upload data
        glGenBuffers(1, &vboIds[i].Get());
        buffer.vboId = vboIds[i];
        glBindBuffer(GL_ARRAY_BUFFER, vboIds[i].Value());
        glBufferData(GL_ARRAY_BUFFER, buffer.numberOfVerts*buffer.vertexSize, buffer.verts, usage);

        // Set up our vertex attributes
        for (uint i = 0; i < buffer.vertexAttributes.size(); i++) {
            glEnableVertexAttribArray(attribLocation);
            glVertexAttribPointer(attribLocation, buffer.vertexAttributes[i].numComponents, buffer.vertexAttributes[i].type, GL_FALSE, buffer.vertexSize, ((char*)0) + buffer.vertexAttributes[i].offset);
            attribLocation++;
        }
    }

    // Clear the VAO binding
    glBindVertexArray(0);

    return std::make_shared<Mesh>( vertexArrayObjectId, iboId, vboIds, GL_UNSIGNED_INT, numberOfIndices, numberOfVerts );
}

void Mesh::UpdateBuffer(const Buffer& buffer)
{
    GLenum usage = buffer.isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vboId.Value());
    glBufferData(GL_ARRAY_BUFFER, buffer.numberOfVerts*buffer.vertexSize, buffer.verts, usage);
}
