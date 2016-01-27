#include "TransformComponent.h"

#include "AntTweakBar.h"

#include <glm/gtc/type_ptr.hpp>

using namespace reng;

void SetTransform_Position(const void* value, void* userdata)
{
    Transform* pTransform = static_cast<Transform*>(userdata);
    float* pos = (float*)value;
    pTransform->SetPosition(glm::vec3(pos[0], pos[1], pos[2]));
}

void GetTransform_Position(void* value, void* userdata)
{
    Transform* pTransform = static_cast<Transform*>(userdata);
    glm::vec3 pos = pTransform->GetPosition();
    float* pPosValue = (float*)value;
    pPosValue[0] = pos[0];
    pPosValue[1] = pos[2];
    pPosValue[2] = pos[3];
}

void TransformComponent::AddDebugVars(TwBar* pBar)
{
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' ");
    TwAddVarCB(pBar, "Position", TwType::TW_TYPE_DIR3F, SetTransform_Position, GetTransform_Position, &m_transform, nullptr);
}
