#pragma once

#include "SystemEventChannel.h"

#include "../Utilities/IDGenerator.h"

namespace cubey3 {
	template<typename EventT>
	class SystemEventLisenter {
	public:
		SystemEventLisenter() :
			id_(0) {}

		SystemEventLisenter(const std::function<void(const EventT&)>& handler_func) :
			id_(0),
			handler_func_(handler_func) {}

		~SystemEventLisenter() {
			if(id_ != 0) {
				RemoveFromChannel();
			}
		}

		template<size_t StreamID = kIDGeneratorDefaultStream>
		void PushToChannel() {
			if(id_ == 0) {
				id_ = IDGenerator::NextID<EventT, StreamID>();
			}
			SystemEventChannel<EventT>::Add(id_, handler_func_);
		}

		void RemoveFromChannel() {
			SystemEventChannel<EventT>::Remove(id_);
		}

		size_t id_;
		std::function<void(const EventT&)> handler_func_;
	};
}