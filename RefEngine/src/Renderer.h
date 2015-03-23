#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>


#include "OpenGLTypes.h"


namespace reng {

class Camera;
class OpenGLRenderer;
class Renderable;

class Renderer
{
public:
	Renderer();
	void Init( int width, int height );
	void Render(const Camera* pCamera, const std::vector<Renderable>& renderables) const;

private:
	std::shared_ptr<OpenGLRenderer> m_pRendererImpl;
};

}