#include <Service/TimeManager.h>

#include <time.h>


namespace cubey3 {
	void TimeManager::StartUp() {
		start_time_point_ = GetCurrentTimePoint();
		start_system_time_point_ = GetCurrentSystemTimePoint();
	}

	TimePoint TimeManager::GetCurrentTimePoint() {
		return std::chrono::high_resolution_clock::now();
	}

	SystemTimePoint TimeManager::GetCurrentSystemTimePoint() {
		return std::chrono::system_clock::now();
	}

	std::string TimeManager::GetTimeString(const SystemTimePoint& _system_time_point, const std::string& _format) {
		time_t raw_time = std::chrono::system_clock::to_time_t(_system_time_point);
		tm time_info;
		localtime_s(&time_info, &raw_time);

		char buffer[80];
		strftime(buffer, 80, _format.c_str(), &time_info);

		return std::string(buffer);
	}

	std::string TimeManager::GetCurrentTimeString(const std::string& _format) {
		SystemTimePoint current_time = GetCurrentSystemTimePoint();
		return GetTimeString(current_time, _format);
	}

}
