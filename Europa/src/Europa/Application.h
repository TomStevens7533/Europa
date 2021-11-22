#pragma once

#include "Window.h"
#include <glm/glm.hpp>
#include "imgui/ImGuiLayer.h"
#include "Core/TimeStep.h"
#include "LayerStack.h"


namespace Eu
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true; 
		bool m_IsMinimized = false;
		LayerStack m_LayerStack;
		TimeStep m_FrameTimeStep;
		float m_LastFrameTime = 0.f;




		static Application* s_Instance;


		glm::mat4 m_WorldMatrix{
		1,0,0,3,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
		};

	};
	// To be defined
	Application* CreateApplication();
}
