#pragma once

#include <glm/vec4.hpp>

class Color
{
public:
	static const glm::vec4 White;
	static const glm::vec4 Black;
	static const glm::vec4 Red;
	static const glm::vec4 Green;
	static const glm::vec4 Blue;
private:
	Color(); // Don't allow object creation
};

