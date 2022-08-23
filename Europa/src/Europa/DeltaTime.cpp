#include "DeltaTime.h"

namespace Eu {
	std::shared_ptr<Eu::Time> Time::m_TimeSingleton;

	Time::Time()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}
	std::shared_ptr<Eu::Time> Time::GetInstance()
	{
		if (m_TimeSingleton == nullptr) {
			//create singleton
			m_TimeSingleton = std::make_shared<Time>();
		}
		return m_TimeSingleton;
	}
	float Time::GetDeltaTime()
	{
		return m_DeltaTime;
	}
	void Time::Update()
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		m_DeltaTime = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - m_StartTime).count();
		m_StartTime = currentTime;
	}


}