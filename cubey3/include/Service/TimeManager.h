#pragma once

#include <string>
#include <chrono>

#include "IService.h"

namespace cubey3 {
	const std::string kDefaultTimeFormat = "%Y/%m/%d_%X";

	using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
	using SystemTimePoint = std::chrono::time_point<std::chrono::system_clock>;

	class TimeManager : public IService<TimeManager> {
	public:
		void OnCreate() override;

		static double GetElapsedTime();

		static TimePoint GetCurrentTimePoint();
		static SystemTimePoint GetCurrentSystemTimePoint();

		static std::string GetTimeString(const SystemTimePoint& _system_time_point, const std::string& _format = kDefaultTimeFormat);
		static std::string GetCurrentTimeString(const std::string& _format = kDefaultTimeFormat);

	private:
		TimePoint start_time_point_;
		SystemTimePoint start_system_time_point_;
	};
}


