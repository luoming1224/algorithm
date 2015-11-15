// TemplateMethod.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class AbstractClass
{
public:
	void TemplateMethod()
	{
		PrimitiveOperation1();
		PrimitiveOperation2();
	}
protected:
	AbstractClass(){}
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
private:
};

class ConcreteClassA : public AbstractClass
{
	void PrimitiveOperation1()
	{
		cout << "ConcreteClassA-----PrimitiveOperation1" << endl;
	}
	void PrimitiveOperation2()
	{
		cout << "ConcreteClassA-----PrimitiveOperation2" << endl;
	}
};

class ConcreteClassB : public AbstractClass
{
	void PrimitiveOperation1()
	{
		cout << "ConcreteClassB-----PrimitiveOperation1" << endl;
	}
	void PrimitiveOperation2()
	{
		cout << "ConcreteClassB-----PrimitiveOperation2" << endl;
	}
};

int main()
{
	AbstractClass *pA = new ConcreteClassA();
	pA->TemplateMethod();

	AbstractClass *pB = new ConcreteClassB();
	pB->TemplateMethod();

	system("pause");
	return 0;
}

