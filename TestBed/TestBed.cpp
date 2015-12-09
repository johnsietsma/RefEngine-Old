#include "TestBed.h"

#include "TestPhysics.h"

#include "AssetManager.h"
#include "GameTime.h"
#include "IGameObject.h"
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


//trans = glm::rotate<float>(trans.GetMartix(), 10 * (float)gameTime.deltaTime, glm::vec3(0, 1.f, 0));

class SpinObject : public IGameObject {
public:
    SpinObject(glm::vec3 pos, std::shared_ptr<Mesh> pMesh, std::shared_ptr<Material> pMaterial) :
        m_transform(pos),
        m_pMesh(pMesh),
        m_pMaterial(pMaterial)
    {}

    void Update( double deltaTime ) override {
        m_transform = glm::rotate<float>(m_transform.GetMartix(), (float)(spinSpeed * deltaTime), glm::vec3(0, 1.f, 0));
    }

    void Draw( OpenGLRenderer* pRenderer, Camera* pCamera ) const override
    {
        pRenderer->UseProgram(m_pMaterial->GetProgramId());

        // TODO: Cache this
        m_pMaterial->UpdateUniforms(pCamera->GetProjectionViewMatrix(), m_transform.GetMartix());

        pRenderer->Bind(*m_pMesh);
        pRenderer->Draw(*m_pMesh);

        pRenderer->Unbind();
        pRenderer->UnuseProgram();
    }

    Transform m_transform;
    std::shared_ptr<Mesh> m_pMesh;
    std::shared_ptr<Material> m_pMaterial;
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

	GameTime* pTime = GetTime();

	// Put in a couple of tris
	std::shared_ptr<Mesh> pTriBuffer = Mesh::Create<>(Prims::Triangle_NumberOfVerts, Prims::Triangle_Vertices);
	std::shared_ptr<Material> pMaterial = std::make_shared<Material>(programId);

    EmplaceGameObject<SpinObject>(glm::vec3(-2, 0, 0), pTriBuffer, pMaterial);


	/*auto ent1 = GetEntityManager()->Create();
	ent1->EmplaceComponent<Transform>(glm::vec3(-2, 0, 0));
	ent1->EmplaceComponent<SpinComponent>();
	ent1->EmplaceComponent<Mesh*>(pTriBuffer);
	ent1->EmplaceComponent<Material*>(pMaterial);
	m_entities.emplace_back(std::move(ent1));
	
	auto ent2 = GetEntityManager()->Create();
	ent2->EmplaceComponent<Transform>(glm::vec3(2, 0, 0));
	ent2->EmplaceComponent<SpinComponent>();
	ent2->EmplaceComponent<Mesh*>(pTriBuffer);
	ent2->EmplaceComponent<Material*>(pMaterial);
	m_entities.emplace_back(std::move(ent2));

	// Add a cube
	auto pCubeBuffer = Mesh::Create(Prims::Cube_NumberOfVerts, Prims::Cube_Vertices, Prims::Cube_NumberOfIndices, Prims::Cube_Indices);

	std::shared_ptr<Entity> cube = GetEntityManager()->Create();
	cube->EmplaceComponent<Transform>(glm::vec3(0, 0, -5));
	cube->EmplaceComponent<Mesh*>(pCubeBuffer);
	cube->EmplaceComponent<Material*>(pMaterial);
	m_entities.emplace_back(std::move(cube));

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

			auto fbxModel = GetEntityManager()->Create();
			fbxModel->EmplaceComponent<Transform>(glm::vec3(0, 0, 3));
			fbxModel->EmplaceComponent<Mesh*>(pMeshBuffer);
			fbxModel->EmplaceComponent<Material*>(pMaterial);
			m_entities.emplace_back(std::move(fbxModel));
		}
	}

	fbx->initialiseOpenGLTextures();

	AddPhysXObjects(GetEntityManager(), m_physXProcessor.get());
	AddPhysicsObjects(GetEntityManager(), m_physicsProcessor.get());
    */
	return true;
}

void TestBed::DoUpdate(double deltaTime)
{
	m_flyInput.Update(GetWindow(), deltaTime);
}
