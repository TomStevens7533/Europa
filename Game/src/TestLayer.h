#pragma once
#include "Europa/Profiling/TimerManager.h"
#include "Europa/camera/CameraController.h"
#include "Europa/Layer.h"
#include "Europa/Scenegraph.h"

class TestLayer : public Eu::Layer
{
public:
	TestLayer();
	virtual ~TestLayer() {};


	void OnAttach() override;


	void OnDetach() override;


	void OnUpdate(Eu::TimeStep deltaTime) override;


	void OnEvent(Eu::Event& event) override;


	void OnImGuiRender() override;

private:
	Eu::TimerManager m_TimerManager;
	Eu::ScenGraph m_LayerSceneGraph;
	Eu::GameObject* go;
	glm::vec3 m_Rotation{};
	Eu::PerspectiveCameraController m_Camera;

};

