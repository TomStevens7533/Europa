#pragma once
#include "Renderer.h"
#include "Eupch.h"
#include <glad/glad.h>
#include "RenderCommand.h"



//https://stackoverflow.com/questions/18403708/crash-on-gldrawelements

namespace Eu
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(Camera& sceneCamera)
	{
		RenderCommand::EnableDepthTest();
		s_SceneData->ViewProjectionMatrix = sceneCamera.GetInverseONBMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform) {
		//Rendercommand
		program->Bind();
		program->SetUniformMatrix4(s_SceneData->ViewProjectionMatrix, "u_ViewProj", BaseProgram::ShaderTypes::T_VertexShader);
		program->SetUniformMatrix4(transform, "u_TranslationMat", BaseProgram::ShaderTypes::T_VertexShader);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::SubmitNoDepth(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform, bool isBackground) {
		//Rendercommand
		program->Bind();

		glm::mat4 view = glm::mat4(1.f);

		if (isBackground) //remove translation data from matrix
			view = glm::mat4(glm::mat3(s_SceneData->ViewProjectionMatrix));
		else
			view = (s_SceneData->ViewProjectionMatrix);

		program->SetUniformMatrix4(view, "u_ViewProj", BaseProgram::ShaderTypes::T_VertexShader);
		program->SetUniformMatrix4(transform, "u_TranslationMat", BaseProgram::ShaderTypes::T_VertexShader);

		if(isBackground) //Add background bool to put w in z in shader
			program->SetUniformInt(isBackground, "u_IsBackGround", BaseProgram::ShaderTypes::T_VertexShader);


		vertexArray->Bind();
		RenderCommand::DrawIndexedNoDepth(vertexArray);

		if(isBackground)  //remove background bool for further cubemaps
			program->SetUniformInt(0, "u_IsBackGround", BaseProgram::ShaderTypes::T_VertexShader);
	}
}