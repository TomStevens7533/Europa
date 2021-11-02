#pragma once
#include "Application.h"
#include "Eupch.h"
#include <glad/glad.h>
#include "Input.h"
#include <glm/glm.hpp>
#include <Europa/mesh/Mesh.h>
#include "glm/gtc/matrix_transform.hpp"
#include "GameObject.h"



namespace Eu
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
		: m_Camera(glm::vec3{ 0,0, 10 }, 60)
	{
		EU_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_Camera.SetWidthAndHeight({ m_Window->GetWidth(), m_Window->GetHeight() });
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		

		m_pCar = std::make_shared<gameObject>();
		m_pCar->AddMesh("Resources/vehicle.obj");
		m_pCar->AddTexture("Resources/vehicle_diffuse.png", TextureTypes::TEXTURE2D);

		m_pCar2 = std::make_shared<gameObject>();
		m_pCar2->AddMesh("Resources/kubus.obj");
		m_pCar2->AddTexture("Resources/skybox/skybox", TextureTypes::CUBETEXTURE);

		m_pSkyBox = std::make_shared<SkyBox>();
		m_pSkyBox->AddTexture("Resources/skybox/skybox");



		

		//m_SkyBoxProgram.reset(BaseProgram::Create());

		//m_SkyBoxProgram->SetUniformInt(0, "u_CubeTexture", BaseProgram::ShaderTypes::T_PixelShader);

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

		//EU_CLIENT_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.GetEventType() == EventType::MouseMoved) {
				MouseMovedEvent* mouseEvent = dynamic_cast<MouseMovedEvent*>(&e);
				m_Camera.MouseInputHandling({ mouseEvent->GetX(), mouseEvent->GetY() });
			}
				
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		glm::vec3 motorPos = {0,-1,0};
		glm::vec3 motorPos2 = { 1.f,2.f,1 };
		m_pCar2->SetPos(motorPos2);

		while (m_Running)
		{
			//motorPos += glm::vec3{0.01f, 0, 0};
			//m_pCar->SetPos(motorPos);
			//m_pCar->Update();

			//RenderCommand::SetClearColor(glm::vec4{ 0.2, 0.2, 0.2, 1 });
			RenderCommand::Clear();

			//m_pCar->Bind();

			//motorPos2 += glm::vec3{ 0.01f, 0, 0 };
			//m_pCar2->SetPos(motorPos2);
			//m_pCar2->Update();
			//m_pCamera->SetCameraOffsetPos(glm::vec3{ 0.01f, 0, 0 });
			Renderer::BeginScene(m_Camera);

			//m_pCar->AddRotation(glm::vec3{ 0.f, glm::radians(0.01f),0.f });

			for (size_t x = 0; x < 10; x++)
			{
				m_pCar->SetPos({ motorPos.x + (20 * x), motorPos.y , motorPos.z });
				m_pCar->Render();

				for (size_t i = 0; i < 20; i++)
				{
					m_pCar->SetPos({ motorPos.x + (20 * x), motorPos.y , motorPos.z + (20 * i) });
					m_pCar->Render();

				}
			}

			m_pCar2->Render();
			m_pSkyBox->Render();


			Renderer::EndScene();

			m_Camera.KeyInputHandling();
			m_Camera.Update(0.1f);



			m_ImGuiLayer->Begin();
			m_ImGuiLayer->OnUpdate();
			m_ImGuiLayer->OnImGuiRender();
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

