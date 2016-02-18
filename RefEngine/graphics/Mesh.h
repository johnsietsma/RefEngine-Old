#pragma once

#include "graphics/Primitive.h"
#include "graphics/GlTypes.h"
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
     * Optionally pass in vertex attributes to use more then just vertex position data.
     */
    template<typename VertT>
    static std::shared_ptr<Mesh> Create( 
        const BufferAccessor& accessor,
        const std::vector<VertexAttribute>& vertexAttributes = Primitive::Vec3VertexAttribute, // Vert positions only by default
        const BufferAccessor& indices = BufferAccessor::Empty // No indices by default
    )
    {
        const Primitive& prim = Primitive(accessor, vertexAttributes);
        auto prims = std::vector<Primitive>(1, prim);
        return Create(prims, indices);
    }

    static std::shared_ptr<Mesh> Create(std::vector<Primitive>& prims, const BufferAccessor& indices);


};

}
