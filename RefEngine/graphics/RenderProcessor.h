#pragma once

#include "components/Processor.h"

#include "Mesh.h"

#include <memory>

namespace reng {

class Camera;
class OpenGLRenderer;

class RenderProcessor : public Processor<Mesh*> {
public:
	RenderProcessor(const Camera* pCamera, std::shared_ptr<OpenGLRenderer> pRenderer) :
		m_pCamera(pCamera),
		m_pRenderer(pRenderer)
	{
	}

private:
	void DoProcess( const std::vector<EntityId>& entityIds, ComponentManager& componentManager ) override;

	const Camera* m_pCamera;
	std::shared_ptr<OpenGLRenderer> m_pRenderer;
};

}