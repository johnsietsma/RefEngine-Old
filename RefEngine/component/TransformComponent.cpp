#include "TransformComponent.h"

#include "imgui.h"

using namespace reng;

void TransformComponent::DrawDebugUI()
{
	Transform t = GetTransform();

	ImGui::BeginChild("Transform");

	glm::vec3 right = t.GetRight();
	if (ImGui::DragFloat3("Right", &right[0]))
	{
		t.SetRight(right);
		SetTransform(t);
	}

	glm::vec3 up = t.GetUp();
	if (ImGui::DragFloat3("Up", &up[0]))
	{
		t.SetUp(up);
		SetTransform(t);
	}

	glm::vec3 fwd = t.GetForward();
	if (ImGui::DragFloat3("Forward", &fwd[0])) {
		t.SetForward(fwd);
		SetTransform(t);
	}

	glm::vec3 pos = t.GetPosition();
	ImGui::DragFloat3("Position", &pos[0]);

	ImGui::EndChild();
}
