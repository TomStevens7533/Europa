#include "Utils.h"
#include <Europa/Core.h>
#include "Europa/Log.h"

namespace Eu {
	Ray::Ray(glm::vec3 startPos, glm::vec3 dirVec, float distance /*= FLT_MAX*/) : m_StartPosition{ startPos }, m_DirectionVector{ dirVec }, m_Distance{distance}
	{
		m_CurrentPos = m_StartPosition;
		m_EndPosition = m_StartPosition * (m_DirectionVector * m_Distance);
	}

	void Ray::Step(float stepPercentage)
	{
		//EU_CORE_ASSERT(m_StepPercent > 1.f, {"RAY ALREADY OUT OF BOUNDS"});
		//EU_CORE_ASSERT({ "RAY GOING OUT OF BOUNDS" }, m_StepPercent + stepPercentage > 1.f);
		m_StepPercent += stepPercentage;

		m_CurrentPos = m_StartPosition + (m_DirectionVector * (m_Distance * m_StepPercent));

	}

	void Ray::StepBack(float stepPercentage)
	{
		EU_ASSERT(stepPercentage < 0, "percentage needs to be below 0 to step back");
		m_StepPercent += stepPercentage;
		m_CurrentPos = m_StartPosition + (m_DirectionVector * ((m_Distance * 1) * std::abs(1 + m_StepPercent)));
	}

}

