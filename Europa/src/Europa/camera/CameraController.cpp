#include "CameraController.h"
#include "Europa/Input.h"
#include <Europa/KeyMouseCodes.h>
#include <glm/glm.hpp>
#include "../GameObject.h"
#include "../DeltaTime.h"

namespace Eu {
	PerspectiveCameraControllerComponent::PerspectiveCameraControllerComponent(float fov) : m_FOV{fov}
	{
	}
	void PerspectiveCameraControllerComponent::Start()
	{
		m_Camera.CalculateProjectionMatrix(m_FOV);
	}



	void PerspectiveCameraControllerComponent::SetNewPosition(glm::vec3 cameraPos)
	{
		GetAttachedGameObject()->SetPosition(cameraPos);
	}

	void PerspectiveCameraControllerComponent::OneEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(EU_BIND_EVENT_FN(PerspectiveCameraControllerComponent::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(EU_BIND_EVENT_FN(PerspectiveCameraControllerComponent::OnMouseMoved));
		dispatcher.Dispatch<WindowResizeEvent>(EU_BIND_EVENT_FN(PerspectiveCameraControllerComponent::OnWindowResized));

	}


	void PerspectiveCameraControllerComponent::Update()
	{
		if (m_UpdateNeeded) {


			auto worldPos = GetAttachedGameObject()->GetTransform().GetPosition();
			auto look = GetAttachedGameObject()->GetTransform().GetForward();
			//EU_CORE_INFO("NEW ROT: X {0}, Y {1}, Z {2}", look.x, look.y, look.z);

			m_Camera.SetViewMatrix((glm::lookAt(worldPos, worldPos + look, glm::vec3{0,1,0})));
			m_UpdateNeeded = false;
		}

		glm::vec3 upVec = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 forwardVec = GetAttachedGameObject()->GetTransform().GetForward();
		glm::vec3 rightVec = glm::normalize(glm::cross(upVec, forwardVec));

		upVec = glm::cross(forwardVec, rightVec);

		glm::vec3 newPos = GetAttachedGameObject()->GetTransform().GetPosition();
		
		auto timeInstance = Time::GetInstance();

		int multiplier = 1;
		if (Input::IsKeyPressed(EU_KEY_LEFT_ALT))
			multiplier++;
		if (Input::IsKeyPressed(EU_KEY_D)) {
			newPos -= rightVec * (timeInstance->GetDeltaTime() * (m_CameraMovementSpeed * multiplier));
			//EU_CORE_INFO("NEW POS: X {0}, Y {1}, Z {2}", newPos.x, newPos.y, newPos.z);
			m_UpdateNeeded = true;
		}
		if (Input::IsKeyPressed(EU_KEY_A)){
			newPos += rightVec * (timeInstance->GetDeltaTime() * (m_CameraMovementSpeed * multiplier));
			//EU_CORE_INFO("NEW POS: X {0}, Y {1}, Z {2}", newPos.x, newPos.y, newPos.z);
			
			m_UpdateNeeded = true;
		}
		if (Input::IsKeyPressed(EU_KEY_W)) {
			newPos += forwardVec * (timeInstance->GetDeltaTime() * (m_CameraMovementSpeed * multiplier));
			//EU_CORE_INFO("NEW POS: X {0}, Y {1}, Z {2}", newPos.x, newPos.y, newPos.z);

			m_UpdateNeeded = true;
		}

		if (Input::IsKeyPressed(EU_KEY_S)) {
			newPos -= forwardVec * (timeInstance->GetDeltaTime() * (m_CameraMovementSpeed * multiplier));
			//EU_CORE_INFO("NEW POS: X {0}, Y {1}, Z {2}", newPos.x, newPos.y, newPos.z);

			m_UpdateNeeded = true;
		}
		if (Input::IsKeyPressed(EU_KEY_SPACE)) {
			newPos += upVec * (timeInstance->GetDeltaTime() * (m_CameraMovementSpeed * multiplier));
			//EU_CORE_INFO("NEW POS: X {0}, Y {1}, Z {2}", newPos.x, newPos.y, newPos.z);

			m_UpdateNeeded = true;
		}
		if (Input::IsKeyPressed(EU_KEY_C)) {
			newPos -= upVec * (timeInstance->GetDeltaTime() * (m_CameraMovementSpeed * multiplier));
			//EU_CORE_INFO("NEW POS: X {0}, Y {1}, Z {2}", newPos.x, newPos.y, newPos.z);

			m_UpdateNeeded = true;

		}

		GetAttachedGameObject()->SetPosition(newPos);
	}

	bool PerspectiveCameraControllerComponent::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_FOV += -e.GetYOffset();
		EU_CORE_INFO("NEW FOV: {0}", m_FOV);
		m_Camera.CalculateProjectionMatrix(m_FOV);
		m_UpdateNeeded = true;
		return true;
	}

	bool PerspectiveCameraControllerComponent::OnMouseMoved(MouseMovedEvent& e)
	{
		if (Input::IsMouseButtonPressed(EU_MOUSE_BUTTON_2)) { //Remove make button configurable
			if (m_IsFirstUpdate)
			{
				m_OldScreenPos.x = e.GetX();
				m_OldScreenPos.y = e.GetY();

				m_IsFirstUpdate = false;
				return true;
			}
			m_ScreenPosOffset = { e.GetX() - m_OldScreenPos.x, e.GetY() - m_OldScreenPos.y };

			m_OldScreenPos.x = e.GetX();
			m_OldScreenPos.y = e.GetY();

			auto timeInstance = Time::GetInstance();
			m_ScreenPosOffset = m_ScreenPosOffset *  (m_sensitivity * timeInstance->GetDeltaTime());

			 
			m_CameraRot.y += m_ScreenPosOffset.x; //yaw rotate x
			m_CameraRot.x += m_ScreenPosOffset.y; //pitch rotate y
			m_CameraRot.z = 0;


			EU_CORE_INFO("ROTATION x {0}, y{1}", m_CameraRot.x, m_CameraRot.y);

			if (m_CameraRot.x > 89.0f)
				m_CameraRot.x = 89.0f;
			if (m_CameraRot.x < -89.0f)
				m_CameraRot.x = -89.0f;

			GetAttachedGameObject()->GetTransform().Rotate(m_CameraRot, true);
			m_UpdateNeeded = true;
			return true;

		}
		m_OldScreenPos.x = e.GetX();
		m_OldScreenPos.y = e.GetY();
		return true;

	}

	bool PerspectiveCameraControllerComponent::OnWindowResized(WindowResizeEvent& e)
	{
		float aspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		m_Camera.CalculateProjectionMatrix(m_FOV, aspectRatio);
		m_UpdateNeeded = true;
		return true;
	}


}
