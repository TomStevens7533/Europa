#include "Timer.h"
#include "../Log.h"

namespace Eu {


	Timer::Timer(const char* name) : m_Name{name}, m_Stopped{false}
	{
		m_StartPoint = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		if (!m_Stopped)
			StopTimer();
	}

	TimerResult Timer::StopTimer()
	{
		auto endPoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endPoint).time_since_epoch().count();

		m_DurationInMicroSeconds = (end - start) * 0.001f;

		return { m_Name, m_DurationInMicroSeconds };
	}

	void Timer::ReportTimer() const
	{
		EU_CORE_INFO("TIMER('{0}') : MicroSec:{1}", m_Name, m_DurationInMicroSeconds);
	}

	const char* Timer::GetName() const
	{
		return m_Name;
	}

	bool Timer::operator==(Timer& rhs)
	{
		return (rhs.m_StartPoint == this->m_StartPoint);
	}

}