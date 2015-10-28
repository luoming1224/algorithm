// trie1.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

typedef struct trie_node 
{
	int count;
	struct trie_node* next[26];
	bool exist;
}TrieNode, *Trie;

TrieNode* CreateNode()
{
	TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
	node->count = 0;
	node->exist = false;
	memset(node->next, 0, sizeof(node->next));
	return node;
}

void Trie_insert(Trie root, const char* word)
{
	Trie node = root;
	const char* p = word;
	int id;
	while (*p)
	{
		id = *p - 'a';
		if (node->next[id] == NULL)
		{
			node->next[id] = CreateNode();
		}
		node = node->next[id];
		node->count++;
		++p;
	}
	node->exist = true;
}

int Trie_search(Trie root, const char* word)
{
	Trie node = root;
	const char* p = word;
	int id;
	while (*p)
	{
		id = *p - 'a';
		if (node->next[id] == NULL)
		{
			return 0;
		}
		node = node->next[id];
		++p;
	}
	return node->count;
}

int main()
{
	Trie root = CreateNode();
	char str[12];
	bool flag = true;
	while (gets(str))
	{
		if (strlen(str) == 0)
		{
			flag = false;
			continue;
		}
		if (flag)
		{
			Trie_insert(root, str);
		}
		else
		{
			int cnt = Trie_search(root, str);
			printf("%d\n", cnt);
		}
		
	}
	
	printf("\n");
	getchar();
//	system("pause");
	return 0;
}

