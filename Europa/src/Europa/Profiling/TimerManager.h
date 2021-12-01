#pragma once
#include "Timer.h"
#include <vector>

namespace Eu {

	class TimerManager final {
	public:
		TimerManager() = default;
		~TimerManager();

		const Timer* AddTimer(const char* name);
		void StopTimer(const Timer* timerToStop);
		void StopTimer(const char* name);
		void ClearTimerResults();
		void ClearRunningTimer();
		inline const std::vector<TimerResult>& GetTimerResults() { return m_TimerResults; }
	private:
		std::vector<Timer> m_RunningTimers;
		std::vector<TimerResult> m_TimerResults;
	};

}