#include "TestBed.h"

#include "TestPhysics.h"

#include "AssetManager.h"
#include "GameTime.h"
#include "RefEngine.h"

#include "entity/RenderableComponent.h"
#include "entity/TransformComponent.h"

#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Prims.h"

#include <cmath>
#include <FBXFile.h>
#include <memory>
#include <vector>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>



using namespace reng;

static const std::vector<VertexAttribute> UVVertexAttributes{
    VertexAttribute::Create<float>(0, 3), // position, 3 float
    VertexAttribute::Create<float>(0, 2)  // uv, 2 floats
};

static const std::vector<VertexAttribute> FBXVertexAttributes {
    VertexAttribute::Create<float>(offsetof(FBXVertex, position), 4),
    VertexAttribute::Create<float>(offsetof(FBXVertex, colour), 4),
    VertexAttribute::Create<float>(offsetof(FBXVertex, normal), 4),
    VertexAttribute::Create<float>(offsetof(FBXVertex, tangent), 4),
    VertexAttribute::Create<float>(offsetof(FBXVertex, binormal), 4),
    VertexAttribute::Create<float>(offsetof(FBXVertex, indices), 4),
    VertexAttribute::Create<float>(offsetof(FBXVertex, weights), 4),
    VertexAttribute::Create<float>(offsetof(FBXVertex, texCoord1), 2),
    VertexAttribute::Create<float>(offsetof(FBXVertex, texCoord2), 2)
};


void EmplaceFBXModel(RefEngine& eng,  const char* fbxFilename, std::shared_ptr<Material> pMaterial)
{
    Entity& fbxEnt = eng.EmplaceEntity();
    auto& transformComponentHandle = fbxEnt.EmplaceComponent<TransformComponent>( Transform(glm::vec3(0, 0, 3)) );

    auto fbx = std::shared_ptr<FBXFile>(new FBXFile());
    fbx->load(fbxFilename);

    for (uint i = 0; i < fbx->getMeshCount(); i++) {
        FBXMeshNode* pMesh = fbx->getMeshByIndex(i);
        if (pMesh->m_vertices.size() >  0) {
            uint numIndices = 0;
            uint* pIndices = nullptr;
            if (pMesh->m_indices.size() > 0) {
                numIndices = pMesh->m_indices.size();
                pIndices = &(pMesh->m_indices[0]);
            }

            const BufferAccessor accessor(pMesh->m_vertices, 1);
            auto pFbxMesh = Mesh::Create<FBXVertex>(accessor, FBXVertexAttributes, BufferAccessor(pMesh->m_indices,1));
            fbxEnt.EmplaceComponent<RenderableComponent>(transformComponentHandle, pFbxMesh, pMaterial);
        }
    }

    fbx->initialiseOpenGLTextures();
}


class SpinComponent : public UpdateComponent {
public:
    SpinComponent(ComponentHandle<TransformComponent>& transComp) :
        m_transformComponentHandle(transComp)
    {}

    void Update(double deltaTime) override
    {
        auto& transComponent = m_transformComponentHandle.GetComponent();
        auto trans = transComponent.GetTransform();
        trans = glm::rotate<float>(trans.GetMartix(), (float)(spinSpeed * deltaTime), glm::vec3(0, 1.f, 0));
        transComponent.SetTransform(trans);
    }

private:
    ComponentHandle<TransformComponent> m_transformComponentHandle;
    float spinSpeed = 10;
};


class VertexColorComponent : public UpdateComponent {
public:
    VertexColorComponent(const Primitive& a_colorPrim) :
        colorPrim(a_colorPrim),
        colors(a_colorPrim.accessor.count*4),
        accumTime(0)
    {
        colorPrim.accessor = BufferAccessor(colors, 1);
    }

    void Update(double deltaTime) override 
    {
        accumTime += deltaTime;
        size_t colorsSize = colorPrim.accessor.count;
        float* colorBuffer = (float*)colorPrim.accessor.buffer.data;
        for (uint i = 0; i < colorsSize; i++)
        {
            float mult = 1 + (i / 3.0f); // 1, 2 or 3
            mult /= 3.0f;
            float time = (float)accumTime + mult;
            float normTime = (time - (int)time); // fractional part
            colorBuffer[i] = sin( normTime );
        }
        colorPrim.UpdateBuffer();
    }

private:
    Primitive colorPrim;
    std::vector<float> colors;
    double accumTime;
};


TestBed::TestBed() :
	m_flyInput(GetCamera())
{}

