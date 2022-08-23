#pragma once
#include <glm/glm.hpp>

namespace Eu {
	class Camera final
	{
	public:
		Camera();
		const glm::mat4& GetViewProjectionMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;


		void CalculateProjectionMatrix(float fov, float aspectRatio = 1.77f);
		void SetViewMatrix(glm::mat4x4 view);
		glm::mat4x4& GetONB();
private:
		void CalculateInverseONB();

private:
		float m_FarPlane = 1000.f;
		float m_NearPlane = 0.1f;

		glm::mat4 m_ViewProjMatrix{};
		glm::mat4 m_Proj{};
		glm::mat4 m_View{};


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
