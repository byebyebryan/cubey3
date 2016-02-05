#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>

#include "Utilities/Types.h"
#include "IService.h"

namespace cubey3 {
	const std::string kMainThreadName = "Main Thread";
	const std::string kNullThreadName = "Null Thread";

	using ThreadID = std::thread::id;

	struct ThreadInfo {
		ThreadInfo() :
			name_(kNullThreadName),
			should_stop_(false) {
		}

		ThreadInfo(const std::string& name) :
			name_(name),
			should_stop_(false) {
		}

		ThreadInfo(const std::string& name, std::thread& thread) :
			name_(name),
			thread_(std::move(thread)),
			should_stop_(false) {
		}

		ThreadInfo(ThreadInfo&& other) :
			name_(other.name_),
			thread_(std::move(other.thread_)),
			should_stop_(other.should_stop_.load()) {
		}

		std::string name_;
		std::thread thread_;
		std::atomic_bool should_stop_;
	};

	class ThreadManager : public IService<ThreadManager> {
	public:
		void OnCreate() override;
		void OnDestroy() override;

		template<class ThreadF, class... ArgTs>
		void LaunchThread(const std::string& name, ThreadF&& f, ArgTs... args) {
			SimpleLock lock(mutex_);
			std::thread thread(f, args...);
			ThreadID id = thread.get_id();
			threads_.emplace(id, ThreadInfo(name, thread));
		}

		size_t GetThreadCount() const {
			return threads_.size();
		}

		static size_t GetHardwareThreadCount() {
			return std::thread::hardware_concurrency();
		}

		ThreadInfo& GetThreadInfo(ThreadID id = std::this_thread::get_id()) {
			SimpleLock lock(mutex_);
			return threads_[id];
		}

	private:
		std::unordered_map<std::thread::id, ThreadInfo> threads_;

		std::mutex mutex_;
	};
}