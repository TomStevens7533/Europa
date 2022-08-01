#include "Camera.h"
#include <ostream>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include <Europa/KeyMouseCodes.h>


namespace Eu {
	Camera::Camera()
	{
		m_ViewProjMatrix = glm::mat4(1.0);
		m_ForwardVector = { 0,0,1 };
	}
	const glm::mat4& Camera::GetViewProjectionMatrix() const
	{
		return m_ViewProjMatrix;
	}

	const glm::mat4& Camera::GetProjectionMatrix() const
	{
		return m_Proj;
	}



	void Camera::CalculateView() {
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
		m_ViewProjMatrix = m_Proj * m_View;
		
	}

	void Camera::CalculateProjectionMatrix(float fov, float aspectRatio)
	{

		m_Proj = glm::perspective(glm::radians(fov / 2.f), aspectRatio, m_NearPlane, m_FarPlane);

	}



	void Camera::SetRotation(glm::vec2 rotationVec)
	{
		m_CameraRot = rotationVec;
		CalculateInverseONB();
	}

	void Camera::SetPosition(glm::vec3 position)
	{
		m_CameraPos = position;
		CalculateInverseONB();
	}

	void Camera::AddPosition(glm::vec3 position)
	{
		m_CameraPos += position;
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


