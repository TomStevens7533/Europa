#include "TestLayer.h"
#include "Europa/GameObject.h"
#include "Europa/Components/MeshComponent.h"
#include "Europa/Components/MeshRenderComponent.h"
#include "Europa/Renderer/Renderer.h"
#include "../MaterialManager.h"
#include "../BaseMaterial/PosTexCol3D.h"
#include <memory>
using namespace Eu;
TestLayer::TestLayer() : m_Camera{60.f}
{

}

void TestLayer::OnAttach()
{
	auto carGo = new GameObject();
	auto meshComponent = std::make_shared<MeshComponent>("Resources/vehicle.obj");
	carGo->AddComponent<MeshComponent>(meshComponent);
	auto meshRenderComponent = std::make_shared<MeshRenderComponent>();
	carGo->AddComponent<MeshRenderComponent>(meshRenderComponent);

	MaterialManager::GetInstance()->CreateMaterial<PosTexCol3D>();
	m_LayerSceneGraph.AddItemToSceneGraph(carGo);
	m_LayerSceneGraph.StartScene();
}

void TestLayer::OnDetach()
{

}

void TestLayer::OnUpdate(Eu::TimeStep deltaTime)
{
	m_Camera.OnUpdate(deltaTime);
	//Renderer::EnableWireFrame();
	RenderCommand::SetClearColor({ 0.f, 0.3f, 0.8f, 1.f });
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

