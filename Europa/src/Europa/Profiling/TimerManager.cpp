#include "TimerManager.h"

namespace Eu {

	TimerManager::~TimerManager()
	{
		ClearTimerResults();
	}

	const Timer* TimerManager::AddTimer(const char* name)
	{
		auto addedPair = m_RunningTimers.insert(std::make_pair(name, Timer{ name }));
		return &(*addedPair.first).second;
	}

	void TimerManager::StopTimer(const Timer* timerToStop)
	{
		auto it = m_RunningTimers.find(timerToStop->GetName());

		if (it != m_RunningTimers.end()) {
			TimerResult timerResult = ((*it).second.StopTimer());
			m_TimerResults.push_back(timerResult);

			m_RunningTimers.erase(timerToStop->GetName());
		}

	}

	void TimerManager::StopTimer(const char* name)
	{
		auto it = m_RunningTimers.find(name);

		if (it != m_RunningTimers.end()) {
			TimerResult timerResult = (*it).second.StopTimer();
			m_TimerResults.push_back(timerResult);

			m_RunningTimers.erase(name);
		}
		
	}

	void TimerManager::StopAllTimers()
	{
		for (auto& timerPair : m_RunningTimers)
		{
			m_TimerResults.push_back(timerPair.second.StopTimer());
			m_RunningTimers.erase(timerPair.second.GetName());
		}
	}

	void TimerManager::ClearTimerResults()
	{
		m_TimerResults.clear();
	}

	void TimerManager::ClearRunningTimer()
	{
		m_RunningTimers.clear();
	}

}