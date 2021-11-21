#pragma once
#include "Renderer.h"
#include "Eupch.h"
#include <glad/glad.h>
#include "RenderCommand.h"



//https://stackoverflow.com/questions/18403708/crash-on-gldrawelements

namespace Eu
{
	//TODO make it onto the stack with no crashes 
	const Camera* Renderer::m_SceneData = nullptr;
	bool Renderer::m_IsFirstFrame = true;

	void Renderer::BeginScene(const Camera& sceneCamera)
	{
		RenderCommand::EnableDepthTest();
		m_SceneData = &sceneCamera;
	}
	void Renderer::EndScene()
	{
		m_IsFirstFrame = true;
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform) {
		//Rendercommand
		//program->Bind();
		if (m_IsFirstFrame == true) {
			program->SetUniformMatrix4(m_SceneData->GetViewProjectionMatrix(), "u_ViewProj", BaseProgram::ShaderTypes::T_VertexShader);
			m_IsFirstFrame = false;
		}
		//(program)->SetUniformMatrix4(transform, "u_TranslationMat", BaseProgram::ShaderTypes::T_VertexShader);

		vertexArray->Bind();


		RenderCommand::DrawIndexed(vertexArray);
	}
	void Renderer::SubmitNoDepth(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<BaseProgram>& program, const glm::mat4& transform, bool isBackground) {
		//Rendercommand
		program->Bind();

		glm::mat4 view = glm::mat4(1.f);

		if (isBackground) //remove translation data from matrix
			view = glm::mat4(glm::mat3(m_SceneData->GetViewProjectionMatrix()));
		else
			view = m_SceneData->GetViewProjectionMatrix();

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