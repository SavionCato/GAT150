#pragma once
#include <chrono>

namespace Rex {
	class Time {
	private:
		using clock = std::chrono::high_resolution_clock;

	public:
		Time() {
			s_startTime = clock::now();
			s_frameTime = clock::now();
		}

		void Tick();
		void Reset() { s_startTime = clock::now(); }

		float GetTime() const { return s_time; }
		float GetDeltaTime() const { return s_deltaTime * s_timeScale; }

		void SetTimeScale(float timeScale) { s_timeScale = timeScale; }

	private:
		float s_time = 0;
		float s_deltaTime = 0;
		float s_timeScale = 1;

		clock::time_point s_startTime;
		clock::time_point s_frameTime;
	};
}