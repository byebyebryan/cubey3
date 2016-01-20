#pragma once

#include <functional>
#include <map>
#include <mutex>

namespace cubey3 {
	template<typename EventT>
	class SystemEventChannel {
	public:
		static void Add(size_t id, const std::function<void(const EventT&)>& handler_func) {
			auto lock = std::lock_guard<std::mutex>(mutex_);
			if (handler_funcs_.find(id) == handler_funcs_.end()) {
				handler_funcs_[id] = handler_func;
			}
		}

		static void Remove(size_t id) {
			auto lock = std::lock_guard<std::mutex>(mutex_);
			handler_funcs_.erase(id);
		}

		static void Mute() {
			auto lock = std::lock_guard<std::mutex>(mutex_);
			is_muted_ = true;
		}

		static void UnMute() {
			auto lock = std::lock_guard<std::mutex>(mutex_);
			is_muted_ = false;
		}

		static void Broadcast(const EventT& event) {
			auto lock = std::lock_guard<std::mutex>(mutex_);
			if (!is_muted_) {
				for (auto it : handler_funcs_) {
					it->second(event);
				}
			}
		}

		static void Broadcast(std::initializer_list<EventT> event_args) {
			Broadcast(EventT(event_args));
		}

	private:
		static std::map<size_t, std::function<void(const EventT&)>> handler_funcs_;
		static bool is_muted_;
		static std::mutex mutex_;
	};

	template <typename EventT>
	std::map<size_t, std::function<void(const EventT&)>> SystemEventChannel<EventT>::handler_funcs_;

	template <typename EventT>
	bool SystemEventChannel<EventT>::is_muted_ = false;

	template <typename EventT>
	std::mutex SystemEventChannel<EventT>::mutex_;
}