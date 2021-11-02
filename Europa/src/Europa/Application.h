#pragma once

#include "Window.h"
#include "Log.h"
#include "Europa/Events/ApplicationEvent.h"
#include "Europa/LayerStack.h"
#include "Europa/imgui/ImGuiLayer.h"
#include "renderer/Renderer.h"
#include "Camera.h"
#include "Renderer/VertexArray.h"
#include "Texture.h"
#include "Renderer/Program.h"

namespace Eu
{
	class gameObject;
	class SkyBox;
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
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		std::unique_ptr<BaseProgram> m_Shader;
		std::shared_ptr<gameObject> m_pCar;
		std::shared_ptr<gameObject> m_pCar2;
		std::shared_ptr<SkyBox> m_pSkyBox;


		static Application* s_Instance;
		Camera m_Camera;


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
