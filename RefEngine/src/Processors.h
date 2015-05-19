#pragma once

#include "ComponentIteratorPair.h"

namespace reng {
	class Camera;
	class Material;
	class Mesh;
	class OpenGLRenderer;
	class Transform;

	void Render(Camera* pCamera, OpenGLRenderer* pRenderer, ComponentIteratorPair<Mesh*> meshIters, ComponentIteratorPair<Material*> materialIters, ComponentIteratorPair<Transform> transformIters);
}