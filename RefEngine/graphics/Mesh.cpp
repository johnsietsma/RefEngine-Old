#include "Mesh.h"

#include "utils/pow2assert.h"

#include <algorithm>

using namespace reng;

Mesh::Mesh(VAOId a_vaoId, IBOId a_iboId, std::vector<VBOId> a_vboIds, GLenum a_indexType, GLuint a_numberOfIndices, GLuint a_numberOfVerts) :
    vaoId(a_vaoId),
    vboIds(a_vboIds),
    numberOfVerts(a_numberOfVerts),
    iboId(a_iboId),
    indexType(a_indexType),
    numberOfIndices(a_numberOfIndices)
{
    POW2_ASSERT(numberOfVerts > 0);

}

std::shared_ptr<Mesh> Mesh::Create(std::vector<Primitive>& primitives,  const BufferAccessor& indices)
{
    VAOId vertexArrayObjectId = VAOId_Invalid;

    std::vector<VBOId> vboIds(primitives.size());
    IBOId iboId = IBOId_Invalid;

    uint numVerts = -1;
    uint numIndices = indices.count;

    // Make the VAO
    glGenVertexArrays(1, &vertexArrayObjectId.Get());
	glBindVertexArray(vertexArrayObjectId.Value());

    uint attribLocation = 0;

    // Optionally make the IBO
    if (numIndices > 0) {
        POW2_ASSERT(indices.buffer.data);
        glGenBuffers(1, &iboId.Get());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId.Value());
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.buffer.size, indices.buffer.data, GL_STATIC_DRAW);
    }

    // Run through each buffer, create and upload it.
    for (uint i = 0; i < primitives.size(); i++)
    {
        auto& prim = primitives[i];

        auto& buffer = prim.accessor.buffer;

        // Check preconditions
        POW2_ASSERT(buffer.size > 0);
        POW2_ASSERT(buffer.data != nullptr);

        numVerts = prim.accessor.count;

        GLenum usage = prim.isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

        // Make the VBO and upload data
        glGenBuffers(1, &vboIds[i].Get());
        prim.vboId = vboIds[i];
        glBindBuffer(GL_ARRAY_BUFFER, vboIds[i].Value());
        glBufferData(GL_ARRAY_BUFFER, buffer.size, buffer.data, usage);

        size_t totalOffset = 0;

        // Set up our vertex attributes
        for (uint i = 0; i < prim.vertexAttributes.size(); i++) {
            auto attrib = prim.vertexAttributes[i].accessor;

            int offset = attrib.byteOffset == 0 ? totalOffset : attrib.byteOffset;

            glEnableVertexAttribArray(attribLocation);
            // We get the stride from the Primitiv, no the attribute.
            glVertexAttribPointer(attribLocation, attrib.count, attrib.type, GL_FALSE, prim.accessor.byteStride, ((char*)0) + totalOffset);
            attribLocation++;

            // If not offset is given, calculate it
            totalOffset += attrib.byteOffset == 0 ? attrib.count*attrib.byteStride : attrib.byteOffset;
        }
    }

    // Clear the VAO binding
    glBindVertexArray(0);

    return std::make_shared<Mesh>(vertexArrayObjectId, iboId, vboIds, GL_UNSIGNED_INT, numIndices, numVerts);
}
