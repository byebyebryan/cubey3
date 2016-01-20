#pragma once

#include <assert.h>
#include <string>
#include <iostream>

namespace cubey3 {
	inline bool ReturnFalse() {
		return false;
	}

	inline void Assert2(bool cond, const std::string& error_msg) {
		if (!cond) {
			std::cout << "Assertion message: " << error_msg << std::endl;
			assert(false);
		}
	}
}