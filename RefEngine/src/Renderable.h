#pragma once
#include "OpenGLTypes.h"

#include "Transform.h"

#include <glm/glm.hpp>

#include <memory>

namespace reng {

class Mesh;
class Material;

class Renderable
{
public:
	Renderable(Material* pMaterial, Mesh* pMesh, Transform* transform);

	Material* GetMaterial() const { return m_pMaterial.get();  }
	Mesh* GetMesh() const { return m_pMesh.get();  }
	const glm::mat4x4& GetTransform() const { return m_pTransform->GetTransform(); }

private:
	std::shared_ptr<Material> m_pMaterial;
	std::shared_ptr<Mesh> m_pMesh;
	Transform* m_pTransform;
};

}