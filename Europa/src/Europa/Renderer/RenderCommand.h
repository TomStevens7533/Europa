#pragma once
#include "RendererAPI.h"

namespace Eu {
	class RenderCommand {
	public:
		static void SetClearColor(const glm::vec4& color);

		static void Clear();

		static void DrawIndexed(const std::shared_ptr<VertexArray>& vA);
		static void DrawIndexedNoDepth(const std::shared_ptr<VertexArray>& vA);

		static void EnableDepthTest();

	private:
		static std::shared_ptr<RendererAPI> s_RenderAPI;
	};
}