#pragma once

#include <thread>
#include <mutex>

#include "Types.h"
#include "DuoBuffer.h"

namespace cubey3 {

	template<typename BufferT>
	class DuoBufferMT : public DuoBuffer<BufferT> {
	public:
		struct BufferMT {
			Lock lock_;
			BufferT& buffer_;
		};

		DuoBufferMT () : DuoBuffer() {
		}

		DuoBufferMT (const DuoBufferMT<BufferT>& other) {
			SimpleLock f_lock(other.front_buffer_mutex_);
			SimpleLock b_lock(other.back_buffer_mutex_);
			DuoBuffer<BufferT>::ping_ = other.ping_;
			DuoBuffer<BufferT>::pong_ = other.pong_;
			DuoBuffer<BufferT>::flip_ = other.flip_;
		}

		DuoBufferMT(DuoBufferMT<BufferT>&& other) {
			SimpleLock f_lock(other.front_buffer_mutex_);
			SimpleLock b_lock(other.back_buffer_mutex_);
			DuoBuffer<BufferT>::ping_ = std::move(other.ping_);
			DuoBuffer<BufferT>::pong_ = std::move(other.pong_);
			DuoBuffer<BufferT>::flip_ = std::move(other.flip_);
		}

		void SwapMT() {
			auto f_lock = LockFrontBuffer();
			auto b_lock = LockBackBuffer();
			DuoBuffer<BufferT>::Swap();
		}

		BufferMT LockFrontBuffer() {
			return BufferMT{ Lock(front_buffer_mutex_), front_buffer() };
		}

		BufferMT LockBackBuffer() {
			return BufferMT{ Lock(back_buffer_mutex_), back_buffer() };
		}

	protected:
		std::mutex front_buffer_mutex_;
		std::mutex back_buffer_mutex_;
	};
}