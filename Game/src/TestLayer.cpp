#include "TestLayer.h"
#include "Europa/GameObject.h"
#include "Europa/Components/MeshComponent.h"
#include "Europa/Components/MeshRenderComponent.h"
#include "Europa/Renderer/Renderer.h"
#include <memory>
#include "Europa/Material/MaterialManager.h"
#include "BaseMaterial/PosTexCol3D.h"
using namespace Eu;
TestLayer::TestLayer() : m_Camera{60.f}
{

}
//MEED UPDATE  BECAUSE CAMERA IS NOW COMPONENT
void TestLayer::OnAttach()
{
	auto carGo = std::make_shared<GameObject>();
	auto meshComponent = std::make_shared<MeshComponent>("Resources/vehicle.obj");
	carGo->AddComponent<MeshComponent>(meshComponent);
	auto meshRenderComponent = std::make_shared<MeshRenderComponent>();
	carGo->AddComponent<MeshRenderComponent>(meshRenderComponent);
	auto posMat = MaterialManager::GetInstance()->CreateMaterial<PosTexCol3D>();
	m_LayerSceneGraph.AddItemToSceneGraph(carGo);
	meshRenderComponent->SetMaterial(posMat);

	m_LayerSceneGraph.StartScene();
	go = carGo;

}

void TestLayer::OnDetach()
{

}

void TestLayer::OnUpdate(Eu::TimeStep deltaTime)
{
	m_Rotation += glm::vec3{ 0.0001,0.0002,0 };
	m_Translation += glm::vec3{ 0.1,0.02,0 };
	go->GetTransform().Translate(m_Translation);
	go->GetTransform().Rotate(m_Rotation);
	




	//Renderer::EnableWireFrame();
	RenderCommand::SetClearColor({ 1.f, 1.f, 0.9f, 1.f });
	RenderCommand::Clear();


	Renderer::BeginScene(m_Camera.GetCamera());

	m_LayerSceneGraph.UpdateScene();
	m_LayerSceneGraph.RenderScene();
	Renderer::BeginScene(m_Camera.GetCamera());

}

void TestLayer::OnEvent(Eu::Event& event)
{
	m_Camera.OneEvent(event);
}

void TestLayer::OnImGuiRender()
{

}

