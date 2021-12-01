#include <Europa.h>

#include "VLD/include/vld.h"
#include "Chunkmanager.h"
#include "Europa/ResourceManager.h"
#include "Europa/Utils.h"
#include "Europa/Profiling/TimerManager.h"


class MineCraftLayer : public Eu::Layer {
public:
	
		MineCraftLayer() : Layer("we love mc"), m_Camera(60.f) {


			m_ChunkManager = new ChunkManager(m_Camera);
			//m_Chunk = new Chunk({ 0,-20,0 });

			//Eu::SkyBox* newSkyBox{ new 	Eu::SkyBox };
			///newSkyBox->AddTexture("Resources/skybox/skybox");
		   
			///mpScene->AddItemToSceneGraph(newSkyBox);
			m_ptexture = &Eu::ResourceManager::GetInstance()->GetTexture("Resources/minecraft/TextureAtlas.png", Eu::TextureTypes::TEXTURE2D);
			m_pCrosshairTexture = &Eu::ResourceManager::GetInstance()->GetTexture("Resources/minecraft/Crosshair.png", Eu::TextureTypes::TEXTURE2D);
		}

	void OnAttach() override
	{
	}


	void OnDetach() override 
	{
		delete m_ChunkManager;
	}


	void OnUpdate(Eu::TimeStep deltaTime) override
	{
		auto updateTimer = m_TimerManager.AddTimer("OnUpdate");
		m_Camera.OnUpdate(deltaTime);
		m_ChunkManager->Update(deltaTime, m_Camera);

		Eu::RenderCommand::SetClearColor({ 0.f, 0.3f, 0.8f, 1.f });
		Eu::RenderCommand::Clear();


		Eu::Renderer::BeginScene(m_Camera.GetCamera());
		(*m_ptexture)->Bind();

		//m_Chunk->Render();
		m_ChunkManager->Render();
		//m_pScene->RenderScene();
		Eu::Renderer::EndScene();



		Eu::Renderer2D::BeginUIScene(m_Camera.GetCamera());
		Eu::Renderer2D::DrawQuad({ 0.f, 0.f, 0.f }, { 0.2f, 0.2f }, *m_pCrosshairTexture , { 0.8f, 0.f, 0.2f, 1.f });
		Eu::Renderer2D::EndUIScene();

		m_TimerManager.StopTimer(updateTimer);
	}


	void OnEvent(Eu::Event& event) override
	{
		if (event.GetEventType() == Eu::EventType::MouseButtonPressed) {
			Eu::MouseButtonPressedEvent* mouseEvent = dynamic_cast<Eu::MouseButtonPressedEvent*>(&event);
			if (mouseEvent->GetMouseButton() == EU_MOUSE_BUTTON_1) {
				EU_CORE_INFO("Mouse down");
				glm::vec3 cameraPos = m_Camera.GetCamerPos();


				for (Eu::Ray lookRay(cameraPos, m_Camera.GetForwardVector(), 10.f); lookRay.GetCurrentPercent() <= 0.75f ; lookRay.Step(0.025f))
				{
 					if(m_ChunkManager->DeleteBlockAtPos(lookRay.GetCurrentPos()))
						break;
				}
			}
			else if (mouseEvent->GetMouseButton() == EU_MOUSE_BUTTON_2) {
				for (Eu::Ray lookRay(m_Camera.GetCamerPos(), m_Camera.GetForwardVector(), 10.f); lookRay.GetCurrentPercent() >= -1.f; lookRay.StepBack(-0.025f))
				{
					if (m_ChunkManager->AddBlockAtPos(lookRay.GetCurrentPos(), BlockTypes::DIRT))
						break;
				}
			}
		}
		m_Camera.OneEvent(event);
	}


	void OnImGuiRender() override
	{
		ImGui::Begin("TIMINGS");

		for (auto trResult : m_TimerManager.GetTimerResults())
		{
			char label[50];
			strcpy(label, trResult.Name);
			strcat(label, " %.3fms");

			ImGui::Text(label, trResult.Time);
		}
		ImGui::End();
		m_TimerManager.ClearTimerResults();
	}
private:
	//std::shared_ptr<Eu::ScenGraph> m_pScene = std::make_shared<Eu::ScenGraph>();
	ChunkManager* m_ChunkManager;
	Eu::TimerManager m_TimerManager;
	
	 std::shared_ptr<Eu::BaseTexture>* m_ptexture;
	 std::shared_ptr<Eu::BaseTexture>* m_pCrosshairTexture;

	Eu::PerspectiveCameraController m_Camera;
};


class Sandbox : public Eu::Application
{
public:
	Sandbox()
	{

		PushLayer(new MineCraftLayer);


	}
	~Sandbox()
	{
		
	}

		
};

Eu::Application* Eu::CreateApplication()
{
	return new Sandbox();
}