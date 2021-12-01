#include "Renderer2D.h"
#include "../ResourceManager.h"
#include "RenderCommand.h"
#include "glm/gtx/transform.hpp"
#include <Platform/OpenGL/EuropaOpenGL.h>


namespace Eu {

	struct Renderer2DStorage {
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<BaseProgram> QuadProgram;
	};

	static Renderer2DStorage* s_2DData = nullptr;

	void Renderer2D::Init()
	{
		if (s_2DData == nullptr) {
			EU_CORE_INFO("INITIALIZING 2D RENDERER!!");
			s_2DData = new Renderer2DStorage();

			s_2DData->QuadVertexArray.reset(VertexArray::Create());

			std::vector<Vertex_Input> squareVertices;
			squareVertices.push_back(Vertex_Input{ {-0.5f, -0.5f, 0.0f},{-0.f, -0.f, 0.0f}, {0.f, 0.f}, {0.f, 0.f, 0.f} });
			squareVertices.push_back(Vertex_Input{ {0.5f,-0.5f,	0.0,},{-0.f, -0.f, 0.0f},	{1.f, 0.f}, {0.f, 0.f, 0.f} });
			squareVertices.push_back(Vertex_Input{ {0.5f, 0.5f, 0.0f},{-0.f, -0.f, 0.0f}, {1.f, 1.f}, {0.f, 0.f, 0.f} });
			squareVertices.push_back(Vertex_Input{ {-0.5f, 0.5f, 0.0f},{-0.f, -0.f, 0.0f}, {0.f, 1.f}, {0.f, 0.f, 0.f} });

			std::shared_ptr<VertexBuffer> quadVertexBuffer;
			quadVertexBuffer.reset(VertexBuffer::Create(squareVertices.data(), squareVertices.size()));

			quadVertexBuffer->SetLayout({
			{Eu::ShaderDataType::Float3, "a_Position"},
			{Eu::ShaderDataType::Float3, "a_Color"},
			{Eu::ShaderDataType::Float2, "a_Uv"},
			{Eu::ShaderDataType::Float3, "a_Normal"},
				});

			s_2DData->QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

			uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
			std::shared_ptr<IndexBuffer> quadIndexBuffer;
			quadIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
			s_2DData->QuadVertexArray->AddIndexBuffer(quadIndexBuffer);

			s_2DData->QuadProgram = ResourceManager::GetInstance()->GetProgram(ShaderType::TEXTURE2D_UILOCALSPACE_SHADER);
		}
		else
			EU_CORE_ERROR("2D renderer already initialized");
		

		
	}

	void Renderer2D::BeginUIScene(const Camera& sceneCamera)
	{


		s_2DData->QuadProgram->Bind();
		s_2DData->QuadProgram->SetUniformInt(0, "u_Texture", Eu::BaseProgram::ShaderTypes::T_PixelShader);


		s_2DData->QuadProgram->SetUniformMatrix4(glm::mat4(1) * sceneCamera.GetProjectionMatrix(), "u_Proj", BaseProgram::ShaderTypes::T_VertexShader);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		//Set Color
		s_2DData->QuadProgram->SetUniformVec4(color, "u_Color", BaseProgram::ShaderTypes::T_VertexShader);
		s_2DData->QuadProgram->SetUniformMatrix4(
			glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), {size.x, size.y , 1.f}) /* * ROTATION*/,
			"u_TransForm", BaseProgram::ShaderTypes::T_VertexShader);
		s_2DData->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_2DData->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<BaseTexture>& Texture, const glm::vec4& color)
	{
		Texture->Bind();
		DrawQuad(position, size, color);
	}

	void Renderer2D::shutdown()
	{
		delete s_2DData;
		s_2DData = nullptr;
	}

	void Renderer2D::EndUIScene()
	{

	}


}



