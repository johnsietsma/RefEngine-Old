#include "TestBed.h"

#include "TestPhysics.h"

#include "AssetManager.h"
#include "GameTime.h"
#include "RenderableGameObject.h"
#include "graphics/OpenGLRenderer.h"
#include "RefEngine.h"
#include "Transform.h"

#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Prims.h"

#include <FBXFile.h>
#include <vector>
#include <memory>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>



using namespace reng;

static const std::vector<VertexAttribute> UVVertexAttributes{
    VertexAttribute::Create<float>(3, 0), // position, 3 float
    VertexAttribute::Create<float>(2, sizeof(float)*3) // uv, 2 floats
};


static const std::vector<VertexAttribute> FBXVertexAttributes {
	VertexAttribute::Create<float>(4, offsetof(FBXVertex, position)),
    VertexAttribute::Create<float>(4, offsetof(FBXVertex, colour)),
    VertexAttribute::Create<float>(4, offsetof(FBXVertex, normal)),
    VertexAttribute::Create<float>(4, offsetof(FBXVertex, tangent)),
    VertexAttribute::Create<float>(4, offsetof(FBXVertex, binormal)),
    VertexAttribute::Create<float>(4, offsetof(FBXVertex, indices)),
    VertexAttribute::Create<float>(4, offsetof(FBXVertex, weights)),
    VertexAttribute::Create<float>(2, offsetof(FBXVertex, texCoord1)),
    VertexAttribute::Create<float>(2, offsetof(FBXVertex, texCoord2))
};


void EmplaceFBXModel(RefEngine& eng,  const char* fbxFilename, std::shared_ptr<Material> pMaterial)
{
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


            auto pFbxMesh = Mesh::Create(pMesh->m_vertices, FBXVertexAttributes, pMesh->m_indices);
            eng.EmplaceGameObject<RenderableGameObject>(glm::vec3(0, 0, 3), pFbxMesh, pMaterial);
        }
    }

    fbx->initialiseOpenGLTextures();
}

class SpinObject : public RenderableGameObject {
public:
    SpinObject(glm::vec3 pos, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Material> pMaterial) 
        : RenderableGameObject(pos, pMesh, pMaterial)
    {}

    void Update( double deltaTime ) override 
    {
        m_transform = glm::rotate<float>(m_transform.GetMartix(), (float)(spinSpeed * deltaTime), glm::vec3(0, 1.f, 0));
    }

    float spinSpeed = 10;
};

class VertexColorAnimator : public RenderableGameObject {
public:
    VertexColorAnimator(glm::vec3 pos, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Material> pMaterial, 
        const VertexBufferInfo& a_colorBuffer, const std::vector<float>& a_colors) :
        RenderableGameObject(pos, pMesh, pMaterial),
        colorBuffer(a_colorBuffer),
        colors(a_colors.begin(), a_colors.end())
    {
        colorBuffer.verts = colors.data();
    }

    void Update(double deltaTime) override 
    {
        for (int i = 0; i < colors.size(); i++)
        {
            colors[i] = 1.f;
        }
        m_pMesh->UpdateBuffer(colorBuffer);
    }

    VertexBufferInfo colorBuffer;
    std::vector<float> colors;
};


TestBed::TestBed() :
	m_flyInput(GetCamera())
{}

bool TestBed::DoInit()
{
    // Add a textured quad
    auto pebbleTex = m_assetManager.LoadTexture("data/textures/Big_pebbles_pxr128.png");

    ProgramId texturedProgram = m_assetManager.LoadProgram("data/shaders/textured.vert", "data/shaders/textured.frag");
    auto texturedMat = std::make_shared<Material>(texturedProgram, pebbleTex.m_textureId);
    auto pQuadMesh = Mesh::Create(Prims::Quad_VerticesAndUVs, UVVertexAttributes, Prims::Quad_Indices);

    Transform quadRot(glm::vec3(5,0,0), glm::quat(glm::vec3(glm::half_pi<float>(), 0, 0)), glm::vec3(3));
    EmplaceGameObject<RenderableGameObject>(quadRot, pQuadMesh, texturedMat);
        
    // Add a couple of non-indexed tris
    ProgramId redProgram = m_assetManager.LoadProgram("data/shaders/default.vert", "data/shaders/red.frag");
    const auto& pRedMaterial = m_assetManager.CreateMaterial(redProgram);

    std::shared_ptr<Mesh> pTriMesh = Mesh::Create(Prims::Triangle_Vertices);
    EmplaceGameObject<SpinObject>(glm::vec3(-2, 0, 0), pTriMesh, pRedMaterial);
    EmplaceGameObject<SpinObject>(glm::vec3(2, 0, 0), pTriMesh, pRedMaterial);
    
    // Add a colored cube
    std::vector<VertexBufferInfo> cubeBuffers;
    cubeBuffers.emplace_back(VertexBufferInfo::Create(Prims::Cube_Vertices));
    cubeBuffers.emplace_back(VertexBufferInfo::Create(Prims::Cube_Colors, VertexBufferInfo::Vec4VertexAttribute, false));
    std::shared_ptr<Mesh> pColoredCubeMesh = Mesh::Create(cubeBuffers, Prims::Cube_Indices);
    ProgramId vertexColorProgram = m_assetManager.LoadProgram("data/shaders/vertexColor.vert", "data/shaders/vertexColor.frag");
    const auto& pVertexColorMaterial = std::make_shared<Material>(vertexColorProgram);
    EmplaceGameObject<VertexColorAnimator>(glm::vec3(3, 2, 3), pColoredCubeMesh, pVertexColorMaterial, cubeBuffers[1], Prims::Cube_Colors);

    // Add an indexed cube
    std::shared_ptr<Mesh> pCubeMesh = Mesh::Create(Prims::Cube_Vertices, VertexBufferInfo::Vec3VertexAttribute, Prims::Cube_Indices);
    EmplaceGameObject<RenderableGameObject>(glm::vec3(0, 0, -5), pCubeMesh, pRedMaterial);

	// Add a fbx model
    EmplaceFBXModel(*this, "data/models/cube.fbx", pRedMaterial);

	return true;
}

void TestBed::DoUpdate(double deltaTime)
{
	m_flyInput.Update(GetWindow(), deltaTime);
}
