#pragma once

#include <functional>

#include "Utilities/IDGenerator.h"
#include "TimeManager.h"

namespace cubey3 {
	template <typename TaskT>
	class ITask {
	public:
		ITask() : 
				id_(IDGenerator::NextID<TaskT>()),
				is_marked_for_deletion_(false) {}

		ITask(const std::function<void()>& process_fn, ITask* subsequent_task = nullptr) :
				id_(IDGenerator::NextID<TaskT>()),
				process_fn_(process_fn),
				is_marked_for_deletion_(false),
				subsequent_task_(subsequent_task) {}

		virtual ~ITask() {}

		virtual void Start(const TimePoint& now) = 0;
		virtual void Update(const TimePoint& now) = 0;
		virtual void Finish(const TimePoint& now) {
			if (subsequent_task_) {
				subsequent_task_->Start(now);
			}
		}

		size_t id_;
		std::function<void()> process_fn_;
		bool is_marked_for_deletion_;
		ITask* subsequent_task_;
	};
}