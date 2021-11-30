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

			virtual void DrawIndexedNoDepth(const std::shared_ptr<VertexArray>& VertexArray) override;

			virtual void EnableDepthTest() override;
		
			virtual void EnableWireFrame() override;

			virtual void DisableWireFrame() override;

			virtual void SetBlending() override;



			void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t heigth) override;

	private:
	};
}