#pragma once

#include <glm/glm.hpp>
#include <memory>


#include "OpenGLTypes.h"

class Camera;
class GameObject;
class OpenGLOperators;
class Renderable;
class ShaderManager;

class Renderer
{
public:
	Renderer();
	void Init( int width, int height );
	void Render(std::shared_ptr<Camera> pCamera, std::shared_ptr<GameObject> pGameObject);

private:
	std::shared_ptr<OpenGLOperators> m_openGLOperators;
};
