#pragma once
#include <glm/glm.hpp>
#include "Core/TimeStep.h"

namespace Eu {
	class Camera final
	{
	public:
		Camera(glm::vec3 pos, float fovAngle);
		void Update(float elapsedSec);
		const float GetFOV() const;
		const glm::vec3& GetPos() const;
		glm::mat4& GetInverseONBMatrix();
		const glm::mat4& GetProjectionMatrix() const;
		void SwitchRenderStateFlag();

		void KeyInputHandling(TimeStep deltaTime);
		void MouseInputHandling(glm::vec2 mousePos);
		void SetCameraPos(glm::vec3 cameraPos);
		void SetCameraOffsetPos(glm::vec3 cameraPos);
		void RecalcProjection();



	private:
		void CalculateInverseONB();
		void CalculateProjectionMatrix(float farPlane, float nearPlane);
		void CalculateView();
		void CalculateModel();


private:
		float m_FOV;
		float m_FOVAngle;
		float m_AspectRatio;
		float m_CameraMovementSpeed{ 2.5f };
		float m_CameraZoomInSpeed{ 2.f };
		float m_RotationSpeed{ 45.f };

		float m_Width;
		float m_Height;


		float m_Yaw;
		float m_Pitch;

		glm::mat4 m_ONB{};
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;


		glm::vec3 m_ForwardVector{ 0, 0, -1 };
		glm::vec3 m_RightVector{-1,0,0};
		glm::vec3 m_UpVector{0,1,0};
		glm::vec3 m_WorldUp{};

		glm::vec3 m_CameraPos{0,0,10};
		glm::vec3 m_CameraRot{ 1.f,0, 0 };

		//camera movement
		glm::vec2 m_OldScreenPos;
		glm::vec2 m_ScreenPosOffset;
		bool m_IsFirstUpdate = false;


		bool m_IsCameraUpdated;

		//Camera Frustum
		//void CreateFrustumForCamera(float aspectRatio, float zNearPlane = 0.f, float zFarPlane = 1000.f);
		//Frustum m_CurrentFrustum;



	};
	//FRUSTUM CULLING
	//struct Plan
	//{ // unit vector
	//	Plan(glm::vec3 normal, float distance) : m_Normal{normal}, m_DistanceFromOrigin{distance}
	//	{

	//	}
	//	float m_DistanceFromOrigin = 0.f;
	//	glm::vec3 m_Normal = { 0.f, 1.f, 0.f };

	//};
	//struct Frustum
	//{
	//	Plan topFace;
	//	Plan bottomFace;

	//	Plan rightFace;
	//	Plan leftFace;

	//	Plan farFace;
	//	Plan nearFace;
	//};

}
