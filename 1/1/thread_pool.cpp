#include "thread_pool.h"




void thread_pool::work(void)
{
	m.lock();
	std::cout << "Start working id: " << std::this_thread::get_id() << std::endl;
	m.unlock();
	while (!flag_done)
	{
		std::unique_lock lk(m);
		data_cond.wait(lk, [&]() {return !s.empty(); });
		if (!s.pop()) std::this_thread::yield();
		lk.unlock();
	}
	while (!s.empty()) {
		s.pop();
	}
}


void thread_pool::submit(std::function<void()> f)
{
	for (int i = 0; i < 5; ++i)
	{
		std::this_thread::sleep_for(200ms);
		s.push(f);
		data_cond.notify_all();
	}

	flag_done = true;
}