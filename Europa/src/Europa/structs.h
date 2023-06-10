#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace Eu {
	struct VertexInput
	{};
	struct ChunkVertexInput : VertexInput
	{
		glm::vec3 Position;
	};
	struct Vertex_Input
	{
		Vertex_Input() = default;
		Vertex_Input(glm::vec3 position, glm::vec3 color, glm::vec2 uv, glm::vec3 normal) : Position{position}, Color{color}, uv{uv}, Normal{normal}
		{

		}
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
	struct OBJ {
		std::vector<Vertex_Input> m_VertexBuffer;
		std::vector<uint32_t> m_IndexBuffer;
	};

}
