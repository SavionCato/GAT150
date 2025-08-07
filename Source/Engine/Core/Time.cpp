#include "Time.h"

namespace Rex {
	void Time::Tick()
	{
		clock::time_point now = clock::now();
		s_time = std::chrono::duration<float>(now - s_startTime).count();
		s_deltaTime = std::chrono::duration<float>(now - s_frameTime).count();
		s_frameTime = now;
	}
}
