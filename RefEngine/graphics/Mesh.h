#pragma once

#include "Buffer.h"
#include "OpenGlTypes.h"
#include "types.h"

#include <memory>
#include <vector>

namespace reng {


class Mesh {
public:
	VBOId vboId;
	VAOId vaoId;
	IBOId iboId;
	GLenum indexType;
    GLuint numberOfVerts;
    GLuint numberOfIndices;

    Mesh(IBOId iboId, VAOId vaoId, VBOId vboId, GLuint numberOfVerts, GLuint numberOfIndices, GLenum indexType);

    /**
     * Create a mesh from vertex data.
     * Optionally pass in index data to create an indexed mesh.
     * Optionall pass in vertex attributes to use more then just vertex position data.
     */
    template<typename VertT>
    static std::shared_ptr<Mesh> Create( 
        const std::vector<VertT>& vertices,
        const std::vector<uint>& indices = Buffer::EmptyIndex, // No indices by default
        const std::vector<VertexAttribute>& vertexAttributes = Buffer::PositionVertexAttribute // Vert postions only by default
    )
    {
        const Buffer& buffer = Buffer::Create(vertices, indices, vertexAttributes);
        return CreateMesh_Impl( std::vector<Buffer>(1, buffer) );
    }

private:
	static std::shared_ptr<Mesh> CreateMesh_Impl( const std::vector<Buffer>& buffer );


};

}
