// SimpleFactory.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
/*#include "Singleton.h"*/
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string, int>  operateMap;

class Operation
{
public:
	virtual double GetResult() = 0;
	void SetNumberA(double numberA){m_numberA = numberA;}
	void SetNumberB(double numberB){m_numberB = numberB;}
protected:
	double m_numberA;
	double m_numberB;
private:
};

class OperationAdd : public Operation
{
public:
	double GetResult()
	{
		double result = 0;
		result = m_numberA + m_numberB;
		return result;
	}
protected:
private:
};

class OperationSub : public Operation
{
public:
	double GetResult()
	{
		double result = 0;
		result = m_numberA - m_numberB;
		return result;
	}
protected:
private:
};

class OperationMul : public Operation
{
public:
	double GetResult()
	{
		double result = 0;
		result = m_numberA * m_numberB;
		return result;
	}
protected:
private:
};

class OperationDiv : public Operation
{
public:
	double GetResult()
	{
		double result = 0;
		if (m_numberB == 0)
		{
			cout << "error!" << endl;
		}
		result = m_numberA / m_numberB;
		return result;
	}
protected:
private:
};

class OperationFactory 
{
public:
	static OperationFactory* Instance();
	void unInstance();

public:
	Operation* CreateOperate(string operate)
	{
		Operation* oper = NULL;
		int noper = operateMap[operate];
		switch (noper)
		{
		case 0:
			oper = new OperationAdd();
			break;
		case 1:
			oper = new OperationSub();
			break;
		case 2:
			oper = new OperationMul();
			break;
		case 3:
			oper = new OperationDiv();
			break;
		}
		return oper;
	}
protected:
private:
	OperationFactory(){}
private:
	static  OperationFactory* pInstance;
};
OperationFactory* OperationFactory::pInstance = NULL;

OperationFactory* OperationFactory::Instance()
{
	if (NULL == pInstance)
	{
		if (NULL == pInstance)
		{
			pInstance = new OperationFactory();
		}
	}
	return pInstance;
}

void OperationFactory::unInstance()
{
	if (NULL != pInstance)
	{
		if (NULL != pInstance)
		{
			delete pInstance;
			pInstance = NULL;
		}
	}
}


int main()
{
	operateMap.insert(make_pair("+", 0));
	operateMap.insert(make_pair("-", 1));
	operateMap.insert(make_pair("*", 2));
	operateMap.insert(make_pair("/", 3));

	Operation* oper;
	oper = OperationFactory::Instance()->CreateOperate("+");
	oper->SetNumberA(12);
	oper->SetNumberB(20);
	double result = oper->GetResult();

	cout << result << endl;

	system("pause");

	return 0;
}

