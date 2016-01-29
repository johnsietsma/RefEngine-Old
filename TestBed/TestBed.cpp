#include "TestBed.h"

#include "AssetManager.h"
#include "RefEngine.h"
#include "MaterialManager.h"
#include "RefEngWindowGLFW.h"

#include "component/CameraComponent.h"
#include "component/FlyInputComponent.h"
#include "component/LightComponent.h"
#include "component/RenderableComponent.h"
#include "component/SpinComponent.h"
#include "component/TransformComponent.h"

#include "entity/Entity.h"

#include "file/FBXFile.h"

#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Prims.h"

#include <cmath>

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


class VertexColorComponent : public UpdateComponent {
public:
    VertexColorComponent(const Primitive& a_colorPrim) :
        colorPrim(a_colorPrim),
        colors(a_colorPrim.accessor.count*4),
        accumTime(0)
    {
        colorPrim.accessor = BufferAccessor(colors, 1);
    }

    void Update(double deltaTime, ComponentDatabase& database ) override 
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
    m_pWindow(std::make_unique<RefEngWindowGLFW>())
{}

bool TestBed::Init()
{
    if( !m_pWindow->Init() ) return false;
    m_pEngine = m_pWindow->GetEngine();

    m_pEngine->RegisterUpdateComponent<FlyInputComponent>();
    m_pEngine->RegisterUpdateComponent<SpinComponent>();
    m_pEngine->RegisterUpdateComponent<VertexColorComponent>();

    Entity& flyEntity = m_pEngine->EmplaceEntity("FlyInput");
    flyEntity.EmplaceComponent<FlyInputComponent>(m_pEngine->GetCamera(), m_pWindow->GetWindow());

    Entity& lightEntity = m_pEngine->EmplaceEntity("Light");
    float rot = glm::half_pi<float>();
    Transform lightTransform(glm::vec3(0), glm::quat(glm::vec3(rot)));
    auto lightTransformHandle = lightEntity.EmplaceComponent<TransformComponent>(lightTransform);
    lightEntity.EmplaceComponent<LightComponent>(lightTransformHandle);

    AddTexturedQuad(glm::vec3(5, 0, 0));

    AddSpinningTri(glm::vec3(-2, 1, 0));
    AddSpinningTri(glm::vec3(2, 1, 0));

    AddVertexColoredCube(glm::vec3(3, 2, 3));

    AddLitCube(glm::vec3(0, 0, -5));

    AddFbxModel(glm::vec3(0, 0, 3), "assets/models/cube/cube.fbx");

    return true;
}

void TestBed::Run()
{
    m_pWindow->Run();
}

void TestBed::AddTexturedQuad(glm::vec3 pos)
{
    MaterialDefinition texturedMatDef(
        "assets/shaders/textured.vert",
        "assets/shaders/textured.frag",
        "assets/textures/Big_pebbles_pxr128.png"
        );

    auto texturedMat = MaterialManager::LoadMaterial(m_pEngine->GetAssetManager(), texturedMatDef);
    auto accessor = BufferAccessor(Prims::Quad_VerticesAndUVs, 5);
    auto pQuadMesh = Mesh::Create<float>(accessor, UVVertexAttributes, BufferAccessor(Prims::Quad_Indices, 1));

    Entity& entTexQuad = m_pEngine->EmplaceEntity("Textured Quad");
    auto texQuadTrans = entTexQuad.EmplaceComponent<TransformComponent>(Transform(pos, glm::quat(glm::vec3(glm::half_pi<float>(), 0, 0)), glm::vec3(3)));
    entTexQuad.EmplaceComponent<RenderableComponent>(texQuadTrans, pQuadMesh, texturedMat);
}

void TestBed::AddSpinningTri(glm::vec3 pos)
{
    MaterialDefinition redMatDef(
        "assets/shaders/default.vert",
        "assets/shaders/red.frag"
        );
    const auto& pRedMaterial = MaterialManager::LoadMaterial(m_pEngine->GetAssetManager(), redMatDef);

    // Non-indexed tri
    // TODO: Meshes in AssetManager so they're cached.
    std::shared_ptr<Mesh> pTriMesh = Mesh::Create<float>(BufferAccessor(Prims::Triangle_Vertices, 3));
    Entity& entSpin1 = m_pEngine->EmplaceEntity("Spinning Tri");
    auto spinTrans1 = entSpin1.EmplaceComponent<TransformComponent>(pos);
    entSpin1.EmplaceComponent<RenderableComponent>(spinTrans1, pTriMesh, pRedMaterial);
    entSpin1.EmplaceComponent<SpinComponent>(spinTrans1, 10.0f);
}

void TestBed::AddVertexColoredCube(glm::vec3 pos)
{
    std::vector<Primitive> cubeBuffers;
    cubeBuffers.emplace_back(BufferAccessor(Prims::Cube_Vertices, 3), Primitive::Vec3VertexAttribute);
    cubeBuffers.emplace_back(BufferAccessor(Prims::Cube_Colors, 4), Primitive::Vec4VertexAttribute, false);
    std::shared_ptr<Mesh> pColoredCubeMesh = Mesh::Create(cubeBuffers, BufferAccessor(Prims::Cube_Indices, 1));

    MaterialDefinition vertColoredMatDef(
        "assets/shaders/vertexColor.vert",
        "assets/shaders/vertexColor.frag"
        );
    const auto& pVertexColorMaterial = MaterialManager::LoadMaterial(m_pEngine->GetAssetManager(), vertColoredMatDef);

    Entity& colorCubeEnt = m_pEngine->EmplaceEntity("Vert Colored Cube");
    auto colorCubeTrans = colorCubeEnt.EmplaceComponent<TransformComponent>(pos);
    colorCubeEnt.EmplaceComponent<RenderableComponent>(colorCubeTrans, pColoredCubeMesh, pVertexColorMaterial);
    colorCubeEnt.EmplaceComponent<VertexColorComponent>(cubeBuffers[1]);
}

void TestBed::AddLitCube(glm::vec3 pos)
{
    MaterialDefinition litMatDef(
        "assets/shaders/lit.vert",
        "assets/shaders/lit.frag"
        );
    const auto& litMaterial = MaterialManager::LoadMaterial(m_pEngine->GetAssetManager(), litMatDef);
    litMaterial->SetSpecularPower(2.0f);

    std::shared_ptr<Mesh> pCubeMesh = Mesh::Create<float>(BufferAccessor(Prims::Cube_VerticesAndNormals, 6), Primitive::VertexPositionAndNormalsAttribute, BufferAccessor(Prims::Cube_Indices, 1));
    Entity& indexedCubeEnt = m_pEngine->EmplaceEntity("Lit Cube");
    auto indexedCubeTrans = indexedCubeEnt.EmplaceComponent<TransformComponent>(pos);
    indexedCubeEnt.EmplaceComponent<RenderableComponent>(indexedCubeTrans, pCubeMesh, litMaterial);
}

void TestBed::AddFbxModel(glm::vec3 pos, const char* fbxFilename)
{
    MaterialDefinition litMatDef(
        "assets/shaders/lit.vert",
        "assets/shaders/lit.frag"
        );
    const auto& litMaterial = MaterialManager::LoadMaterial(m_pEngine->GetAssetManager(), litMatDef);

    Entity& fbxEnt = m_pEngine->EmplaceEntity("Fbx Model");
    auto transformComponentHandle = fbxEnt.EmplaceComponent<TransformComponent>(Transform(pos));

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
            auto pFbxMesh = Mesh::Create<FBXVertex>(accessor, FBXVertexAttributes, BufferAccessor(pMesh->m_indices, 1));
            fbxEnt.EmplaceComponent<RenderableComponent>(transformComponentHandle, pFbxMesh, litMaterial);
        }
    }

    fbx->initialiseOpenGLTextures();
}