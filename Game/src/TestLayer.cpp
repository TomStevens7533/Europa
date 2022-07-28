#include "TestLayer.h"
#include "Europa/GameObject.h"
#include "Europa/Components/MeshComponent.h"
using namespace Eu;
TestLayer::TestLayer() : m_Camera{60.f}
{

}

void TestLayer::OnAttach()
{
	auto carGo = new GameObject();
	auto meshComponent = std::make_shared<MeshComponent>("Resources/vehicle.obj");
	carGo->AddComponent<MeshComponent>(meshComponent);
	m_LayerSceneGraph.AddItemToSceneGraph(carGo);
}

void TestLayer::OnDetach()
{

}

void TestLayer::OnUpdate(Eu::TimeStep deltaTime)
{
	m_LayerSceneGraph.UpdateScene();
	m_LayerSceneGraph.RenderScene();
}

void TestLayer::OnEvent(Eu::Event& event)
{

}

void TestLayer::OnImGuiRender()
{

}

