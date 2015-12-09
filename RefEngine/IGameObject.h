#pragma once

namespace reng {

class OpenGLRenderer;
class Camera;

class IGameObject
{
public:
    virtual void Update(double deltaTime) = 0;
    virtual void Draw(OpenGLRenderer* pRenderer, Camera* pCamera) const = 0;
};

}