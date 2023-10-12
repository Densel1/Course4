#pragma once
#include <queue>
#include <mutex>

template<class T>
class safe_queue
{
	mutex m;
public:

	safe_queue() = default;

	void push() {}
	T pop() {}
};

