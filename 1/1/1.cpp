

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <chrono>
#include <functional>
#include <future>
#include <atomic>
#include <condition_variable>
#include "thread_pool.h"
#include "safe_queue.h"

using namespace std::chrono_literals;

std::condition_variable d_cond;
std::mutex m;
void func1() {
	std::this_thread::sleep_for(500ms);
	std::lock_guard l(m);
	std::cout << "Working " << __FUNCTION__ << "...\n";
}

void func2() {
	std::this_thread::sleep_for(100ms);
	std::lock_guard l(m);
	std::cout << "Working " << __FUNCTION__ << "...\n";
}


int main()
{
	thread_pool tp1;
	thread_pool tp2;

	for (int i = 0; i < 5; ++i)
	{
		tp1.submit(func1);
		std::this_thread::sleep_for(1000ms);
		tp2.submit(func2);

	}
	return 0;
}


