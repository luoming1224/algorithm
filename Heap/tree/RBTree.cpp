// RBTree.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
using namespace std;

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

// struct __rb_tree_node_base 
// {
// 	
// };

template <class Value>
struct __rb_tree_node 
{
	typedef __rb_tree_node<Value>* link_type;
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node* base_ptr;

	color_type	color;
	base_ptr	parent;
	base_ptr	left;
	base_ptr	right;

	static base_ptr minimum(base_ptr x)
	{
		while (x->left != 0)
		{
			x = x->left;
		}
		return x;
	}

	static base_ptr maximum(base_ptr x)
	{
		while (x->right != 0)
		{
			x = x->right;
		}
		return x;
	}
	Value value_field;
};

template <class Value>
class rb_tree
{
protected:
	typedef void* void_pointer;
//	typedef __rb_tree_node_base* base_ptr;
	typedef __rb_tree_node<Value> rb_tree_node;
	typedef __rb_tree_node<Value>* rb_tree_ptr;
	typedef __rb_tree_color_type color_type;

public:
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
public:
	rb_tree();
	~rb_tree(){}

public:
	rb_tree_ptr successor(rb_tree_ptr pnode);
	rb_tree_ptr predecessor(rb_tree_ptr pnode);
	int insert_key(const value_type& k);
	void left_rotate(rb_tree_ptr pnode);
	void right_rotate(rb_tree_ptr pnode);
	void rb_insert_rebalance(rb_tree_ptr pnode);
	void inorder_search();
protected:
private:
public:
	rb_tree_ptr	root;
};

template <class Value>
void rb_tree<Value>::inorder_search()
{
	if (NULL != root)
	{
		stack<rb_tree_ptr> s;
		rb_tree_ptr ptmpnode;
		ptmpnode = root;
		while (NULL != ptmpnode || !s.empty())
		{
			if (NULL != ptmpnode)
			{
				s.push(ptmpnode);
				ptmpnode = ptmpnode->left;
			}
			else
			{
				ptmpnode = s.top();
				s.pop();
				cout << ptmpnode->value_field << ":";
				if (ptmpnode->color == __rb_tree_black)
				{
					cout << "Black" << endl;
				}
				else
					cout << "Red" << endl;
				ptmpnode = ptmpnode->right;
			}
		}
	}
}

template <class Value>
void rb_tree<Value>::rb_insert_rebalance( rb_tree_ptr pnode )
{
	while (pnode != root && pnode->parent->color == __rb_tree_red)
	{
		if (pnode->parent == pnode->parent->parent->left)
		{
			rb_tree_ptr rnode = pnode->parent->parent->right;
			if (rnode && rnode->color == __rb_tree_red)		//叔父节点存在且为red
			{
				pnode->parent->color = __rb_tree_black;
				rnode->color = __rb_tree_black;
				pnode->parent->parent->color = __rb_tree_red;
				pnode = pnode->parent->parent;
			}
			else	//叔父节点不存在或为black
			{
				if (pnode == pnode->parent->right)
				{
					pnode = pnode->parent;
					left_rotate(pnode);
				}
				pnode->parent->color = __rb_tree_black;
				pnode->parent->parent->color = __rb_tree_red;
				right_rotate(pnode->parent->parent);
			}
		}
		else
		{
			rb_tree_ptr lnode = pnode->parent->parent->left;
			if (lnode && lnode->color == __rb_tree_red)
			{
				pnode->parent->color = __rb_tree_black;
				lnode->color = __rb_tree_black;
				pnode->parent->parent->color = __rb_tree_red;
				pnode = pnode->parent->parent;
			}
			else
			{
				if (pnode == pnode->parent->left)
				{
					pnode = pnode->parent;
					right_rotate(pnode);
				}
				pnode->parent->color = __rb_tree_black;
				pnode->parent->parent->color = __rb_tree_red;
				left_rotate(pnode->parent->parent);
			}
		}
	}
	root->color = __rb_tree_black;
}

