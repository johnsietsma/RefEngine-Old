#pragma once
#include "OpenGLTypes.h"
#include <memory>

class Buffer;
class Material;

class Renderable
{
public:
	Renderable(Material* pMaterial, Buffer* pBuffer);

	std::shared_ptr<Material> GetMaterial() const { return m_pMaterial;  }
	std::shared_ptr<Buffer> GetBuffer() const { return m_pBuffer;  }

private:
	std::shared_ptr<Material> m_pMaterial;
	std::shared_ptr<Buffer> m_pBuffer;
};
