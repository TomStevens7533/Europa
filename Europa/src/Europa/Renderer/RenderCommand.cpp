#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

//place for all renderer commands

namespace Eu {
	RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI;


	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RenderAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RenderAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& a)
	{
		s_RenderAPI->DrawIndexed(a);
	}

	void RenderCommand::DrawIndexedNoDepth(const std::shared_ptr<VertexArray>& a)
	{
		s_RenderAPI->DrawIndexedNoDepth(a);
	}


	void RenderCommand::EnableDepthTest()
	{
		s_RenderAPI->EnableDepthTest();
	}

}