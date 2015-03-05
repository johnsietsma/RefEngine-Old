#pragma once

#include <glm/glm.hpp>
#include <memory>

class Buffer;
class Material;

class GameObject
{
public:
	GameObject( const glm::vec3& transform, std::shared_ptr<Material> pMaterial, std::shared_ptr<Buffer> pBuffer );

	const glm::mat4x4& GetTransform() const { return m_transform;  }
	const std::shared_ptr<Material> GetMaterial() const { return m_pMaterial; }
	const std::shared_ptr<Buffer> GetBuffer() const { return m_pBuffer;  }

private:
	glm::mat4x4 m_transform;
	std::shared_ptr<Material> m_pMaterial;
	std::shared_ptr<Buffer>	m_pBuffer;
};
