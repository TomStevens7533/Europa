#pragma once

#include "Window.h"
#include "Log.h"
#include "Europa/Events/ApplicationEvent.h"
#include "Europa/LayerStack.h"
#include "Europa/imgui/ImGuiLayer.h"
namespace Eu
{
	class EUROPA_API Application
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
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};
	// To be defined
	Application* CreateApplication();
}
