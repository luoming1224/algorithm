// Handle_Class.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

class Item_base
{
public:
	Item_base(const std::string &book = "", double sales_price = 0.0):
	  isbn(book), price(sales_price){}

	std::string book() const { return isbn; }

	virtual double net_price(std::size_t n) const
	{
		return n * price;
	}

	virtual ~Item_base(){}

	virtual Item_base* clone() const
	{
		return new Item_base(*this);
	}

protected:
	double price;
private:
	std::string isbn;
};

class Bulk_item : public Item_base
{
public:
	Bulk_item* clone() const
	{
		return new Bulk_item(*this);
	}
protected:
private:
};

class Sales_item
{
public:
	Sales_item(): p(0), use(new std::size_t(1)){}

	Sales_item(const Item_base&);

	Sales_item(const Sales_item &i):
		p(i.p),use(i.use) { ++*use; }

	~Sales_item(){ decr_use(); }

	Sales_item& operator=(const Sales_item&);

	const Item_base* operator->() const { if(p) return p; }

	const Item_base& operator*() const { if(p) return *p; }

protected:
private:
	Item_base *p;
	std::size_t *use;

	void decr_use(){ if(--*use == 0) { delete p; delete use; } }
};

Sales_item& Sales_item::operator=( const Sales_item& rhs )
{
	++*rhs.use;
	decr_use();
	p = rhs.p;
	use = rhs.use;

	return *this;
}

Sales_item::Sales_item( const Item_base& item)
: p(item.clone()), use(new std::size_t(1))
{

}


int main()
{
	return 0;
}

