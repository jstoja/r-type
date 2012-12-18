#include <iostream>

#include "Threading.h"

Threading::Mutex g_mutex;
Threading::Atomic<int> g_atomic;

class Test
{
public:
	Test() {}

	void	operator()()
	{
		Threading::MutexLocker	locker(&g_mutex);
		std::cout << "PLOP" << std::endl;
		Sleep(2000);
		g_atomic = 42;
	}
};

int	main(int ac, char **av)
{
	Threading::Thread<Test> tmp(new Test);
	g_atomic = 2;

	Threading::MutexLocker	locker(&g_mutex);
	tmp.run();
	getchar();
	locker.unlock();
	std::cout << "Before join" << g_atomic << std::endl;
	locker.relock();
	tmp.join();
	std::cout << "After join" << g_atomic << std::endl;
	Sleep(2000);
	return (0);
}