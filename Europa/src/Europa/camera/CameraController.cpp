#include "CameraController.h"
#include "Europa/Input.h"
#include <Europa/KeyMouseCodes.h>
#include <glm/glm.hpp>

namespace Eu {
	PerspectiveCameraController::PerspectiveCameraController(float fov) : m_FOV{fov}
	{
		m_Camera.CalculateProjectionMatrix(m_FOV);
	}

	void PerspectiveCameraController::OnUpdate(TimeStep deltaTime)
	{
		glm::vec3 forwardVec = m_Camera.GetForwardVec();
		glm::vec3 rightVec = m_Camera.GetRightVec();
		glm::vec3 upVec = m_Camera.GetUpVector();
		int multiplier = 1;
		if (Input::IsKeyPressed(EU_KEY_LEFT_ALT))
			multiplier++;
		if (Input::IsKeyPressed(EU_KEY_D))
			m_CameraPos += glm::normalize(glm::cross(forwardVec, upVec)) * (deltaTime.GetSeconds() * (m_CameraMovementSpeed * multiplier));
		if (Input::IsKeyPressed(EU_KEY_A))
			m_CameraPos -= glm::normalize(glm::cross(forwardVec, upVec)) * (deltaTime.GetSeconds() * (m_CameraMovementSpeed * multiplier));
		if (Input::IsKeyPressed(EU_KEY_W))
			m_CameraPos += forwardVec * (deltaTime.GetSeconds() * (m_CameraMovementSpeed * multiplier));
		if (Input::IsKeyPressed(EU_KEY_S))
			m_CameraPos -= forwardVec * (deltaTime.GetSeconds() * (m_CameraMovementSpeed * multiplier));
		if (Input::IsKeyPressed(EU_KEY_SPACE))
			m_CameraPos += upVec * (deltaTime.GetSeconds() * (m_CameraMovementSpeed * multiplier));
		if (Input::IsKeyPressed(EU_KEY_C))
			m_CameraPos -= upVec * (deltaTime.GetSeconds() * (m_CameraMovementSpeed * multiplier));

		m_Camera.SetPosition(m_CameraPos);

	}

	void PerspectiveCameraController::SetNewPosition(glm::vec3 cameraPos)
	{
		m_Camera.SetPosition(cameraPos);
	}

	void PerspectiveCameraController::OneEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(EU_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<MouseMovedEvent>(EU_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
		dispatcher.Dispatch<WindowResizeEvent>(EU_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));

	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_FOV += -e.GetYOffset();
		EU_CORE_INFO("NEW FOV: {0}", m_FOV);
		m_Camera.CalculateProjectionMatrix(m_FOV, m_AspectRatio);
		return true;
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		if (Input::IsMouseButtonPressed(EU_MOUSE_BUTTON_2)) {
			if (m_IsFirstUpdate)
			{
				m_OldScreenPos.x = e.GetX();
				m_OldScreenPos.y = e.GetY();

				m_IsFirstUpdate = false;
			}

			m_ScreenPosOffset = { e.GetX() - m_OldScreenPos.x,m_OldScreenPos.y - e.GetY() };

			m_OldScreenPos.x = e.GetX();
			m_OldScreenPos.y = e.GetY();



			float sensitivity = 0.1f;
			m_ScreenPosOffset.y *= sensitivity;
			m_ScreenPosOffset.x *= sensitivity;

			
			//  screen doesn't get flipped
			if (m_CameraRot.x >= 88.5f)
				m_CameraRot.x = 88.5f;
			if (m_CameraRot.x <= -88.5f)
				m_CameraRot.x = -88.5f;


			m_CameraRot.x += m_ScreenPosOffset.y;
			m_CameraRot.y += m_ScreenPosOffset.x;
			m_Camera.SetRotation(m_CameraRot);
			return true;

		}
		m_OldScreenPos.x = e.GetX();
		m_OldScreenPos.y = e.GetY();
		return true;

	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
		m_Camera.CalculateProjectionMatrix(m_FOV, m_AspectRatio);
		return true;


	}


}
