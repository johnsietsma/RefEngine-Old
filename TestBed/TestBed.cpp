#include "TestBed.h"

#include "AssetManager.h"
#include "ComponentManager.h"
#include "Entity.h"
#include "EntityManager.h"
#include "GameTime.h"
#include "Material.h"
#include "Mesh.h"
#include "RefEngine.h"
#include "Prims.h"
#include "Processor.h"
#include "Transform.h"

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


struct SpinComponent {
	SpinComponent() = default;
	SpinComponent(int s) : spinSpeed(s) {}
	int spinSpeed;
};

class SpinProcessor : public Processor<SpinComponent,GameTime>
{
public:
	virtual void DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager, GameTime& gameTime)
	{
		auto spinContainer = componentManager.GetComponentContainer<SpinComponent>();
		auto transformContainer = componentManager.GetComponentContainer<Transform>();

		for (auto entityId : entityIds)
		{
			auto& spin = spinContainer->Get(entityId);
			auto& trans = transformContainer->Get(entityId);
			trans = glm::rotate<float>(trans.GetMartix(), 10 * gameTime.deltaTime, glm::vec3(0, 1.f, 0));
		}
	}

private:
	GameTime* m_gameTime;
};


TestBed::TestBed() :
	m_pAssetManager( new AssetManager() ),
	m_spinProcessor( new SpinProcessor() )
{}

bool TestBed::DoInit()
{
	ShaderId vertShader = m_pAssetManager->LoadShader("data/shaders/default.vert", VertexShader);
	ShaderId fragShader = m_pAssetManager->LoadShader("data/shaders/red.frag", FragmentShader);
	if (vertShader == ShaderId_Invalid || fragShader == ShaderId_Invalid) return false;

	ProgramId programId = m_pAssetManager->LinkProgram(vertShader, fragShader);
	if (programId == ProgramId_Invalid) return false;

	GameTime* pTime = GetTime();

	// Put in a couple of tris
	Mesh* pTriBuffer = Mesh::Create<>(Prims::Triangle_NumberOfVerts, Prims::Triangle_Vertices);
	Material* pMaterial = new Material(programId);

	auto ent1 = GetEntityManager()->Create();
	ent1->AddComponent<Transform>(glm::vec3(-2, 0, 0));
	ent1->AddComponent<SpinComponent>();
	ent1->AddComponent<Mesh*>(pTriBuffer);
	ent1->AddComponent<Material*>(pMaterial);
	m_entities.emplace_back(std::move(ent1));
	
	auto ent2 = GetEntityManager()->Create();
	ent2->AddComponent<Transform>(glm::vec3(2, 0, 0));
	ent2->AddComponent<SpinComponent>();
	ent2->AddComponent<Mesh*>(pTriBuffer);
	ent2->AddComponent<Material*>(pMaterial);
	m_entities.emplace_back(std::move(ent2));

	// Add a cube
	auto pCubeBuffer = Mesh::Create(Prims::Cube_NumberOfVerts, Prims::Cube_Vertices, Prims::Cube_NumberOfIndices, Prims::Cube_Indices);

	std::shared_ptr<Entity> cube = GetEntityManager()->Create();
	cube->AddComponent<Transform>(glm::vec3(0, 0, -5));
	cube->AddComponent<Mesh*>(pCubeBuffer);
	cube->AddComponent<Material*>(pMaterial);
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
			fbxModel->AddComponent<Transform>(glm::vec3(0, 0, 3));
			fbxModel->AddComponent<Mesh*>(pMeshBuffer);
			fbxModel->AddComponent<Material*>(pMaterial);
			m_entities.emplace_back(std::move(fbxModel));
		}
	}

	fbx->initialiseOpenGLTextures();

	return true;
}

void TestBed::DoUpdate(double deltaTime)
{
	m_spinProcessor->Process(*GetComponentManager(), *GetTime());
}
