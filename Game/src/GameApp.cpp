#include <Europa.h>
#include "MincecraftGO.h"

#include "VLD/include/vld.h"

class MineCraftLayer : public Eu::Layer {
public:
	
		MineCraftLayer() : Layer("we love mc"), m_Camera(glm::vec3{ 0,0, 10 }, 60) {


			Chunk* newChunl = new Chunk;
		

			Eu::SkyBox* newSkyBox{ new 	Eu::SkyBox };
			newSkyBox->AddTexture("Resources/skybox/skybox");


			m_pScene->AddItemToSceneGraph(newChunl);
			m_pScene->AddItemToSceneGraph(newSkyBox);
		}

	void OnAttach() override
	{
	}


	void OnDetach() override
	{
	}


	void OnUpdate(Eu::TimeStep deltaTime) override
	{

		Eu::RenderCommand::Clear();
		Eu::Renderer::BeginScene(m_Camera);


		m_pScene->RenderScene();
		//

		Eu::Renderer::EndScene();

		m_Camera.KeyInputHandling(deltaTime);
		m_Camera.Update(0.1f);
	}


	void OnEvent(Eu::Event& event) override
	{
		if (event.GetEventType() == Eu::EventType::MouseMoved) {
			Eu::MouseMovedEvent* mouseEvent = dynamic_cast<Eu::MouseMovedEvent*>(&event);
			m_Camera.MouseInputHandling({ mouseEvent->GetX(), mouseEvent->GetY() });
		}
		if (event.GetEventType() == Eu::EventType::WindowResize) {
			m_Camera.RecalcProjection();
		}

		if (event.Handled)
			return;

		
	}


	void OnImGuiRender() override
	{
	}
private:
	std::shared_ptr<Eu::ScenGraph> m_pScene = std::make_shared<Eu::ScenGraph>();

	Eu::Camera m_Camera;

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