#pragma once

namespace cubey3 {
	template<typename BufferT>
	class DuoBuffer {
	public:
		DuoBuffer() :
				ping_(BufferT()), 
				pong_(BufferT()), 
				flip_(false) {
		}

		DuoBuffer(const BufferT& front_buffer) :
				ping_(front_buffer), 
				pong_(BufferT()), 
				flip_(false) {
		}

		DuoBuffer(const BufferT& front_buffer, const BufferT& back_buffer) :
				ping_(front_buffer), 
				pong_(back_buffer), 
				flip_(false) {
		}

		BufferT& front_buffer() {
			return flip_ ? ping_ : pong_;
		}

		BufferT& back_buffer() {
			return flip_ ? pong_ : ping_;
		}

		void Swap() {
			flip_ = !flip_;
		}

	protected:
		BufferT ping_;
		BufferT pong_;

		bool flip_;
	};
}