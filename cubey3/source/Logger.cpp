#include "Service/Logger.h"

#include "Service/TimeManager.h"
#include "Service/ThreadManager.h"

namespace cubey3 {

	void Logger::LogToConsole(const std::string& message) {
		SimpleLock lock(console_mutex_);
		std::cout << TimeManager::GetTimeString() + " - " + ThreadManager::GetService()->GetThreadInfo().name_ + " - " + message + "\n";
	}
}
