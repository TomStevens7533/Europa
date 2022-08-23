 #pragma once
#include "Europa/Core/TimeStep.h"
#include "Europa/Events/ApplicationEvent.h"
#include "Europa/Events/MouseEvent.h"
#include "Europa/Camera/Camera.h"
#include "../Components/BaseComponent.h"


namespace Eu {


	//wrapper class around the camera(which contains the core data) and manipulate that data on here
	class PerspectiveCameraControllerComponent : public BaseComponent {
	public:
		PerspectiveCameraControllerComponent(float fov = 60.f);
		void SetNewPosition(glm::vec3 cameraPos); 
		void OneEvent(Event& e);


		void Start() override;
		void Update() override;
		void FixedUpdate() override {};
		void Render() const override {};

		Camera& GetCamera() { return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_FOV;
		bool m_UpdateNeeded{ true };
		Camera m_Camera;

		bool m_IsFirstUpdate;
		glm::vec2 m_OldScreenPos;
		glm::vec2 m_ScreenPosOffset;
		glm::vec3 m_CameraRot{};




		float m_sensitivity = 3.f;
		//variables
		float m_CameraMovementSpeed{ 5.5f };
		float m_RotationSpeed{ 45.f };

	};
}