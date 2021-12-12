#pragma once
#include "Eupch.h"
#include <glm/glm.hpp>
#include "Renderer.h"
#include "../Texture.h"

namespace Eu {
	class Renderer2D 
	{
	public:
		static void Init();

		static void BeginUIScene(const Camera& sceneCamera);

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4{1.f, 1.f, 1.f, 1.f});
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<BaseTexture>& Texture,  const glm::vec4& color = glm::vec4{ 1.f, 1.f, 1.f, 1.f });



		static void shutdown();

		static void EndUIScene();
	private:
		
	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<BaseProgram> QuadProgram;
	};

	static Renderer2DStorage* s_2DData;

	};

}
