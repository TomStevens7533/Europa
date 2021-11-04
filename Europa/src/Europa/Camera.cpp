#include "Camera.h"
#include <ostream>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <Europa/KeyMouseCodes.h>
#include "Input.h"
#include "Application.h"

namespace Eu {
	Camera::Camera(glm::vec3 pos, float fovAngle) : m_CameraPos{ pos }, m_FOVAngle{ fovAngle }
	{
		m_ONB = glm::mat4(1.0);
		m_ForwardVector = { 0,0,1 };
		m_FOV = glm::radians(fovAngle) / 2.f;
		
		m_Pitch = 0;
		m_Yaw = 0;
		RecalcProjection();



	}
	void Camera::Update(float elapsedSec)
	{
		//RecalcProjection();

		CalculateInverseONB();


	}

	const float Camera::GetFOV() const
	{
		return m_FOV;
	}

	const glm::vec3& Camera::GetPos() const
	{
		return m_CameraPos;
	}


	glm::mat4& Camera::GetInverseONBMatrix()
	{
		return m_ONB;
	}

	const glm::mat4& Camera::GetProjectionMatrix() const
	{
		return m_Proj;
	}
	void Camera::SwitchRenderStateFlag()
	{
		//only happens once when switching
	   /* CalculateProjectionMatrix(100.f, 0.1f);
		CalculateInverseONB(FVector3{ 0,0,0 });*/

	}

	void Camera::KeyInputHandling(TimeStep deltaTime)
	{
		//glm::vec2 dragDiffernce = Input::GetMouseDrag(EU_MOUSE_BUTTON_2);

		//if (dragDiffernce != glm::vec2{0, 0}) {
		//	m_CameraRot.x -= dragDiffernce.x * 0.01f;
		//	m_CameraRot.y -= dragDiffernce.y * 0.01f;

		//}

		if (Input::IsKeyPressed(EU_KEY_D))
			m_CameraPos += glm::normalize(glm::cross(m_ForwardVector, m_UpVector)) * (deltaTime.GetSeconds() * m_CameraMovementSpeed);
		if (Input::IsKeyPressed(EU_KEY_A))
			m_CameraPos -= glm::normalize(glm::cross(m_ForwardVector, m_UpVector)) * (deltaTime.GetSeconds() * m_CameraMovementSpeed);
		if(Input::IsKeyPressed(EU_KEY_W))
			m_CameraPos += m_ForwardVector * (deltaTime.GetSeconds() * m_CameraMovementSpeed);
		if (Input::IsKeyPressed(EU_KEY_S))
			m_CameraPos -= m_ForwardVector *(deltaTime.GetSeconds() * m_CameraMovementSpeed);
		if (Input::IsKeyPressed(EU_KEY_SPACE))
			m_CameraPos += m_UpVector *(deltaTime.GetSeconds() * m_CameraMovementSpeed);
		if (Input::IsKeyPressed(EU_KEY_C))
			m_CameraPos -= m_UpVector * (deltaTime.GetSeconds() * m_CameraMovementSpeed);
	}

	void Camera::MouseInputHandling(glm::vec2 mousePos)
	{
		//TODO REWORK

		if (Input::IsMouseButtonPressed(EU_MOUSE_BUTTON_2)) {
			if (m_IsFirstUpdate)
			{
				m_OldScreenPos.x = mousePos.x;
				m_OldScreenPos.y = mousePos.y;

				m_IsFirstUpdate = false;
			}

			m_ScreenPosOffset = { mousePos.x - m_OldScreenPos.x,m_OldScreenPos.y - mousePos.y };

			m_OldScreenPos.x = mousePos.x;
			m_OldScreenPos.y = mousePos.y;



			float sensitivity = 0.1f;
			m_ScreenPosOffset.y *= sensitivity;
			m_ScreenPosOffset.x *= sensitivity;

			// make sure that when pitch is out of bounds, screen doesn't get flipped
			if (m_CameraRot.x >= 88.5f)
				m_CameraRot.x = 88.5f;
			if (m_CameraRot.x <= -88.5f)
				m_CameraRot.x = -88.5f;


			m_CameraRot.x += m_ScreenPosOffset.y;
			m_CameraRot.y += m_ScreenPosOffset.x;
			return;
		}
		m_OldScreenPos.x = mousePos.x;
		m_OldScreenPos.y = mousePos.y;

	
	}