bool TestBed::DoInit()
{
    RegisterUpdateComponent<SpinComponent>();
    RegisterUpdateComponent<VertexColorComponent>();

    // Add a textured quad
    auto pebbleTex = m_assetManager.LoadTexture("data/textures/Big_pebbles_pxr128.png");
    
    ProgramId texturedProgram = m_assetManager.LoadProgram("data/shaders/textured.vert", "data/shaders/textured.frag");
    auto texturedMat = std::make_shared<Material>(texturedProgram, pebbleTex.m_textureId);
    auto accessor = BufferAccessor(Prims::Quad_VerticesAndUVs, 5);
    auto pQuadMesh = Mesh::Create<float>( accessor, UVVertexAttributes, BufferAccessor(Prims::Quad_Indices,1) );

    Entity& entTexQuad = EmplaceEntity();
    auto& texQuadTrans = entTexQuad.EmplaceComponent<TransformComponent>(Transform(glm::vec3(5, 0, 0), glm::quat(glm::vec3(glm::half_pi<float>(), 0, 0)), glm::vec3(3)));
    entTexQuad.EmplaceComponent<RenderableComponent>(texQuadTrans, pQuadMesh, texturedMat);


    // Add a couple of non-indexed tris
    ProgramId redProgram = m_assetManager.LoadProgram("data/shaders/default.vert", "data/shaders/red.frag");
    const auto& pRedMaterial = m_assetManager.CreateMaterial(redProgram);

    std::shared_ptr<Mesh> pTriMesh = Mesh::Create<float>( BufferAccessor(Prims::Triangle_Vertices, 3) );
    Entity& entSpin1 = EmplaceEntity();
    auto& spinTrans1 = entSpin1.EmplaceComponent<TransformComponent>(glm::vec3(-2, 1, 0));
    entSpin1.EmplaceComponent<RenderableComponent>(spinTrans1, pTriMesh, pRedMaterial);
    entSpin1.EmplaceComponent<SpinComponent>(spinTrans1);

    Entity& entSpin2 = EmplaceEntity();
    auto& spinTrans2 = entSpin1.EmplaceComponent<TransformComponent>(glm::vec3(2, 1, 0));
    entSpin2.EmplaceComponent<RenderableComponent>(spinTrans2, pTriMesh, pRedMaterial);
    entSpin2.EmplaceComponent<SpinComponent>(spinTrans2);

    // Add a colored cube
    std::vector<Primitive> cubeBuffers;
    cubeBuffers.emplace_back( BufferAccessor(Prims::Cube_Vertices,3), Primitive::Vec3VertexAttribute );
    cubeBuffers.emplace_back( BufferAccessor(Prims::Cube_Colors,4), Primitive::Vec4VertexAttribute, false );
    std::shared_ptr<Mesh> pColoredCubeMesh = Mesh::Create(cubeBuffers, BufferAccessor(Prims::Cube_Indices,1));
    ProgramId vertexColorProgram = m_assetManager.LoadProgram("data/shaders/vertexColor.vert", "data/shaders/vertexColor.frag");
    const auto& pVertexColorMaterial = std::make_shared<Material>(vertexColorProgram);

    Entity& colorCubeEnt = EmplaceEntity();
    auto& colorCubeTrans = colorCubeEnt.EmplaceComponent<TransformComponent>(glm::vec3(3, 2, 3));
    colorCubeEnt.EmplaceComponent<RenderableComponent>(colorCubeTrans, pColoredCubeMesh, pVertexColorMaterial);
    colorCubeEnt.EmplaceComponent<VertexColorComponent>(cubeBuffers[1]);

    // Add an indexed cube
    const auto& litMaterial = m_assetManager.CreateMaterial("data/shaders/lit.vert", "data/shaders/lit.frag");
    std::shared_ptr<Mesh> pCubeMesh = Mesh::Create<float>(BufferAccessor(Prims::Cube_VerticesAndNormals, 6), Primitive::VertexPositionAndNormalsAttribute, BufferAccessor(Prims::Cube_Indices,1));
    Entity& indexedCubeEnt = EmplaceEntity();
    auto& indexedCubeTrans = indexedCubeEnt.EmplaceComponent<TransformComponent>(glm::vec3(0, 0, -5));
    indexedCubeEnt.EmplaceComponent<RenderableComponent>(indexedCubeTrans, pCubeMesh, litMaterial);

	// Add a fbx model
    EmplaceFBXModel(*this, "data/models/cube.fbx", litMaterial);

    return true;
}

void TestBed::DoUpdate(double deltaTime)
{
	m_flyInput.Update(GetWindow(), deltaTime);
}
