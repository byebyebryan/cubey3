#pragma once

#include <stdint.h>
#include <atomic>

#include "Utilities.h"

namespace cubey3 {
	
	const size_t kIDGeneratorStreamCount = 100;
	const size_t kIDGeneratorDefaultStream = kIDGeneratorStreamCount / 2;
	const size_t kIDGeneratorStreamSize = SIZE_MAX / kIDGeneratorStreamCount;

	class IDGenerator {
	public:

		template <typename T, size_t StreamID = kIDGeneratorDefaultStream>
		static size_t NextID() {
			std::atomic_size_t current_id_ = 0;
			size_t new_id = (++current_id_) + StreamID * kIDGeneratorStreamSize;
			Assert2(current_id_ < kIDGeneratorStreamSize, "IDGenerator overflow.");
			return new_id;
		}
	};
}
