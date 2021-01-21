#include "semaphore.h"

void semaphore::continuoenter()
{
	m.lock();
	while (flag == 1) {

	}
	signal = 1;
	m.unlock();
}

void semaphore::conntinuoexit()
{
	signal = 0;
}

void semaphore::enter()
{
	m.lock();
	flag = 1;
	while (signal == 1) {

	}
	m.unlock();
}

void semaphore::exit()
{
	flag = 0;
}
