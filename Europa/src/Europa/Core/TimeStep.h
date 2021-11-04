#pragma once

namespace Eu {
	class TimeStep
	{
	public:
		inline TimeStep(float time = 0.f) : m_Time{ time }
		{

		}
		inline float GetSeconds() const { return m_Time; }
		inline float GetMilliseconds() const { return m_Time * 1000.f; }
		//TODO overload operators to make time management easy
	private:
		float m_Time;
	};
}