// FactoryMethod.cpp : 
//��������ģʽ����ڼ򵥹���ģʽ�������廯��Ĺ����ӳٵ�����
//Factoryģʽ������һ���࣬��product����һ�࣬��һ����ͬ�Ļ���
//Ϊ��ͬ������ṩһ�����󴴽��Ľӿڣ��Ǿ�Ҫ��AbstractFactory

//#include "stdafx.h"
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
	OperationFactory(){}

public:
	virtual Operation* CreateOperate() = 0;
protected:
};

class AddFactory : public OperationFactory
{
public:
	Operation* CreateOperate()
	{
		return new OperationAdd();
	}
};

class SubFactory : public OperationFactory
{
public:
	Operation* CreateOperate()
	{
		return new OperationSub();
	}
};

class MulFactory : public OperationFactory
{
public:
	Operation* CreateOperate()
	{
		return new OperationMul();
	}
};

class DivFactory : public OperationFactory
{
public:
	Operation* CreateOperate()
	{
		return new OperationDiv();
	}
};


int main()
{
	OperationFactory* operFactory = new AddFactory();
	Operation* oper = operFactory->CreateOperate();
	
	oper->SetNumberA(12);
	oper->SetNumberB(20);
	double result = oper->GetResult();

	cout << result << endl;

	system("pause");

	return 0;
}

