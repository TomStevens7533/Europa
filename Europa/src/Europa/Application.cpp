#pragma once
#include "Application.h"
#include "Eupch.h"
#include <glad/glad.h>
#include "Input.h"
#include <glm/glm.hpp>
#include "ResourceManager.h"
#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"



namespace Eu
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		EU_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application()
	{
		Renderer::ShutDown();
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
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));


		//EU_CLIENT_TRACE("{0}", e);

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

			//Calculate deltaTime
			float time = static_cast<float>(glfwGetTime()); //TODO: make it so its platform indepedent Platform::GetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_IsMinimized) {
				for (Layer* currentLayer : m_LayerStack)
					currentLayer->OnUpdate(timestep);
			}


			m_ImGuiLayer->Begin();
			for (Layer* currentLayer : m_LayerStack)
				currentLayer->OnImGuiRender();
			m_ImGuiLayer->End();

			
			m_Window->OnUpdate();
		}

		
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_IsMinimized = true;
			return false;
		}
		m_IsMinimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		//All layers need to know about resizing
		return false;
	}

}

