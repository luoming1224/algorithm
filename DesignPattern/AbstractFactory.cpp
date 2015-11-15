// AbstractFactory.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include "Factory.h"
#include <stdlib.h>


int main()
{
	User* user = new User();
	Department* pDepartment = new Department();
//	IFactory* factory = new SqlServerFactory();
	IFactory* factory = new AccessFactory();

	IUser* iu = factory->CreateUser();
	iu->Insert(user);
	iu->GetUser(1);

	IDepartment* pD = factory->CreateDepartment();
	pD->Insert(pDepartment);
	pD->GetDepartment(2);

	system("pause");
	return 0;
}

