#pragma once

#include <unordered_map>

#include "IService.h"
#include "ThreadManager.h"
#include "TimeManager.h"
#include "RepeatingTask.h"
#include "Utilities.h"

namespace cubey3 {
	const size_t kDefaultSchedulerInterval = 100;

	class TaskScheduler : public IService<TaskScheduler> {
	public:
		void Init() override {
			std::lock_guard<std::mutex> lock(mutex_);
			interval_ = std::chrono::milliseconds(kDefaultSchedulerInterval);
			stop_signal_received_ = false;
			ThreadManager::GetInstance()->LaunchThread("TaskScheduler Thread",&TaskScheduler::ThreadWorker, this);
		}

		void Destroy() override {
		}

		void UnscheduleAllTask() {
			std::lock_guard<std::mutex> lock(mutex_);
			stop_signal_received_ = true;
		}

		UID ScheduleRepeatingTask(size_t _interval_ms, std::function<void()> _process_fn, std::function<bool()> _override_trigger_fn = ReturnFalse) {
			std::lock_guard<std::mutex> lock(mutex_);
			UID id = IDGenerator<TaskScheduler>::NextID();
			TimePoint now = TimeManager::GetInstance()->GetCurrentTimePoint();
			std::chrono::milliseconds interval(_interval_ms);
			TimePoint next_run_time = now + interval;
			schedules_.emplace(std::make_pair(id, RepeatingTask{id, interval, now, next_run_time, _process_fn, _override_trigger_fn}));
			return id;
		}

		void UnscheduleRepeatingTask(UID _task_id) {
			std::lock_guard<std::mutex> lock(mutex_);
			schedules_.erase(_task_id);
		}
	private:
		std::unordered_map<UID, RepeatingTask> schedules_;

		void ThreadWorker() {
			while(!stop_signal_received_) {
				{
					std::lock_guard<std::mutex> lock(mutex_);
					last_run_time_ = TimeManager::GetInstance()->GetCurrentTimePoint();
					next_run_time_ = last_run_time_ + interval_;
					for (auto& schedule : schedules_) {
						schedule.second.Update(last_run_time_);
					}
				}
				std::this_thread::sleep_until(next_run_time_);
			}
		}

		TimePoint last_run_time_;
		TimePoint next_run_time_;
		std::chrono::milliseconds interval_;
		std::atomic_bool stop_signal_received_;

		std::mutex mutex_;
	};
}

