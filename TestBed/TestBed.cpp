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
#include <memory>
#include <glm/gtx/transform.hpp>



using namespace reng;

static const VertexAttribute FBXVertexAttributes[9] = {
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
	ShaderId fragShader = m_assetManager.LoadShader("data/shaders/red.frag", FragmentShader);
	if (vertShader == ShaderId_Invalid || fragShader == ShaderId_Invalid) return false;

	ProgramId programId = m_assetManager.LinkProgram(vertShader, fragShader);
	if (programId == ProgramId_Invalid) return false;

	// Put in a couple of tris
	std::shared_ptr<Mesh> pTriBuffer = Mesh::Create<>(Prims::Triangle_NumberOfVerts, Prims::Triangle_Vertices);
    std::shared_ptr<Mesh> pCubeBuffer = Mesh::Create(Prims::Cube_NumberOfVerts, Prims::Cube_Vertices, Prims::Cube_NumberOfIndices, Prims::Cube_Indices);

    std::shared_ptr<Material> pMaterial = std::make_shared<Material>(programId);

    // Add a couple of tris
    EmplaceGameObject<SpinObject>(glm::vec3(-2, 0, 0), pTriBuffer, pMaterial);
    EmplaceGameObject<SpinObject>(glm::vec3(2, 0, 0), pTriBuffer, pMaterial);

    // Add a cube
    EmplaceGameObject<RenderableGameObject>(glm::vec3(0, 0, -5), pCubeBuffer, pMaterial);

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


			auto pMeshBuffer = Mesh::Create(
				pMesh->m_vertices.size(), &(pMesh->m_vertices[0]),
				numIndices, pIndices,
				sizeof(FBXVertexAttributes) / sizeof(VertexAttribute), FBXVertexAttributes
				);

            EmplaceGameObject<RenderableGameObject>(glm::vec3(0, 0, 3), pMeshBuffer, pMaterial);
		}
	}

	fbx->initialiseOpenGLTextures();

	return true;
}

void TestBed::DoUpdate(double deltaTime)
{
	m_flyInput.Update(GetWindow(), deltaTime);
}
