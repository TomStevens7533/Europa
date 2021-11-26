#pragma once
#include <glm/glm.hpp>

namespace Eu {
	class Ray
	{
	public:
		Ray(glm::vec3 startPos, glm::vec3 dirVec, float distance = FLT_MAX);
		void Step(float stepPercentage);
		void StepBack(float stepPercentage);

		inline glm::vec3 GetCurrentPos() { return m_CurrentPos; }
		inline float GetCurrentPercent() { return m_StepPercent; }
	private:
		glm::vec3 m_StartPosition;
		glm::vec3 m_CurrentPos;
		glm::vec3 m_DirectionVector;
		glm::vec3 m_EndPosition;
		float m_Distance;
		float m_StepPercent = 0.f;

	};


}