	void Camera::SetCameraPos(glm::vec3 cameraPos)
	{
		m_CameraPos = cameraPos;
	}

	void Camera::SetCameraOffsetPos(glm::vec3 cameraPos)
	{
		m_CameraPos += cameraPos;
	}

	void Camera::CalculateView() {
		//glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, m_CameraPos);
		//glm::mat4 rot = glm::mat4(1.0f);
		//rot = glm::rotate(rot, glm::radians(m_CameraRot.y), { 0,1,0 }); //yaw

		//rot = glm::rotate(rot, glm::radians(m_CameraRot.x), { 1,0,0 }); //pitch

		m_ForwardVector.x = cos(glm::radians(m_CameraRot.y)) * cos(glm::radians(m_CameraRot.x));
		m_ForwardVector.y = sin(glm::radians(m_CameraRot.x));
		m_ForwardVector.z = sin(glm::radians(m_CameraRot.y)) * cos(glm::radians(m_CameraRot.x));
		m_ForwardVector = glm::normalize(m_ForwardVector);

		//m_View = view * rot;

		m_View = glm::lookAt(m_CameraPos, m_CameraPos + m_ForwardVector, m_UpVector);
	}
	void Camera::CalculateModel() {

		m_Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	}

	void Camera::CalculateInverseONB()
	{	
		CalculateView();
		CalculateModel();
		m_ONB = m_Proj * m_View;
		
	}

	void Camera::CalculateProjectionMatrix(float farPlane, float nearPlane)
	{

		glm::vec2 windowResolution = { Application::Get().GetWindow().GetWidth(),Application::Get().GetWindow().GetHeight() };


		m_AspectRatio = static_cast<float>(windowResolution.x) / static_cast<float>(windowResolution.y);



		m_Proj = glm::perspective(m_FOV, m_AspectRatio, nearPlane, farPlane);

	}

	void Camera::RecalcProjection()
	{
		CalculateProjectionMatrix(1000.f, 0.1f);
		CalculateInverseONB();

	}



	//frustum culling
	//void Camera::CreateFrustumForCamera(float aspectRatio, float zNearPlane = 0.f, float zFarPlane = 1000.f)
	//{
	//	const float halfVSide = zFarPlane * tanf(m_FOV * .5f);
	//	const float halfHSide = halfVSide * m_AspectRatio;
	//	const glm::vec3 frontMultFar = zFarPlane * m_ForwardVector;

	//	m_CurrentFrustum.nearFace = Plan{ glm::vec3{m_CameraPos + zNearPlane * m_ForwardVector}, m_ForwardVector };

	//	m_CurrentFrustum.farFace = Plan{ m_ForwardVector + frontMultFar, -m_ForwardVector };

	//	m_CurrentFrustum.rightFace = Plan{ m_CameraPos,
	//							glm::cross(m_UpVector,frontMultFar + m_RightVector * halfHSide) };

	//	m_CurrentFrustum.leftFace = Plan{ m_CameraPos,
	//							glm::cross(frontMultFar - m_RightVector * halfHSide, m_UpVector) };

	//	m_CurrentFrustum.topFace = Plan{ m_CameraPos,
	//							glm::cross(m_RightVector, frontMultFar - m_UpVector * halfVSide) };

	//	m_CurrentFrustum.bottomFace = Plan{ m_CameraPos,
	//							glm::cross(frontMultFar + m_UpVector * halfVSide, m_RightVector) };
	//}
}


