#pragma once

#include <thread>
#include <mutex>

#include "DuoBuffer.h"

namespace cubey3 {

	template<typename BufferT>
	class DuoBufferMT : public DuoBuffer<BufferT> {
	public:
		struct BufferMT {
			std::unique_lock<std::mutex> lock_;
			BufferT& buffer_;
		};

		DuoBufferMT () : DuoBuffer() {
		}

		DuoBufferMT (const DuoBufferMT<BufferT>& _other) {
			std::lock_guard<std::mutex> f_lock(_other.front_buffer_mutex_);
			std::lock_guard<std::mutex> b_lock(_other.back_buffer_mutex_);
			DuoBuffer<BufferT>::ping_ = _other.ping_;
			DuoBuffer<BufferT>::pong_ = _other.pong_;
			DuoBuffer<BufferT>::flip_ = _other.flip_;
		}

		DuoBufferMT(DuoBufferMT<BufferT>&& _other) {
			std::lock_guard<std::mutex> f_lock(_other.front_buffer_mutex_);
			std::lock_guard<std::mutex> b_lock(_other.back_buffer_mutex_);
			DuoBuffer<BufferT>::ping_ = std::move(_other.ping_);
			DuoBuffer<BufferT>::pong_ = std::move(_other.pong_);
			DuoBuffer<BufferT>::flip_ = std::move(_other.flip_);
		}

		void SwapMT() {
			auto f_lock = LockFrontBuffer();
			auto b_lock = LockBackBuffer();
			DuoBuffer<BufferT>::Swap();
		}

		BufferMT LockFrontBuffer() {
			return BufferMT{ std::unique_lock<std::mutex>(front_buffer_mutex_), front_buffer() };
		}

		BufferMT LockBackBuffer() {
			return BufferMT{ std::unique_lock<std::mutex>(back_buffer_mutex_), back_buffer() };
		}

	protected:
		mutable std::mutex front_buffer_mutex_;
		mutable std::mutex back_buffer_mutex_;
	};
}