#pragma once

#include "ComponentIteratorPair.h"

#include <memory>
#include <tuple>

namespace reng {
	class Camera;
	class Material;
	class Mesh;
	class OpenGLRenderer;
	class Transform;

class RenderProcessor {
public:



	RenderProcessor(std::shared_ptr<Camera> pCamera, std::shared_ptr<OpenGLRenderer> pRenderer) :
		m_pCamera(pCamera),
		m_pRenderer(pRenderer)
	{
	}

	void Process(ComponentIteratorPair<Mesh*> meshIters, ComponentIteratorPair<Material*> materialIters, ComponentIteratorPair<Transform> transformIters);
	void Process( std::tuple<ComponentIteratorPair<Mesh*>, ComponentIteratorPair<Material*>, ComponentIteratorPair<Transform>> iterators );
private:
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<OpenGLRenderer> m_pRenderer;
};

}