#include "MyThread.h"



MyThread::MyThread(void *(__cdecl *start)(void *), void *arg)
{
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);//
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&pid, &attr, start, arg);
	isReleased = 0;
}


MyThread::~MyThread()
{
}

int MyThread::release()
{
	if (!isReleased)
	{
		pthread_attr_destroy(&attr);
		isReleased = 1;
		return 0;
	}
	else
		return -1;
}

void * f(void * p)
{

	return NULL;
}