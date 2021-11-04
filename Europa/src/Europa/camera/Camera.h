#pragma once
#include <glm/glm.hpp>

namespace Eu {
	class Camera final
	{
	public:
		Camera();
		const glm::mat4& GetViewProjectionMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;

		
		inline glm::vec3& GetForwardVec() { return m_ForwardVector; }
		inline glm::vec3& GetRightVec() { return m_RightVector; }
		inline glm::vec3& GetUpVector() { return m_UpVector; }

		void CalculateProjectionMatrix(float fov, float aspectRatio = 1.77f);
		void SetRotation(glm::vec2 rotationVec);
		void SetPosition(glm::vec3 position);

	private:
		void CalculateInverseONB();
		void CalculateView();
		void CalculateModel();


private:
		float m_CameraZoomInSpeed{ 2.f };
		float m_RotationSpeed{ 45.f };



		float m_FarPlane = 1000.f;
		float m_NearPlane = 0.1f;

		glm::mat4 m_ViewProjMatrix;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::mat4 m_Model;


		glm::vec3 m_ForwardVector{ 0, 0, -1 };
		glm::vec3 m_RightVector{-1,0,0};
		glm::vec3 m_UpVector{0,1,0};



		//camera movement
		glm::vec2 m_OldScreenPos;
		glm::vec2 m_ScreenPosOffset;
		bool m_IsFirstUpdate = false;
		glm::vec2 m_CameraRot{ 1.f,0};
		glm::vec3 m_CameraPos = {0,0,0};





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
