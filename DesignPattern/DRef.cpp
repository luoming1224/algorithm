// DRef.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

template<class T>
class DRef
{
public:
	DRef(T* p = NULL): m_pObj(p), use(new std::size_t(1)){}

	DRef(const DRef<T>& rhs)
		: m_pObj(rhs.m_pObj), use(rhs.use)
	{ 
		++*use;
	}

	DRef<T>& operator=(const DRef< T > &rhs)
	{
		if( m_pObj == rhs.m_pObj)
			return *this;
		decr_use();
		++*rhs.use;
		m_pObj = rhs.m_pObj;
		use = rhs.use;
	}

	~DRef(){ decr_use(); }
protected:
private:
	void decr_use(){ 
		if(--*use == 0) 
		{ 
			delete m_pObj; 
			delete use; 
		} 
	}
protected:
	T * m_pObj;
	std::size_t *use;
};

int main()
{
	int *x = new int(30);
	DRef<int>	*p1 = new DRef<int>(x);
	DRef<int>	*p2 = new DRef<int>(*p1);
	delete p1;
	delete p2;
	system("pause");
	return 0;
}

