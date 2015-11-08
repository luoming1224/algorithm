// Singleton.cpp : 定义控制台应用程序的入口点。
//让类自身负责保存它的唯一实例，这个类可以保证没有其他实例被创建，并且它可以提供一个访问该实例的方法

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

CRITICAL_SECTION g_cs, g_csRelease;

class Singleton
{
public:
	static Singleton* Instance();
	void unInstance();
protected:
private:
	Singleton(){}
private:
	static Singleton* pInstance;
};


Singleton* Singleton::pInstance = NULL;

Singleton* Singleton::Instance()
{
	if (NULL == pInstance)
	{
		EnterCriticalSection(&g_cs);
		if (NULL == pInstance)
		{
			pInstance = new Singleton();
		}
		LeaveCriticalSection(&g_cs);
	}
	return pInstance;
}

void Singleton::unInstance()
{
	if (NULL != pInstance)
	{
		EnterCriticalSection(&g_csRelease);
		if (NULL != pInstance)
		{
			delete pInstance;
			pInstance = NULL;
		}
		LeaveCriticalSection(&g_csRelease);
	}
}


int main()
{
	InitializeCriticalSection(&g_cs);
	InitializeCriticalSection(&g_csRelease);
	//
	DeleteCriticalSection(&g_cs);
	DeleteCriticalSection(&g_csRelease);
	return 0;
}

