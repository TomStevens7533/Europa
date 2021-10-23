#pragma once
#include <glm/vec3.hpp> // glm::vec3
#include <glm/mat4x4.hpp> // glm::mat4

namespace Eu {
	class Camera final
	{
	public:
		Camera(glm::vec3 pos, float fovAngle, float width, float height);
		void Update(float elapsedSec);
		const float GetFOV() const;
		const glm::vec3& GetPos() const;
		glm::mat4 GetInverseONBMatrix();
		const glm::mat4& GetProjectionMatrix() const;
		void SwitchRenderStateFlag();

		void InputHandling();


	private:
		void CalculateInverseONB();
		void CalculateProjectionMatrix(float farPlane, float nearPlane);
		void CalculateView();
		void CalculateModel();


private:
		float m_FOV;
		float m_FOVAngle;
		float m_CameraMovementSpeed{ 50.f };
		float m_CameraZoomInSpeed{ 20.f };
		float m_RotationSpeed{ 4.f };
		glm::vec3 m_Pos;

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


		bool m_IsCameraUpdated;


	};

}
