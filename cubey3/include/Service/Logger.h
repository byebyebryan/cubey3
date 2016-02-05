#pragma once

#include <iostream>

#include "Utilities/Types.h"
#include "IService.h"

namespace cubey3 {

	class Logger : public IService<Logger> {
	public:
		void LogToConsole(const std::string& message);

	private:
		std::mutex console_mutex_;
	};
}
