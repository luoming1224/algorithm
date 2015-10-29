#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

#define ALPHABET 26

typedef struct node 
{
	struct node* next[ALPHABET];
	struct node* fail;
	int patterTag;
	char data[100];
}TreeNode, *Tree;

TreeNode* CreateNode()
{
	TreeNode* tnode = (TreeNode*)malloc(sizeof(TreeNode));
	tnode->fail = NULL;
	tnode->patterTag = 0;
	memset(tnode->next, 0, sizeof(tnode->next));
	memset(tnode->data, 0, sizeof(tnode->data));
	return tnode;
}

void EnQueue(Tree _node, queue<Tree>& TreeQ)
{
	for (int i = 0; i < ALPHABET; i++)
	{
		if (_node->next[i] != NULL)
		{
			TreeQ.push(_node->next[i]);
		}
	}
}

void buildTrieTree(Tree root, const char* word)
{
	Tree p = root;
	int i = 0, index;
	while (word[i])
	{
		index = word[i] - 'a';
		if (p->next[index] == NULL)
		{
			p->next[index] = CreateNode();
		}
		p = p->next[index];
		i++;
	}
	p->patterTag = 1;
	memcpy(p->data, word, 100);
}

void build_AC_Automation(Tree root)
{
	int i;
	queue<Tree> TreeQ;
	root->fail = NULL;
	for (i = 0; i < ALPHABET; i++)
	{
		if (root->next[i] != NULL)
		{
//			EnQueue(root->next[i], TreeQ);
			TreeQ.push(root->next[i]);
			root->next[i]->fail = root;
		}
	}
	Tree tmp = NULL, par = NULL;
	while (!TreeQ.empty())
	{
		tmp = TreeQ.front();
		TreeQ.pop();
//		EnQueue(tmp, TreeQ);
		
//		par = tmp->par;
		for (i = 0; i < ALPHABET; i++)
		{
			if (tmp->next[i] != NULL)
			{
				TreeQ.push(tmp->next[i]);
				par = tmp->fail;
				while (par != NULL)
				{
					if (par->next[i] != NULL)
					{
						tmp->next[i]->fail = par->next[i];
						break;
					}
					par = par->fail;
				}
				if (par == NULL)
				{
					tmp->next[i]->fail = root;
				}
			}
		}

	}
}

int search(Tree root, const char* str)
{
	int len = strlen(str);
	Tree tmp = root;
	int i = 0;
	while (i < len)
	{
		int id = str[i] - 'a';
		if (tmp->next[id] != NULL)
		{
			tmp = tmp->next[id];
			if (tmp->patterTag == 1)
			{
				cout << i - strlen(tmp->data) + 1 << '\t' << tmp->data << endl;
			}
			i++;
		}
		else
		{
			if (tmp == root)
			{
				i++;
			}
			else
			{
				tmp = tmp->fail;
				if (tmp->patterTag == 1)
				{
					cout << i - strlen(tmp->data) + 1 << '\t' << tmp->data << endl;
				}
			}
		}
	}
	while (tmp != root)
	{
		tmp = tmp->fail;
		if (tmp->patterTag == 1)
		{
			cout << i - strlen(tmp->data) + 1 << '\t' << tmp->data << endl;
		}
	}
	return 0;
}

char pattern[4][30]={"nihao","hao","hs","hsr"};

void main()
{
	char a[]="sdmfhsgnshejfgnihaofhsrnihao";
	int i,j;
	Tree root = CreateNode();
	for (i = 0; i < 4; i++)
	{
		buildTrieTree(root, pattern[i]);
	}
	build_AC_Automation(root);
	search(root,a);
	getchar();
}
