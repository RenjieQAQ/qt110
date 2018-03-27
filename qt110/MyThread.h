#pragma once
#include <pthread.h>
#include<Windows.h>
#include <iostream>
using namespace std;
/**
void * f(void * p)
{
	int cnt = 0;
	for (;;)
	{
		cout << (char *)p << ":" << cnt++ << endl;
		Sleep(1000);
	}
}
*/
class MyThread
{
private:
	pthread_t pid;
	pthread_attr_t attr;
	bool isReleased;
public:
	MyThread(void *(__cdecl *start)(void *) , void *arg);
	~MyThread();
	int release();
};

