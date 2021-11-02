#include "Camera.h"
#include <ostream>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <Europa/KeyMouseCodes.h>
#include "Input.h"

namespace Eu {
	Camera::Camera(glm::vec3 pos, float fovAngle) : m_CameraPos{ pos }, m_FOVAngle{ fovAngle }
	{
		m_ONB = glm::mat4(1.0);
		m_ForwardVector = { 0,0,1 };
		m_FOV = glm::radians(fovAngle) / 2.f;
		
		m_Pitch = 0;
		m_Yaw = 0;


	}
	void Camera::Update(float elapsedSec)
	{

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

	void Camera::KeyInputHandling()
	{
		//glm::vec2 dragDiffernce = Input::GetMouseDrag(EU_MOUSE_BUTTON_2);

		//if (dragDiffernce != glm::vec2{0, 0}) {
		//	m_CameraRot.x -= dragDiffernce.x * 0.01f;
		//	m_CameraRot.y -= dragDiffernce.y * 0.01f;

		//}

		if (Input::IsKeyPressed(EU_KEY_D))
			m_CameraPos += glm::normalize(glm::cross(m_ForwardVector, m_UpVector)) * 0.01f;
		if (Input::IsKeyPressed(EU_KEY_A))
			m_CameraPos -= glm::normalize(glm::cross(m_ForwardVector, m_UpVector)) * 0.01f;
		if(Input::IsKeyPressed(EU_KEY_W))
			m_CameraPos += m_ForwardVector *0.01f;
		if (Input::IsKeyPressed(EU_KEY_S))
			m_CameraPos -= m_ForwardVector * 0.01f;
		if (Input::IsKeyPressed(EU_KEY_SPACE))
			m_CameraPos += m_UpVector * 0.01f;
		if (Input::IsKeyPressed(EU_KEY_C))
			m_CameraPos -= m_UpVector *0.01f;
	}

	void Camera::MouseInputHandling(glm::vec2 mousePos)
	{
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
			//if (m_CameraRot.x >= 88.5f)
			//	m_CameraRot.x = 180.5f;
			//if (m_CameraRot.x <= -88.5f)
			//	m_CameraRot.x = -88.5f;


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
		CalculateProjectionMatrix(1000.f, 0.1f);
		m_ONB = m_Proj * m_View;
		
	}

	void Camera::CalculateProjectionMatrix(float farPlane, float nearPlane)
	{
		float aspectRatio = float(m_Width) / float(m_Height);



		m_Proj = glm::perspective(m_FOV, aspectRatio, nearPlane, farPlane);

	}

	void Camera::SetWidthAndHeight(glm::vec2 widthHeightInfo)
	{
		m_Width = widthHeightInfo.x;
		m_Height = widthHeightInfo.y;
		CalculateInverseONB();

	}

}


