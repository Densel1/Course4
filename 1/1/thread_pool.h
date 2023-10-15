#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "safe_queue.h"


using namespace std::chrono_literals;


class thread_pool
{
	std::mutex m;
	std::vector<std::thread> v;
	unsigned int cores;
	safe_queue<std::function<void()>> s;
	std::atomic<bool> flag_done{ false };
	std::condition_variable data_cond;

public:
	thread_pool()
	{
		cores = std::thread::hardware_concurrency();
		for (int i = 0; i < cores/2 - 1; ++i)
		{
			v.push_back(std::thread(&thread_pool::work, this));
		}
	}

	void work(void);


	void submit(std::function<void()> f);

	~thread_pool()
	{
		for (auto& el : v)
		{
			if(el.joinable()) el.join();
		}
	}
};

