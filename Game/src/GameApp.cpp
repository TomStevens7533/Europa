#include <Europa.h>
#include "MincecraftGO.h"

#include "VLD/include/vld.h"

class MineCraftLayer : public Eu::Layer {
public:
	
		MineCraftLayer() : Layer("we love mc"), m_Camera(60.f) {


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
		m_Camera.OnUpdate(deltaTime);

		Eu::RenderCommand::Clear();
		Eu::Renderer::BeginScene(m_Camera.GetCamera());


		m_pScene->RenderScene();
		

		Eu::Renderer::EndScene();

	}


	void OnEvent(Eu::Event& event) override
	{

		m_Camera.OneEvent(event);
	}


	void OnImGuiRender() override
	{
	}
private:
	std::shared_ptr<Eu::ScenGraph> m_pScene = std::make_shared<Eu::ScenGraph>();

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