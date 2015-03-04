#pragma once
#include "OpenGLTypes.h"
#include <memory>

class Buffer;
class Material;

class Renderable
{
public:
	Renderable(ProgramId programId, std::shared_ptr<Material>, std::shared_ptr<Buffer> buffer);
	void Init();
	void Render();
private:
	ProgramId m_programId;
	std::shared_ptr<Material> m_material;
	std::shared_ptr<Buffer> m_buffer;
};
