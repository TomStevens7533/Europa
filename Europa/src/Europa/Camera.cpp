#include "Camera.h"
#include <ostream>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <Europa/KeyMouseCodes.h>
#include "Input.h"

namespace Eu {
	Camera::Camera(glm::vec3 pos, float fovAngle, float width, float height) : m_Pos{ pos }, m_FOVAngle{ fovAngle }, m_Width{ width }, m_Height{ height }
	{
		m_ONB = glm::mat4(1.0);
		m_ForwardVector = { 0,0,1 };
		m_FOV = glm::radians(fovAngle) / 2.f;
		
		m_Pitch = 0;
		m_Yaw = 0;

		CalculateInverseONB();

	}
	void Camera::Update(float elapsedSec)
	{



	}

	const float Camera::GetFOV() const
	{
		return m_FOV;
	}

	const glm::vec3& Camera::GetPos() const
	{
		return m_Pos;
	}


	glm::mat4 Camera::GetInverseONBMatrix()
	{
		CalculateInverseONB();
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

	void Camera::InputHandling()
	{
		glm::vec2 dragDiffernce = Input::GetMouseDrag(EU_MOUSE_BUTTON_2);

		if (dragDiffernce != glm::vec2{0, 0}) {
			m_CameraRot.x += dragDiffernce.x * 0.01f;
			m_CameraRot.y += dragDiffernce.y * 0.01f;

		}

		if (Input::IsKeyPressed(EU_KEY_D))
			m_CameraPos += m_RightVector *0.01f;
		if (Input::IsKeyPressed(EU_KEY_A))
			m_CameraPos -= m_RightVector * 0.01f;
		if(Input::IsKeyPressed(EU_KEY_W))
			m_CameraPos -= m_ForwardVector *0.01f;
		if (Input::IsKeyPressed(EU_KEY_S))
			m_CameraPos += m_ForwardVector * 0.01f;
		if (Input::IsKeyPressed(EU_KEY_SPACE))
			m_CameraPos += m_UpVector * 0.01f;
		if (Input::IsKeyPressed(EU_KEY_C))
			m_CameraPos -= m_UpVector *0.01f;
	}

	void Camera::CalculateView() {
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, m_CameraPos);
		glm::mat4 rot = glm::mat4(1.0f);
		rot = glm::rotate(rot, glm::radians(m_CameraRot.x), { 0,1,0 });

		rot = glm::rotate(rot, glm::radians(m_CameraRot.y), { -1,0,0 });

		

		m_View = view * rot;

		m_ForwardVector = m_View[2];
		m_RightVector = m_View[0];
		m_UpVector = m_View[1];

		m_View = glm::inverse(m_View);
	}
	void Camera::CalculateModel() {

		m_Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	}
	void Camera::CalculateInverseONB()
	{	
		CalculateView();
		CalculateModel();
		CalculateProjectionMatrix(100.f, 0.1f);
		m_ONB = m_Proj * m_View;
	}

	void Camera::CalculateProjectionMatrix(float farPlane, float nearPlane)
	{
		float aspectRatio = float(m_Width) / float(m_Height);

		m_Proj = glm::perspective(m_FOV, aspectRatio, nearPlane, farPlane);

	}
}


