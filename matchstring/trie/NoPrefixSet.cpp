#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef struct trie_node 
{
	struct trie_node* next[26];
	bool exist;
}TrieNode, *Trie;


TrieNode* CreateNode()
{
	TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
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
		++p;
	}
	node->exist = true;
}

bool isprefix(Trie root, const char* word)
{
	Trie node = root;
	const char* p = word;
	while (*p)
	{
		int id = *p - 'a';
		node = node->next[id];
		if (!node)
		{
			return false;
		}
		if (node && node->exist)
		{
			return true;
		}
		++p;
	}
	if (node && !node->exist)
	{
		return true;
	}
	return false;
}

int main()
{
	Trie root = CreateNode();
	int N;
	scanf("%d", &N);
	char text[61];
	int ret;
	for (int i = 0; i < N; i++)
	{
		scanf("%s", text);
		if (isprefix(root, text))
		{
			printf("BAD SET\n");
			printf("%s\n", text);
			return 0;
		}
		Trie_insert(root, text);
	}

	printf("GOOD SET\n");

	return 0;
}
