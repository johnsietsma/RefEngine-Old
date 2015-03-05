#pragma once
#include "OpenGLTypes.h"
#include <memory>

class Buffer;
class Material;

class Renderable
{
public:
	Renderable(std::shared_ptr<Material> material, std::shared_ptr<Buffer> buffer);

	std::shared_ptr<Material> GetMaterial() const { return m_pMaterial;  }
	std::shared_ptr<Buffer> GetBuffer() const { return m_pBuffer;  }

private:
	std::shared_ptr<Material> m_pMaterial;
	std::shared_ptr<Buffer> m_pBuffer;
};
