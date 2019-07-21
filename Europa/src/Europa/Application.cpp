#pragma once
#include "Application.h"
#include "Eupch.h"
#include <glad/glad.h>
#include "Input.h"



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



		float vertices[3 * 7] =
		{
			-0.5f,-0.5f,0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f,0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f,0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"}

			};

			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				m_VertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset);
			index++;
		}



		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));


		std::string VertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = v_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
				
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
			glClearColor(0.2, 0.2, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			glBindVertexArray(m_VertexArray);
			m_Shader->Bind();
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			Input::IsMouseButtonPressed(1);

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

