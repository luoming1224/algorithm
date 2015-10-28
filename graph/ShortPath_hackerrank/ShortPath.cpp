//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <fstream>

//#include <hash_map>
using namespace std;

const int MAX_NODES = 1000 + 5;

const int INF = 1000000000;
/*
struct cmp{
	bool operator()(int &a, int &b)
	{
		return a > b;
	}
};
*/
int sunday(const string s, const string p)			
{
	if ("" == s || "" == p)
	{
		return 0;
	}
	int slen = s.length();
	int plen = p.length();

	int count = 0;
	int next[256] = {0};
	for (int i = 0; i < 256; i++)
	{
		next[i] = plen+1;
	}
	for (int j = 0; j < plen; j++)
	{
		next[(int)p[j]] = plen - j;
	}

	int pos = 0;
	while (pos < (slen-plen+1))
	{
		int k = 0;
		for (; k < plen; k++)
		{
			if (p[k] != s[pos+k])
			{
				pos += next[(int)s[pos+plen]];
				break;
			}
		}
		if (k == plen)
		{
			//			return pos;
			count++;
			pos += next[(int)s[pos+plen]];
		}
	}
	return count;
}

struct edge 
{
	int to, weight;
	char tag;
	edge(){}
	edge(int to, int weight, char tag)
		:to(to), weight(weight),tag(tag)
	{

	}
// 	bool operator<(const node& rhs)const
// 	{
// 		return x > rhs.x;
// 	}
};

vector<edge> adj[MAX_NODES];
int n, m, x, y, z;
char tag;
string text;

struct vertex 
{
	int x;
	long long f;
	string tag;
	vertex(int x=0, long long f=0, string tag="")
		:x(x), f(f), tag(tag)
	{

	}
	bool operator==(const vertex& rhs)const
	{
		return x == rhs.x;
	}
	bool operator<(const vertex& rhs)const
	{
		return f > rhs.f;
	}
};

priority_queue<vertex>		DataQueue;
map<int, long long>			cost_so_far;

//priority_queue<int>		dataQ;

inline void add_edge (int x, int y, int z, char tag) {
	adj[x].push_back(edge(y, z, tag));
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <=m; i++)
	{
		cin >> x >> y >> z >> tag;
		add_edge(x, y, z, tag);
		add_edge(y, x, z, tag);
	}
	cin >> text;

	vertex start(1, 0, "");
	vertex goal(n);
	DataQueue.push(start);
	cost_so_far[1] = 0;

	while (!DataQueue.empty())
	{
		vertex current = DataQueue.top();
		DataQueue.pop();

		if (current == goal)
		{
			break;
		}

		int index = current.x;
		
		for (int j = 0; j < adj[index].size(); j++)
		{
			edge curEdge = adj[index][j];
			int next = curEdge.to;
			int edge_cost = curEdge.weight;
			char c = curEdge.tag;
			char t[2] = {0};
			t[0] = c;
			string tmp(t);
			string nextTag = current.tag + tmp;
			int count = sunday(text, nextTag);
        if (count == 0)
			{
				continue;
			}
			long long new_cost = cost_so_far[index] + edge_cost*count;
			
			if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				vertex nextVertex(next, new_cost, nextTag);
				DataQueue.push(nextVertex);
			}
		}
	}

	printf("%ld\n", cost_so_far[n]);
	return 0;
}