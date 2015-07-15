#pragma once

#include "components/Processor.h"

#include "Mesh.h"

#include <memory>

namespace reng {

class Camera;
class OpenGLRenderer;

class FlyCameraProcessor : public Processor<Camera> {
public:
	RenderProcessor(std::shared_ptr<Camera> pCamera, std::shared_ptr<OpenGLRenderer> pRenderer) :
		m_pCamera(pCamera),
		m_pRenderer(pRenderer)
	{
	}

private:
	void DoProcess( const std::vector<EntityId>& entityIds, ComponentManager& componentManager ) override;

	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<OpenGLRenderer> m_pRenderer;
};

}