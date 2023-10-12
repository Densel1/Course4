#pragma once
#include <vector>
#include <thread>
#include <functional>

class thread_pool
{
	std::vector<std::thread> v;
public:
	thread_pool(std::vector<std::thread> &vec)
	{
		v = move(vec);
	}

	void work()
	{

	}

	void submit(std::function<void()> f)
	{

	}

	~thread_pool()
	{
		for (auto& el : v)
		{
			el.join();
		}
	}
};

