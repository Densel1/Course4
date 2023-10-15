#pragma once
#include <queue>
#include <mutex>
#include <chrono>
#include <functional>
#include <condition_variable>

using namespace std::chrono_literals;


template<typename T>
class safe_queue
{
	std::mutex m;
	std::queue<std::function<void()>> work_q;
	std::condition_variable data_cond;
public:

	safe_queue() = default;


	void push(T fn) 
	{
		work_q.push(fn);
		data_cond.notify_all();
	}

	bool pop()
	{
		std::lock_guard l(m);
		if (!empty())
		{
			auto func = work_q.front();
			func();
			work_q.pop();

			return true;
		}
		return false;
	}


	bool empty()
	{
		return work_q.empty();
	}
};

