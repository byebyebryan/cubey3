#include "Service/ThreadManager.h"

namespace cubey3 {
	void ThreadManager::OnCreate() {
		SimpleLock lock(mutex_);
		threads_.emplace(std::this_thread::get_id(), ThreadInfo(kMainThreadName));
	}

	void ThreadManager::OnDestroy() {
		SimpleLock lock(mutex_);
		for (auto& thread : threads_) {
			if(thread.second.thread_.joinable()) {
				thread.second.thread_.join();
			}
		}
	}
}
