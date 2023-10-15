

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <chrono>
#include <functional>
#include <future>
#include <atomic>
#include "thread_pool.h"
#include "safe_queue.h"

using namespace std::chrono_literals;


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
	tp1.submit(func1);
	tp2.submit(func2);

	return 0;
}



//
//std::queue<std::function<void()>> work_queue;
//std::vector<std::thread> VecThread;
//
//std::atomic<bool> flag_done{ false };
//
//
//void addF1() {
//	for (int i = 0; i < 5; ++i)
//	{
//		std::this_thread::sleep_for(500ms);
//		std::lock_guard l(m);
//		work_queue.push(func1);
//	}
//}
//
//void addF2() {
//	for (int i = 0; i < 5; ++i)
//	{
//		std::this_thread::sleep_for(1s);
//		std::lock_guard l(m);
//		work_queue.push(func2);
//	}
//	flag_done = true;
//}
//

/*
void work() {
	m.lock();
	std::cout << "Start working id: " << std::this_thread::get_id() << std::endl;
	m.unlock();
	while (!flag_done)
	{
		if (!work_queue.empty()) {
			auto func = work_queue.front();
			func();
			work_queue.pop();
		}
		else { std::this_thread::yield(); }
	}
	while (!work_queue.empty()) {
		auto func = work_queue.front();
		func();
		work_queue.pop();
	}
}
*/

/*
int main_01()
{
	const auto cores = std::thread::hardware_concurrency();
	std::cout << "Cores# " << cores << std::endl;
	std::thread th1(addF1);
	std::thread th2(addF2);


	for (int i = 0; i < cores - 2; ++i)
	{
		VecThread.push_back(std::thread(work));
	}
	for (auto& el : VecThread)
	{
		el.join();
	}
	th1.join();
	th2.join();
	return 0;
}
*/