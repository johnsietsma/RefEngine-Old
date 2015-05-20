#include "TestBed.h"

#include <AssetManager.h>
#include <ComponentManager.h>
#include <Entity.h>
#include <EntityManager.h>
#include <Material.h>
#include <Mesh.h>
#include <RefEngine.h>
#include <Prims.h>
#include <ProcessorManager.h>
#include <Transform.h>

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


TestBed::TestBed() :
	m_pAssetManager( new AssetManager() ),
	m_pRefEngine(new RefEngine() )
{}

bool TestBed::Init()
{
	m_pRefEngine->Init();

	ShaderId vertShader = m_pAssetManager->LoadShader("data/shaders/default.vert", VertexShader);
	ShaderId fragShader = m_pAssetManager->LoadShader("data/shaders/red.frag", FragmentShader);
	if (vertShader == ShaderId_Invalid || fragShader == ShaderId_Invalid) return false;

	ProgramId programId = m_pAssetManager->LinkProgram(vertShader, fragShader);
	if (programId == ProgramId_Invalid) return false;



	std::shared_ptr<GameTime> pTime = m_pRefEngine->GetTime();

	// Put in a couple of tris
	Mesh* pTriBuffer = Mesh::Create<>(Prims::Triangle_NumberOfVerts, Prims::Triangle_Vertices);
	Material* pMaterial = new Material(programId);

	auto ent1 = m_pRefEngine->GetEntityManager()->Create();
	ent1->AddComponent<Transform>(glm::vec3(-2, 0, 0));
	ent1->AddComponent<SpinComponent>();
	ent1->AddComponent<Mesh*>(pTriBuffer);
	ent1->AddComponent<Material*>(pMaterial);
	m_entities.emplace_back(std::move(ent1));
	
	auto ent2 = m_pRefEngine->GetEntityManager()->Create();
	ent2->AddComponent<Transform>(glm::vec3(2, 0, 0));
	ent2->AddComponent<SpinComponent>();
	ent2->AddComponent<Mesh*>(pTriBuffer);
	ent2->AddComponent<Material*>(pMaterial);
	m_entities.emplace_back(std::move(ent2));

	// Add a cube
	auto pCubeBuffer = Mesh::Create(Prims::Cube_NumberOfVerts, Prims::Cube_Vertices, Prims::Cube_NumberOfIndices, Prims::Cube_Indices);

	std::shared_ptr<Entity> cube = m_pRefEngine->GetEntityManager()->Create();
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

			auto fbxModel = m_pRefEngine->GetEntityManager()->Create();
			fbxModel->AddComponent<Transform>(glm::vec3(0, 0, 3));
			fbxModel->AddComponent<Mesh*>(pMeshBuffer);
			fbxModel->AddComponent<Material*>(pMaterial);
			m_entities.emplace_back(std::move(fbxModel));
		}
	}

	fbx->initialiseOpenGLTextures();

	return true;
}

void TestBed::Run()
{
	m_pRefEngine->Run();
}
