#pragma once
#include "Application.h"
#include "Eupch.h"
#include <glad/glad.h>
#include "Input.h"
#include <glm/glm.hpp>
#include <Europa/mesh/Mesh.h>


namespace Eu
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Eu::ShaderDataType::Float:		return GL_FLOAT;
			case Eu::ShaderDataType::Float2:	return GL_FLOAT;
			case Eu::ShaderDataType::Float3:	return GL_FLOAT;
			case Eu::ShaderDataType::Float4:	return GL_FLOAT;
			case Eu::ShaderDataType::Mat3:		return GL_FLOAT;
			case Eu::ShaderDataType::Mat4:		return GL_FLOAT;
			case Eu::ShaderDataType::Int:		return GL_INT;
			case Eu::ShaderDataType::Int2:		return GL_INT;
			case Eu::ShaderDataType::Int3:		return GL_INT;
			case Eu::ShaderDataType::Int4:		return GL_INT;
			case Eu::ShaderDataType::Bool:		return GL_BOOL;
		}
	}

	Application::Application()
	{
		EU_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_pCamera = std::make_unique<Camera>(glm::vec3{ 0,0, 2 }, 60, m_Window->GetWidth(), m_Window->GetHeight());

		Mesh nieuwMesh{ "Resources/vehicle.obj" };


		float vertices[3 * 6] =
		{
			//first thre positions last 4 color
			-0.5f,-0.5f,0.0f, 1.f, 0.f, 0.f,
			0.5f, -0.5f,0.0f, 0.2f, 0.3f, 0.8f,
			0.0f, 0.5f,0.0f, 0.8f, 0.8f, 0.2f,
		};
		auto vertexBuffer = nieuwMesh.GetVertexBuffer();
		auto indexBuffer = nieuwMesh.GetIndexBuffer();

		m_VertexBuffer.reset(VertexBuffer::Create(vertexBuffer.data(), vertexBuffer.size()));
		{
			BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Color"},
			{ShaderDataType::Float2, "a_Uv"},
			{ShaderDataType::Float3, "a_Normal"},







			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);


			//uses data from current bound glarraybuffer
			glVertexAttribPointer(index, //get start index(for exmaple layout(location = 0) in vertex shader)
				element.GetComponentCount(), //Get size of component
				ShaderDataTypeToOpenGLBaseType(element.Type), //get OPENGL TYPE
				element.Normalized ? GL_TRUE : GL_FALSE, //normalize or not
				m_VertexBuffer->GetLayout().GetStride(), //how many data do we wanna skip
				(const void*)element.Offset); //where should we start reading the data from
			index++;


		}



		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indexBuffer.data(), indexBuffer.size() ));

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		std::string VertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProj;


			out vec3 v_Position;
			out vec4 v_Color;


			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProj * vec4(a_Position, 1.0);
				
			}
		)";

		std::string FragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;




			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";





		m_Shader.reset(new Shader(VertexSrc, FragmentSrc));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
		
	}

	void Application::OnEvent(Event& e)
	{


		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		EU_CLIENT_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{

		while (m_Running)
		{
			RenderCommand::SetClearColor(glm::vec4{ 0.2, 0.2, 0.2, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			m_pCamera->InputHandling();
			auto mat = (m_pCamera->GetInverseONBMatrix());
			m_Shader->SetUniformMatrix4(mat, "u_ViewProj");


			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			

			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();


			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}

