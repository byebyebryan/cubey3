
#include <iostream>
#include <thread>

#include "cubey3.h"

using namespace cubey3;

DuoBufferMT<int> duo_buffer_mt;

void ThreadWork() {
	for (int i = 0; i < 100; i++) {
		duo_buffer_mt.LockFrontBuffer().buffer_ += 100;

		//duo_buffer_mt.SwapMT();

		std::cout << duo_buffer_mt.LockFrontBuffer().buffer_ << std::endl;
		//std::cout << duo_buffer_mt.LockBackBuffer().buffer_ << std::endl;
	}
	
}

int main(void) {
	{	duo_buffer_mt.LockFrontBuffer().buffer_ = 0;
		duo_buffer_mt.LockBackBuffer().buffer_ = 1; 
	}

	auto it = std::thread(ThreadWork);

	for (int i = 0; i < 100; i++) {
		duo_buffer_mt.LockFrontBuffer().buffer_ += 1;

		//duo_buffer_mt.SwapMT();

		std::cout << duo_buffer_mt.LockFrontBuffer().buffer_ << std::endl;
		//std::cout << duo_buffer_mt.LockBackBuffer().buffer_ << std::endl;
	}

	it.join();
}