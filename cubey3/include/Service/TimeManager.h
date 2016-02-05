#pragma once

#include <string>
#include <chrono>

#include "Utilities/Types.h"
#include "IService.h"

namespace cubey3 {
	const std::string kDefaultTimeFormat = "%Y/%m/%d_%X";

	class TimeManager : public IService<TimeManager> {
	public:
		void OnCreate() override;

		double GetElapsedTime(TimePoint start_time_point) const;
		double GetElapsedTime() const;

		static TimePoint GetCurrentTimePoint();
		static SystemTimePoint GetCurrentSystemTimePoint();

		static std::string GetTimeString(const SystemTimePoint& _system_time_point = GetCurrentSystemTimePoint(), const std::string& _format = kDefaultTimeFormat);
		static std::string GetCurrentTimeString(const std::string& _format = kDefaultTimeFormat);

	private:
		TimePoint start_time_point_;
		SystemTimePoint start_system_time_point_;
	};
}


