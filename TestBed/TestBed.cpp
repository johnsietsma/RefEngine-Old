#include "TestBed.h"

#include <AssetManager.h>
#include <ComponentManager.h>
#include <Material.h>
#include <Mesh.h>
#include <RefEngine.h>
#include <Renderable.h>
#include <Prims.h>
#include <Processor.h>
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




TestBed::TestBed() :
	m_pAssetManager( new AssetManager() ),
	m_pRefEngine(new RefEngine() )
{}

bool TestBed::Init()
{
	ShaderId vertShader = m_pAssetManager->LoadShader("data/shaders/default.vert", VertexShader);
	ShaderId fragShader = m_pAssetManager->LoadShader("data/shaders/red.frag", FragmentShader);
	if (vertShader == ShaderId_Invalid || fragShader == ShaderId_Invalid) return false;

	ProgramId programId = m_pAssetManager->LinkProgram(vertShader, fragShader);
	if (programId == ProgramId_Invalid) return false;


	Material* pMaterial = new Material(programId);

	GameTime* pTime = m_pRefEngine->GetTime();
	Transform* pT1 = new Transform(glm::vec3(-2, 0, 0));
	Transform* pT2 = new Transform(glm::vec3(2, 0, 0));

	// Put in a couple of tris
	Mesh* pTriBuffer = Mesh::Create<>(Prims::Triangle_NumberOfVerts, Prims::Triangle_Vertices);
	Renderable* triRenderable = new Renderable(pMaterial, pTriBuffer, pT1);

	SpinComponent spin1 = { pT1, pTime };
	SpinComponent spin2 = { pT2, pTime };

	ComponentManager* pComponentManager = m_pRefEngine->GetComponentManager();
	pComponentManager->AddComponent(spin1);
	pComponentManager->AddComponent(spin2);



	//m_gameObjects.push_back(, new SpinController(), triRenderable));
	//m_gameObjects.push_back(new Transform(glm::vec3(2, 0, 0), new SpinController(), triRenderable));

	// Add a cube
	auto pCubeBuffer = Mesh::Create(Prims::Cube_NumberOfVerts, Prims::Cube_Vertices, Prims::Cube_NumberOfIndices, Prims::Cube_Indices);
	Renderable* cubeRenderable = new Renderable(pMaterial, pCubeBuffer, pT2);
	//m_gameObjects.push_back(new GameObject(glm::vec3(0, 0, -5), nullptr, cubeRenderable));

	// Add a fbx model
	m_fbx = std::shared_ptr<FBXFile>(new FBXFile());
	m_fbx->load("data/models/cube.fbx");

	Transform* fbxTransform = new Transform(glm::vec3(0, 0, 3));

	for (uint i = 0; i < m_fbx->getMeshCount(); i++) {
		FBXMeshNode* pMesh = m_fbx->getMeshByIndex(i);
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

			Renderable* fbxRenderable = new Renderable(pMaterial, pMeshBuffer, fbxTransform);
			//m_gameObjects.push_back(new GameObject(glm::vec3(0, 0, 3), nullptr, fbxRenderable));
		}
	}

	m_fbx->initialiseOpenGLTextures();
}

void TestBed::Run()
{

}
