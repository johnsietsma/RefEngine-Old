#include "TestBed.h"

#include "TestPhysics.h"

#include "AssetManager.h"
#include "GameTime.h"
#include "GizmosComponent.h"
#include "RefEngine.h"
#include "Transform.h"

#include "components/ComponentManager.h"
#include "components/Entity.h"
#include "components/EntityManager.h"
#include "components/Processor.h"

#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Prims.h"

#include "physics/PhysicsComponent.h"
#include "physics/PhysXComponent.h"
#include "physics/PhysXGizmoComponent.h"

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
	void DoProcess(const std::vector<EntityId>& entityIds, ComponentManager& componentManager, GameTime& gameTime) override
	{
		auto spinContainer = componentManager.GetComponentContainer<SpinComponent>();
		auto transformContainer = componentManager.GetComponentContainer<Transform>();

		for (auto entityId : entityIds)
		{
			auto& spin = spinContainer->Get(entityId);
			auto& trans = transformContainer->Get(entityId);
			trans = glm::rotate<float>(trans.GetMartix(), 10 * (float)gameTime.deltaTime, glm::vec3(0, 1.f, 0));
		}
	}
};


TestBed::TestBed() :
	m_flyInput(GetCamera()),
	m_spinProcessor(new SpinProcessor()),
	m_physXProcessor(new PhysXProcessor()),
	m_physicsProcessor(new PhysicsProcessor()),
	m_gizmoProcessor(new AABBGizmoProcessor()),
	m_physXGizmoProcessor(new PhysXGizmoProcessor())
{}

bool TestBed::DoInit()
{
	m_physXProcessor->InitVisualDebugger();

	ShaderId vertShader = m_assetManager.LoadShader("data/shaders/default.vert", VertexShader);
	ShaderId fragShader = m_assetManager.LoadShader("data/shaders/red.frag", FragmentShader);
	if (vertShader == ShaderId_Invalid || fragShader == ShaderId_Invalid) return false;

	ProgramId programId = m_assetManager.LinkProgram(vertShader, fragShader);
	if (programId == ProgramId_Invalid) return false;

	GameTime* pTime = GetTime();

	// Put in a couple of tris
	Mesh* pTriBuffer = Mesh::Create<>(Prims::Triangle_NumberOfVerts, Prims::Triangle_Vertices);
	Material* pMaterial = new Material(programId);

	auto ent1 = GetEntityManager()->Create();
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

	return true;
}

void TestBed::DoUpdate(double deltaTime)
{
	m_flyInput.Update(GetWindow(), deltaTime);
	m_spinProcessor->Process(*GetComponentManager(), *GetTime());
	m_physXProcessor->Process(*GetComponentManager(), *GetTime());
	m_physicsProcessor->Process(*GetComponentManager(), *GetTime());
	m_gizmoProcessor->Process(*GetComponentManager());
	m_physXGizmoProcessor->Process(*GetComponentManager());
}
