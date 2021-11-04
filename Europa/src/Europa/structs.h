#pragma once
#include <glm/glm.hpp>

namespace Eu {
	struct Vertex_Input
	{
		glm::vec3 Position;
		glm::vec3 Color;
		glm::vec2 uv;
		glm::vec3 Normal;

		bool operator == (Vertex_Input rhs) {
			if (this->Position == rhs.Position && this->uv == rhs.uv && this->Color == rhs.Color)
				return true;
			else return false;
		}
	};
}
