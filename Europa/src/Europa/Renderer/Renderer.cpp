#pragma once
#include "Renderer.h"
#include "Eupch.h"
#include <glad/glad.h>
#include "RenderCommand.h"

namespace Eu
{
	void Renderer::BeginScene()
	{
		RenderCommand::EnableDepthTest();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
		//Rendercommand
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray); //render command
	}
}