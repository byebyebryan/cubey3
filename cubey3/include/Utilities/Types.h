#pragma once

#include <mutex>

namespace cubey3 {
	typedef std::lock_guard<std::mutex> SimpleLock;
	typedef std::unique_lock<std::mutex> Lock;

	typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;
	typedef std::chrono::time_point<std::chrono::system_clock> SystemTimePoint;

	typedef std::chrono::seconds Seconds;
	typedef std::chrono::milliseconds MilliSeconds;

	typedef std::thread::id ThreadID;
}
