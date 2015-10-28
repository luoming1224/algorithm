// trie.cpp : 
//

//#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

typedef struct trie_node 
{
	int count;
	char translate[15];
	bool exist;
	struct trie_node* next[26];
}TrieNode, *Trie;

TrieNode* CreateNode()
{
	TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
	node->count = 0;
	node->exist = false;
	memset(node->next, 0, sizeof(node->next));
	return node;
}

void Trie_insert(Trie root, const char* word, const char* translateword)
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
		++p;
		node->count += 1;
	}
	node->exist = true;
//	strcpy(node->translate, translateword);
	memcpy(node->translate, translateword, 10);
}

const char* Trie_search(Trie root, const char* word)
{
	Trie node = root;
	const char* p = word;
	int id;
	while (*p)
	{
		id = *p - 'a';
		node = node->next[id];
		++p;
		if (node == NULL)
		{
			return word;
		}
	}
	if (node->exist == true)
	{
		return node->translate;
	}
	else
		return word;
}

int main()
{
	Trie root = CreateNode();
	string str1, str2;
	char buffer[3005], str[3005];
	while ( cin >> str1 )
	{
		if (str1 == "START")
		{
			continue;
		}
		else if (str1 == "END")
		{
			break;
		}
		cin >> str2;
		Trie_insert(root, str2.c_str(), str1.c_str());
	}

	int k = 0;
	while (gets(buffer))
	{
		if (strcmp(buffer, "START") == 0)
		{
			continue;
		}
		else if (strcmp(buffer, "END") == 0)
		{
			break;
		}
		for (int i = 0; buffer[i] != '\0'; i++)
		{
			if (buffer[i] >= 'a' && buffer[i] <= 'z')
			{
				str[k++] = buffer[i];
			}
			else
			{
				str[k] = '\0';
				if (k > 0)
				{
					const char* opstr = Trie_search(root, str);
					printf("%s", opstr);
				}
				
				printf("%c", buffer[i]);
				k = 0;
			}
		}
		printf("\n");
	}

	printf("\n");
	getchar();
	return 0;
}

/*
#include<iostream>
#include<cstring>
using namespace std;

typedef struct Trie_node
{
	int count;                    // 统计单词前缀出现的次数
	struct Trie_node* next[26];   // 指向各个子树的指针
	bool exist;                   // 标记该结点处是否构成单词  
	char trans[11];               // 翻译
}TrieNode , *Trie;

TrieNode* createTrieNode()
{
	TrieNode* node = (TrieNode *)malloc(sizeof(TrieNode));
	node->count = 0;
	node->exist = false;
	memset(node->next , 0 , sizeof(node->next));    // 初始化为空指针
	return node;
}

void Trie_insert(Trie root, char* word , char* trans)
{
	Trie node = root;
	char *p = word;
	int id;
	while( *p )
	{
		id = *p - 'a';
		if(node->next[id] == NULL)
		{
			node->next[id] = createTrieNode();
		}
		node = node->next[id];  // 每插入一步，相当于有一个新串经过，指针向下移动
		++p;
		node->count += 1;      // 这行代码用于统计每个单词前缀出现的次数（也包括统计每个单词出现的次数）
	}
	node->exist = true;        // 单词结束的地方标记此处可以构成一个单词
	strcpy(node->trans , trans);
}

char* Trie_search(Trie root, char* word)
{
	Trie node = root;
	char *p = word;
	int id;
	while( *p )
	{
		id = *p - 'a';
		node = node->next[id];
		++p;
		if(node == NULL)
			return 0;
	}
	if(node->exist)          // 查找成功
		return node->trans;
	else                     // 查找失败
		return NULL;
}

int main(void)
{
	Trie root = createTrieNode();     // 初始化字典树的根节点
	char str1[3003] , str2[3003] , str[3003] , *p;
	int i , k;

	scanf("%s",str1);
	while(scanf("%s",str1) && strcmp(str1 , "END") != 0)
	{
		scanf("%s",str2);
		Trie_insert(root , str2 , str1);
	}

	getchar();
	gets(str1);
	k = 0;
	while(gets(str1))
	{
		if(strcmp(str1 , "END") == 0)
			break;
		for(i = 0 ; str1[i] != '\0' ; ++i)
		{
			if(str1[i] >= 'a' && str1[i] <= 'z')
			{
				str[k++] = str1[i];
			}
			else
			{
				str[k] = '\0';
				p = Trie_search(root , str);
				if(p)
					printf("%s", p);
				else
					printf("%s", str);
				k = 0;
				printf("%c", str1[i]);
			}
		}
		printf("\n");
	}
	getchar();
	return 0;
}
*/
