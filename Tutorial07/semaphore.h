#pragma once
#include<mutex>

class semaphore
{
	std::mutex m;
	int signal,flag=0;
public:
	void continuoenter();
	void conntinuoexit();
	void enter();
	void exit();
};

