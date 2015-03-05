#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>


#include "OpenGLTypes.h"

class Camera;
class GameObject;
class Renderable;
class ShaderManager;

class Renderer
{
public:
	void Init( int width, int height );
	void Render(std::shared_ptr<Camera> pCamera, std::vector<GameObject*> gameObjects);
};
