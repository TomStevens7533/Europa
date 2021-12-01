#include "TimerManager.h"

namespace Eu {

	TimerManager::~TimerManager()
	{
		ClearTimerResults();
	}

	const Timer* TimerManager::AddTimer(const char* name)
	{
		return &m_RunningTimers.emplace_back(name);
	}

	void TimerManager::StopTimer(const Timer* timerToStop)
	{
		auto it = std::find_if(m_RunningTimers.begin(), m_RunningTimers.end(), [&timerToStop](Timer& tr) {
			return timerToStop->GetName() == tr.GetName();
			});
		
		m_TimerResults.push_back(it->StopTimer());

		m_RunningTimers.erase(it);

	}

	void TimerManager::StopTimer(const char* name)
	{
		auto it = std::find_if(m_RunningTimers.begin(), m_RunningTimers.end(), [&name](Timer& tr) {
			return name == tr.GetName();
			});

		m_TimerResults.push_back(it->StopTimer());

		m_RunningTimers.erase(it);
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