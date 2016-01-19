#pragma once

#include <stdint.h>
#include <atomic>

#include "Utilities.h"

namespace cubey3 {
	
	class IDGenerator {
	public:
		const static size_t kStreamCount = 100;
		const static size_t kStreamSize = SIZE_MAX / kStreamCount;

		template <typename T, size_t StreamID = 0>
		static size_t NextID() {
			std::atomic_size_t current_id_ = 0;
			size_t new_id = (++current_id_) + StreamID * kStreamSize;
			Assert2(current_id_ < kStreamSize, "IDGenerator overflow.");
			return new_id;
		}
	};
}
