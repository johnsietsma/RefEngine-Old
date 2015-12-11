#include "TestBed.h"

#include "TestPhysics.h"

#include "AssetManager.h"
#include "GameTime.h"
#include "RenderableGameObject.h"
#include "graphics\OpenGLRenderer.h"
#include "RefEngine.h"
#include "Transform.h"

#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Prims.h"

#include <FBXFile.h>
#include <array>
#include <memory>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>



using namespace reng;

static const std::vector<VertexAttribute> UVVertexAttributes{
    VertexAttribute::Create<glm::vec4>(4, 0, GL_FLOAT),
    VertexAttribute::Create<glm::vec2>(2, sizeof(float)*4, GL_FLOAT)
};


static const std::vector<VertexAttribute> FBXVertexAttributes {
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, position), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, colour), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, normal), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, tangent), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, binormal), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, indices), GL_FLOAT),
	VertexAttribute::Create<glm::vec4>(4, offsetof(FBXVertex, weights), GL_FLOAT),
	VertexAttribute::Create<glm::vec2>(2, offsetof(FBXVertex, texCoord1), GL_FLOAT),
	VertexAttribute::Create<glm::vec2>(2, offsetof(FBXVertex, texCoord2), GL_FLOAT)
};

class SpinObject : public RenderableGameObject {
public:
    SpinObject(glm::vec3 pos, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Material> pMaterial) 
        : RenderableGameObject(pos, pMesh, pMaterial)
    {}

    void Update( double deltaTime ) override {
        m_transform = glm::rotate<float>(m_transform.GetMartix(), (float)(spinSpeed * deltaTime), glm::vec3(0, 1.f, 0));
    }

    float spinSpeed = 10;
};


TestBed::TestBed() :
	m_flyInput(GetCamera())
{}

bool TestBed::DoInit()
{
	ShaderId vertShader = m_assetManager.LoadShader("data/shaders/default.vert", VertexShader);
	ShaderId redFragShader = m_assetManager.LoadShader("data/shaders/red.frag", FragmentShader);
	if (vertShader == ShaderId_Invalid || redFragShader == ShaderId_Invalid) return false;

	ProgramId redProgram = m_assetManager.LinkProgram(vertShader, redFragShader);
	if (redProgram == ProgramId_Invalid) return false;

    std::shared_ptr<Material> pRedMaterial = std::make_shared<Material>(redProgram);

    // Add a quad
    auto pQuadMesh = Mesh::Create(Prims::Quad_VerticesAndUVs, Prims::Quad_Indices, UVVertexAttributes);
    Transform quadRot(glm::vec3(5,0,0), glm::quat(glm::vec3(glm::half_pi<float>(), 0, 0)), glm::vec3(3));
    EmplaceGameObject<RenderableGameObject>(quadRot, pQuadMesh, pRedMaterial);

    // Add a couple of tris
    std::shared_ptr<Mesh> pTriMesh = Mesh::Create(Prims::Triangle_Vertices);
    EmplaceGameObject<SpinObject>(glm::vec3(-2, 0, 0), pTriMesh, pRedMaterial);
    EmplaceGameObject<SpinObject>(glm::vec3(2, 0, 0), pTriMesh, pRedMaterial);

    // Add a cube
    std::shared_ptr<Mesh> pCubeMesh = Mesh::Create(Prims::Cube_Vertices, Prims::Cube_Indices);
    EmplaceGameObject<RenderableGameObject>(glm::vec3(0, 0, -5), pCubeMesh, pRedMaterial);

	// Add a fbx model
	auto fbx = std::shared_ptr<FBXFile>(new FBXFile());
	fbx->load("data/models/cube.fbx");

	for (uint i = 0; i < fbx->getMeshCount(); i++) {
		FBXMeshNode* pMesh = fbx->getMeshByIndex(i);
		if (pMesh->m_vertices.size() >  0) {
			uint numIndices = 0;
			uint* pIndices = nullptr;
			if (pMesh->m_indices.size() > 0) {
				numIndices = pMesh->m_indices.size();
				pIndices = &(pMesh->m_indices[0]);
			}


            auto pFbxMesh = Mesh::Create(pMesh->m_vertices, pMesh->m_indices, FBXVertexAttributes);
            EmplaceGameObject<RenderableGameObject>(glm::vec3(0, 0, 3), pFbxMesh, pRedMaterial);
		}
	}

	fbx->initialiseOpenGLTextures();

	return true;
}

void TestBed::DoUpdate(double deltaTime)
{
	m_flyInput.Update(GetWindow(), deltaTime);
}
