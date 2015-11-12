// tree.cpp : 
//

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <stack>
using namespace std;

typedef struct TreeNode* pNode;
struct TreeNode 
{
	int data;
	pNode  left;
	pNode  right;
};

void PreOrderRecursive(pNode root)
{
	if(NULL == root) return;

	cout << root->data << " ";
	PreOrderRecursive(root->left);
	PreOrderRecursive(root->right);
}

void InOrderRecursive(pNode root)
{
	if(NULL == root) return;

	InOrderRecursive(root->left);
	cout << root->data << " ";
	InOrderRecursive(root->right);
}

void PostOrderRecursive(pNode root)
{
	if(NULL == root) return;

	PostOrderRecursive(root->left);
	PostOrderRecursive(root->right);
	cout << root->data << " ";
}

void PreOrderNonRecursive(pNode root)
{
	if(NULL == root) return;

	stack<pNode> s;
	pNode p = NULL;
	s.push(root);
	while (!s.empty())
	{
		p = s.top();
		s.pop();
		cout << p->data << " ";
		if(p->right)
			s.push(p->right);
		if(p->left)
			s.push(p->left);
	}
}
void PreOrderNonRecursive2(pNode root)
{
	if(NULL == root) return;

	stack<pNode> s;
	pNode T = root;
	while (T || !s.empty())
	{
		while (T != NULL)
		{
			s.push(T);
			cout << T->data << " ";
			T = T->left;
		}
		if (!s.empty())
		{
			T = s.top();
			s.pop();	
			T = T->right;
		}
	}
}

void inorder2(TreeNode *root)
{
	TreeNode *p = root;
	while (p != NULL)
	{
		if (p->left == NULL)
			cout << p->data << " ", p = p->right;
		else
		{
			TreeNode *pre = p->left;
			while (pre->right != NULL && pre->right != p)
				pre = pre->right;

			if (pre->right == NULL) 
				pre->right = p, p = p->left;
			else                    
				pre->right = NULL, cout << p->data << " ", p = p->right;
		}
	}
}

void InOrderNonRecursive(pNode root)
{
	if(NULL == root) return;

	stack<pNode> s;
	pNode T = root;
	while (T || !s.empty())
	{
		while (T != NULL)
		{
			s.push(T);
			T = T->left;
		}
		if (!s.empty())
		{
			T = s.top();
			s.pop();
			cout << T->data << " ";
			T = T->right;
		}
	}
}

void PostOrderNonRecursive(pNode root)
{
	if(NULL == root) return;

	stack<pNode> s, v;
	pNode T = NULL;
	s.push(root);
	while (!s.empty())
	{
		T = s.top();
		s.pop();
		v.push(T);
		if(T->left) s.push(T->left);
		if(T->right) s.push(T->right);
	}
	while (!v.empty())
	{
		T = v.top();
		v.pop();
		cout << T->data << " ";
	}
}

struct SNode
{
	TreeNode* p;
	int rvisited;
	SNode(TreeNode* pT, int rv) : p(pT), rvisited(rv){}
};

void PostOrderNonRecursive2(pNode root)
{
	if(root == NULL) return;

	stack<SNode*>  s;
	while (root)
	{
		SNode* sn = new SNode(root, 0);
		s.push(sn);
		root = root->left;
	}
	while (!s.empty())
	{
		SNode* sn = s.top();

		if (!sn->p->right || sn->rvisited)
		{
			s.pop();
			cout << sn->p->data << " ";
		}
		else
		{
			sn->rvisited = 1;
			TreeNode* p = sn->p->right;
			while (p != NULL)
			{
				SNode* st = new SNode(p, 0);
				s.push(st);
				p = p->left;
			}
		}
	}
}

void CreateTree(pNode& root)
{
	int ch;
	cin >> ch;

	if (ch == 0)
	{
		root = NULL;
	}
	else
	{
		root = (TreeNode*)malloc(sizeof(TreeNode));
		if (root == NULL)
		{
			return;
		}
		root->data = ch;
		CreateTree(root->left);
		CreateTree(root->right);
	}
	return ;
}

int main()
{
	pNode root = NULL; 
	CreateTree(root);
	
	PreOrderRecursive(root);
	cout << endl;
	PreOrderNonRecursive(root);
	cout << endl;
	PreOrderNonRecursive2(root);
	cout << endl;

	InOrderRecursive(root);
	cout << endl;
	InOrderNonRecursive(root);
	cout << endl;
	inorder2(root);
	cout << endl;

	PostOrderRecursive(root);
	cout << endl;
	PostOrderNonRecursive2(root);
	cout << endl;
	PostOrderNonRecursive(root);
	cout << endl;
	
	system("pause");
	return 0;
}

