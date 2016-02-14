#include "TransformComponent.h"

#include "entity/Component.h"

#include "imgui.h"

using namespace reng;

void TransformComponent::DrawDebugUI(ComponentId id)
{
	Transform t = GetTransform();

	char name[512];
	sprintf(name, "Transform - %ld", id);

	ImGui::BeginChild(name, ImVec2(250,50));

	//
	glm::vec3 rot = t.GetEulerAngles();
	rot *= 180 / glm::pi<float>();

	if (ImGui::DragFloat3("Rotation", &rot[0])) {
		rot *= glm::pi<float>() / 180;
		t.SetEulerAngles(rot);
		SetTransform(t);
	}

	glm::vec3 pos = t.GetPosition();
	if (ImGui::DragFloat3("Position", &pos[0])) {
		t.SetPosition(pos);
		SetTransform(t);
	}

	ImGui::EndChild();
}

