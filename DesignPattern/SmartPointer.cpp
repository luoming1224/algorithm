// SmartPointer.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class U_Ptr
{
	friend class HasPtr;
	int *ip;
	size_t use;
	U_Ptr(int *p): ip(p), use(1){}
	~U_Ptr(){ 
		delete ip; 
		ip = NULL;
	}
};

class HasPtr
{
public:
	HasPtr(int *p, int i): ptr(new U_Ptr(p)), val(i){}

	HasPtr(const HasPtr &orig):
	ptr(orig.ptr), val(orig.val) {++ptr->use;}

	HasPtr& operator=(const HasPtr&);

	~HasPtr(){ 
		if(--ptr->use == 0) 
			delete ptr; 
	}

public:
	int *get_ptr() const { return ptr->ip; }
	int get_int() const { return val; }

	void set_ptr(int *p) { ptr->ip = p; }
	void set_int(int i) { val = i; }

	int get_ptr_var() const { return *ptr->ip; }
	void set_ptr_val(int i) { *ptr->ip = i; }
protected:
private:
	U_Ptr *ptr;
	int val;
};

HasPtr& HasPtr::operator=( const HasPtr& rhs)
{
	++rhs.ptr->use;
	if (--ptr->use == 0)
	{
		delete ptr;
	}
	ptr = rhs.ptr;
	val = rhs.val;

	return *this;
}

int main()
{
	int *pvalue = new int(10);
	HasPtr* p1 = new HasPtr(pvalue, 20);
	HasPtr* p2 = new HasPtr(*p1);
	
	cout << p2->get_int() << "  "  << p2->get_ptr_var() << endl;
	delete p1;

	delete p2;

	return 0;
}

