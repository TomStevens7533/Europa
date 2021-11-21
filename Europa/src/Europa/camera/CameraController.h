#pragma once
#include "Europa/Core/TimeStep.h"
#include "Europa/Events/ApplicationEvent.h"
#include "Europa/Events/MouseEvent.h"
#include "Europa/Camera/Camera.h"


namespace Eu {


	//wrapper class around the camera(which contains the core data) and manipulate that data on here
	class PerspectiveCameraController {
	public:
		PerspectiveCameraController(float fov = 60.f);
		void OnUpdate(TimeStep deltaTime);
		void SetNewPosition(glm::vec3 cameraPos); 
		void OneEvent(Event& e);
		inline const Camera& GetCamera() { return m_Camera; }
		inline const glm::vec3 GetCamerPos() { return m_CameraPos; }
		inline const glm::vec3& GetForwardVector() { return m_Camera.GetForwardVec(); }


	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_FOV;
		Camera m_Camera;

		bool m_IsFirstUpdate;
		glm::vec3 m_CameraPos{ 0,150,0 };
		glm::vec2 m_OldScreenPos;
		glm::vec2 m_ScreenPosOffset;
		glm::vec2 m_CameraRot{0,0};


		//variables
		float m_CameraMovementSpeed{ 5.5f };
		float m_RotationSpeed{ 45.f };

	};
}