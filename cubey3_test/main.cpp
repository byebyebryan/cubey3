
#include <iostream>
#include <thread>

#include "cubey3.h"

using namespace cubey3;

void ThreadWork() {
	Logger::GetService()->LogToConsole("hello");

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main(void) {
	TimeManager::CreateService();
	ThreadManager::CreateService();
	Logger::CreateService();

	ThreadManager::GetService()->LaunchThread("test",ThreadWork);
	Logger::GetService()->LogToConsole("hello");

	ThreadManager::DestroyService();
}