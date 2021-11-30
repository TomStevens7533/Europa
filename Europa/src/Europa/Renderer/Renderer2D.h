#pragma once
#include <glm/glm.hpp>
#include "Renderer.h"

namespace Eu {
	class Renderer2D 
	{
	public:
		static void Init();

		static void BeginUIScene();

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4{1.f, 1.f, 1.f, 1.f});


		static void shutdown();

		static void EndUIScene();
	private:

	};

}
