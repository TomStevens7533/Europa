#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "VertexArray.h"

namespace Eu {

	class RendererAPI { //interface so we can use multiple apis for now only opengl
	public:
		enum class API
		{
			None = 0, OpenGL = 1


		};
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) = 0;

		virtual void DrawIndexedNoDepth(const std::shared_ptr<VertexArray>& VertexArray) = 0;

		virtual void EnableDepthTest() = 0;

		inline static API GetAPI() { return s_CurrentAPI; }

	private:
		static API s_CurrentAPI;
		glm::vec4 clearColor;
	};
}

