#pragma once

#include <assert.h>
#include <string>
#include <iostream>

namespace cubey3 {
	inline bool ReturnFalse() {
		return false;
	}

	inline void Assert2(bool _cond, const std::string& _error_msg) {
		if (!_cond) {
			std::cout << "Assertion message: " << _error_msg << std::endl;
			assert(false);
		}
	}
}