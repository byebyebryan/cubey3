#pragma once

#include "ITask.h"

namespace cubey3 {
	class RepeatingTask : public ITask<RepeatingTask> {
	public:
		void Start(const TimePoint& _now) override {
			next_run_time_ = _now + interval_;;
		}

		void Update(const TimePoint& _now) override {
			if (_now > next_run_time_ || override_trigger_fn_()) {
				process_fn_();
				last_run_time_ = _now;
				next_run_time_ = _now + interval_;
			}
		}

		std::chrono::milliseconds interval_;
		std::function<bool()> override_trigger_fn_;
		TimePoint last_run_time_;
		TimePoint next_run_time_;
	};
}