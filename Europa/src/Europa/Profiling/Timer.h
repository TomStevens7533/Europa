#pragma once
#include <chrono>

namespace Eu {


	struct TimerResult {
		const char* Name;
		float Time;
	};

	class Timer {
	public:
		Timer(const char* name);
		~Timer();

		TimerResult StopTimer();
		void ReportTimer() const;
		const char* GetName() const;
		
		bool operator==(Timer& rhs);

	private:
		const char* m_Name;
		float m_DurationInMicroSeconds;
		bool m_Stopped;
		std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
	};

}