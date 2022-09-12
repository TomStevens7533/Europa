#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

//place for all renderer commands

namespace Eu {
	std::shared_ptr<RendererAPI> RenderCommand::s_RenderAPI = std::make_shared<OpenGLRendererAPI>();


	void RenderCommand::Init()
	{
		RenderCommand::EnableDepthTest();
		s_RenderAPI->SetBlending();
		//s_RenderAPI->EnableWireFrame();
	}

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

	void RenderCommand::EnableWireFrame()
	{
		s_RenderAPI->EnableWireFrame();
	}

	void RenderCommand::DisablewireFrame()
	{
		s_RenderAPI->DisableWireFrame();
	}

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t heigth)
	{
		s_RenderAPI->SetViewPort(x, y, width, heigth);
	}

}