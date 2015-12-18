#pragma once

#include "graphics/VertexBufferInfo.h"
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
        const std::vector<VertexAttribute>& vertexAttributes = VertexBufferInfo::Vec3VertexAttribute, // Vert postions only by default
        const std::vector<uint>& indices = VertexBufferInfo::EmptyIndex // No indices by default
    )
    {
        const VertexBufferInfo& buffer = VertexBufferInfo::Create(vertices, vertexAttributes, true);
        auto buffers = std::vector<VertexBufferInfo>(1, buffer);
        return Create(buffers, indices);
    }

    void UpdateBuffer(const VertexBufferInfo& buffer);

    static std::shared_ptr<Mesh> Create(std::vector<VertexBufferInfo> & buffers, const std::vector<uint>& indices);


};

}
