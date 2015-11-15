// StrategyPattern.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class Strategy
{
public:
	virtual void AlgorithmInterface() = 0;
protected:
private:
};

class ConcreteStrategyA : public Strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout << "achieve Algorithm..A" << endl;
	}
};

class ConcreteStrategyB : public Strategy
{
public:
	virtual void AlgorithmInterface()
	{
		cout << "achieve Algorithm..B" << endl;
	}
};

class Context
{
public:
	Context(Strategy* strategy)
	{
		pStrategy = strategy;
	}

	void ContextInterface()
	{
		pStrategy->AlgorithmInterface();
	}
protected:
private:
	Strategy* pStrategy;
};

//策略模式与简单工厂模式结合
class ContextFactory
{
public:
	ContextFactory(int index)
	{
		switch (index)
		{
		case 0:
			pStrategy = new ConcreteStrategyA();
			break;
		case 1:
			pStrategy = new ConcreteStrategyB();
			break;
		}
	}

	void ContextInterface()
	{
		pStrategy->AlgorithmInterface();
	}
protected:
private:
	Strategy* pStrategy;
};

int main()
{
	Context* pContext = new Context(new ConcreteStrategyB());
	pContext->ContextInterface();

	ContextFactory* pFactory = new ContextFactory(0);
	pFactory->ContextInterface();

	system("pause");
	return 0;
}

