#pragma once
#include "Europa/Renderer/RendererAPI.h"

//place with raw opengl calls

namespace Eu {
	class OpenGLRendererAPI final : public RendererAPI
	{
		public:
			virtual void SetClearColor(const glm::vec4& color) override;

			virtual void Clear() override;

			virtual void DrawIndexed(const std::shared_ptr<VertexArray>& a) override;
		private:
	};
}