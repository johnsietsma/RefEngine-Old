#pragma once

#include "Buffer.h"
#include "OpenGlTypes.h"
#include "types.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace reng {


class Mesh {
public:
    // Vertex array object id
	const VAOId vaoId;

    // Vertex buffer information
    const std::vector<VBOId> vboIds;
    const uint numberOfVerts;

    // Index buffer information
    const IBOId iboId;
    const GLenum indexType;
    const uint numberOfIndices;
        
    Mesh(VAOId a_vaoId, IBOId a_iboId, std::vector<VBOId> a_vboIds, GLenum a_indexType, GLuint a_numberOfIndices, GLuint a_numberOfVerts);

    /**
     * Create a mesh from vertex data.
     * Optionally pass in index data to create an indexed mesh.
     * Optionall pass in vertex attributes to use more then just vertex position data.
     */
    template<typename VertT>
    static std::shared_ptr<Mesh> Create( 
        const std::vector<VertT>& vertices,
        const std::vector<VertexAttribute>& vertexAttributes = Buffer::Vec3VertexAttribute, // Vert postions only by default
        const std::vector<uint>& indices = Buffer::EmptyIndex // No indices by default
    )
    {
        const Buffer& buffer = Buffer::Create(vertices, vertexAttributes, true);
        return Create( std::vector<Buffer>(1, buffer), indices );
    }

    void UpdateBuffer(const Buffer& buffer);

    static std::shared_ptr<Mesh> Create(std::vector<Buffer>& buffers, const std::vector<uint>& indices);


};

}
