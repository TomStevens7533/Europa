#pragma once
#include "Timer.h"
#include <vector>
#include <unordered_map>

namespace Eu {

	class TimerManager final {
	public:
		TimerManager() = default;
		~TimerManager();

		const Timer* AddTimer(const char* name);
		void StopTimer(const Timer* timerToStop);
		void StopTimer(const char* name);
		void StopAllTimers();
		void ClearTimerResults();
		void ClearRunningTimer();
		inline const std::vector<TimerResult>& GetTimerResults() { return m_TimerResults; }
	private:
		std::unordered_map<const char*, Timer> m_RunningTimers;
		std::vector<TimerResult> m_TimerResults;
	};

}