template <class Value>
void rb_tree<Value>::right_rotate( rb_tree_ptr pnode )
{
	rb_tree_ptr lnode = pnode->left;
	pnode->left = lnode->right;
	if (lnode->right !=NULL)
	{
		lnode->right->parent = pnode;
	}
	lnode->parent = pnode->parent;
	if (pnode->parent == NULL)
	{
		root = lnode;
	}
	else if (pnode == pnode->parent->left)
	{
		pnode->parent->left = lnode;
	}
	else
		pnode->parent->right = lnode;
	lnode->right = pnode;
	pnode->parent = lnode;
}

template <class Value>
void rb_tree<Value>::left_rotate( rb_tree_ptr pnode )
{
	rb_tree_ptr rnode = pnode->right;
	pnode->right = rnode->left;
	if (rnode->left != NULL)
	{
		rnode->left->parent = pnode;
	}
	rnode->parent = pnode->parent;
	if (pnode->parent == NULL)
	{
		root = rnode;
	}
	else if (pnode == pnode->parent->left)
	{
		pnode->parent->left = rnode;
	}
	else
		pnode->parent->right = rnode;

	rnode->left = pnode;
	pnode->parent = rnode;
}

template <class Value>
rb_tree<Value>::rb_tree()
{
	root = NULL;
}

template <class Value>
int rb_tree<Value>::insert_key( const value_type& k )
{
	rb_tree_node* newnode = (rb_tree_node*)malloc(sizeof(rb_tree_node));
	newnode->value_field = k;
	newnode->color = __rb_tree_red;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;

	if (NULL == root)
	{
		root = newnode;
	}
	else
	{
		rb_tree_ptr pnode = root;
		rb_tree_ptr qnode;
		while (pnode != NULL)
		{
			qnode = pnode;
			if (pnode->value_field > newnode->value_field)
			{
				pnode = pnode->left;
			}
			else
				pnode = pnode->right;
		}
		newnode->parent = qnode;
		if (qnode->value_field > newnode->value_field)
		{
			qnode->left = newnode;
		}
		else
			qnode->right = newnode;
	}
	rb_insert_rebalance(newnode);
	return 0;
}

template <class Value>
__rb_tree_node<Value>* rb_tree<Value>::successor( rb_tree_ptr pnode )	//why?为什么rb_tree_ptr可以作为参数类型，不可以作为返回值类型？
{
	if (pnode->right != NULL)
	{
		return __rb_tree_node::minimum(pnode->right);
	}
	rb_tree_ptr parentnode = pnode->parent;
	while (parentnode != NULL && parentnode->right == pnode)
	{
		pnode = parentnode;
		parentnode = pnode->parent;
	}
	return parentnode;
}

template <class Value>
__rb_tree_node<Value>* rb_tree<Value>::predecessor( rb_tree_ptr pnode )
{
	if (pnode->left != NULL)
	{
		return __rb_tree_node::maximum(pnode->left);
	}
	rb_tree_ptr parentnode = pnode->parent;
	while (parentnode != NULL && parentnode->left == pnode)
	{
		pnode = parentnode;
		parentnode = pnode->parent;
	}
	return parentnode;
}

int main()
{
	rb_tree<int> rbtree;
	rbtree.insert_key(41);
	rbtree.insert_key(38);
	rbtree.inorder_search();
	cout << "************" << endl;
	rbtree.insert_key(31);
	rbtree.inorder_search();
	cout << rbtree.root->value_field << " : " << rbtree.root->color << endl; 
	cout << "************" << endl;
	rbtree.insert_key(12);
	rbtree.inorder_search();
	cout << "************" << endl;
	rbtree.insert_key(19);
	rbtree.inorder_search();
	cout << "************" << endl;
	rbtree.insert_key(8);
	rbtree.inorder_search();
	cout << "************" << endl;
	rbtree.insert_key(6);
	rbtree.inorder_search();
	cout << rbtree.root->value_field << " : " << rbtree.root->color << endl; 
	system("pause");
	return 0;
}

