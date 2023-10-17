#include "thread_pool.h"




void thread_pool::work(void)
{
	m.lock();
	std::cout << "Start working id: " << std::this_thread::get_id() << std::endl;
	m.unlock();
	while (!flag_done)
	{
		std::unique_lock lk(m);
		data_cond.wait_for(lk, std::chrono::milliseconds(1700));
		if (!s.pop()) std::this_thread::yield();
		lk.unlock();
	}
}


void thread_pool::submit(std::function<void()> f)
{
	std::this_thread::sleep_for(100ms);
		s.push(f);
		data_cond.notify_all();
}