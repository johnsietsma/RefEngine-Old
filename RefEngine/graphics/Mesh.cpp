#include "Mesh.h"

#include "utils/pow2assert.h"

using namespace reng;


const std::vector<VertexAttribute> Mesh::PositionVertexAttribute {
    VertexAttribute::Create<float>(3, 0),
};


Mesh::Mesh(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType) :
vboId(vboId),
vaoId(vaoId),
iboId(iboId),
indexType(indexType),
numberOfVerts(numberOfVerts),
numberOfIndices(numberOfIndices)
{
}


std::shared_ptr<Mesh> Mesh::CreateMesh_Impl(
	size_t vertexSize, uint numberOfVerts, const void* verts,
    GLenum indexType, uint numberOfIndices, const void* indices,
	size_t numberOfVertexAttributes, const VertexAttribute vertexAttributes[]
	)
{
    // Check preconditions
	POW2_ASSERT(vertexSize > 0);
	POW2_ASSERT(numberOfVerts != 0 || numberOfVerts != (GLuint)-1);
	POW2_ASSERT(verts != nullptr);

	POW2_ASSERT(indexType != (GLenum)-1);
	POW2_ASSERT((((int)numberOfIndices) == -1 || numberOfIndices == 0) || indices != nullptr);
	POW2_ASSERT(indexType >= 0);

	VAOId vertexArrayObjectId = VAOId_Invalid;
	VBOId vertexBufferId = VBOId_Invalid;
	IBOId indexBufferObjectId = IBOId_Invalid;

    // Make the VAO
    glGenVertexArrays(1, &vertexArrayObjectId.Get());
	glBindVertexArray(vertexArrayObjectId.Value());

    // Make the VBO and upload data
    glGenBuffers(1, &vertexBufferId.Get());
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId.Value());
	glBufferData(GL_ARRAY_BUFFER, numberOfVerts*vertexSize, verts, GL_STATIC_DRAW);

    // Optionally make the IBO
	if (numberOfIndices > 0) {
		glGenBuffers(1, &indexBufferObjectId.Get());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObjectId.Value());
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices*sizeof(uint), indices, GL_STATIC_DRAW);
	}

    // Set up our vertex attributes
    for (uint i = 0; i < numberOfVertexAttributes; i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, vertexAttributes[i].numComponents, vertexAttributes[i].type, GL_FALSE, vertexSize, ((char*)0) + vertexAttributes[i].offset);
    }

    // Clear the VAO binding
    glBindVertexArray(0);

	return std::make_shared<Mesh>(indexBufferObjectId, vertexArrayObjectId, vertexBufferId, numberOfVerts, numberOfIndices, indexType);
}

int Mesh::CalculateNumberOfComponents(const std::vector<VertexAttribute>& vertexAttributes) {
    int numComponents = 0;
    std::for_each(vertexAttributes.begin(), vertexAttributes.end(), [&numComponents](const VertexAttribute& va) { numComponents += va.numComponents; });
    return numComponents;
}

int Mesh::CalculateVertexSize(const std::vector<VertexAttribute>& vertexAttributes) {
    int vertexSize = 0;
    std::for_each(vertexAttributes.begin(), vertexAttributes.end(), [&vertexSize](const VertexAttribute& va) { vertexSize += va.componentSize*va.numComponents; });
    return vertexSize;
}
