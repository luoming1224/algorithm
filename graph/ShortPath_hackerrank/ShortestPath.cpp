// ShortestPath.cpp : 
//

//#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

const int MAX_SA_STATES = 2000 + 5;
const int ALPHABET_SIZE = 26;
const int MAX_NODES = 1000 + 5;
const int INF = 1000000000;
const int MAX_HEAP_NODES = MAX_SA_STATES * MAX_NODES;

struct state {
	int to, weight;
	char tag;
	state () {}
	state (int to, int weight, char tag) : to(to), weight(weight), tag(tag) {}
};

typedef long long ll;

struct vertex
{
	int vtx;
	ll  cost;
	string tag;
	vertex() {}
	vertex(int vtx, ll cost, string tag): vtx(vtx), cost(cost), tag(tag){}
};

vector<state> adj[MAX_NODES];
struct vertex heap[MAX_HEAP_NODES];
map<int, int>	PosMap;
set<int>		closelist;
int heap_size = 0;
int n, m, x, y, z;
char tag;
string text;

int sunday(const char* s, const char* p)			//
{
	if (NULL == s || NULL == p)
	{
		return 0;
	}
	int slen = strlen(s);
	int plen = strlen(p);

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
	bool flag = false;
	while (pos < (slen-plen+1))
	{
		int k = 0;
		for (; k < plen; k++)
		{
			if (p[k] != s[pos+k])
			{
				if (pos + plen >= slen)
				{
					flag = true;
					break;
				}
				pos += next[(int)s[pos+plen]];
				break;
			}
		}
		if (k == plen)
		{
			//			return pos;
			count++;
			if (pos + plen >= slen)
			{
				flag = true;
			}
			pos += next[(int)s[pos+plen]];
		}
		if (flag)
		{
			break;
		}
	}
	return count;
}

inline void add_edge (int x, int y, int z, char tag) {
	adj[x].push_back(state(y, z, tag));
}

void sift_down(int i, int n)
{
	vertex tmp = heap[i];
	int p = i * 2 + 1;
	while(p < n)
	{
		if (p+1 < n && heap[p+1].cost < heap[p].cost)
		{
			p+=1;
		}
		if (heap[p].cost < tmp.cost)
		{
			heap[i] = heap[p];
			PosMap[heap[p].vtx] = i;
			i = p;
			p = i * 2 +	1;
		}
		else
			break;
	}
	heap[i] = tmp;
	PosMap[tmp.vtx] = i;
	//PosMap[heap[i].vtx] = PosMap[tmp.vtx];
}

void sift_up(int position)
{
	int child = position;
	int father = (child-1)/2;
	vertex temp = heap[position];
	while(father >= 0 && child >= 1)
	{
		if (heap[father].cost > temp.cost)
		{
			heap[child] = heap[father];
			PosMap[heap[father].vtx] = child;
			//PosMap[heap[child].vtx] = PosMap[heap[father].vtx];
			child = father;
			father = (child-1)/2;
		}
		else
			break;
	}
	heap[child] = temp;
	PosMap[temp.vtx] = child;
	//PosMap[heap[child].vtx] = PosMap[temp.vtx];
}

inline void heap_add (int vtx, ll cost, string tag) 
{
	heap[heap_size] = vertex(vtx, cost, tag);
	PosMap[vtx] = heap_size;
	sift_up(heap_size);
	++heap_size;
}
void heap_add (vertex rhs)
{
	heap[heap_size] = rhs;
	PosMap[rhs.vtx] = heap_size;
	sift_up(heap_size);
	++heap_size;
}

void map_delete(int key)
{
	map<int, int>::iterator it = PosMap.find(key);
	if (it != PosMap.end())
	{
		PosMap.erase(it);
	}
}

void heap_delete(int position)
{
	if (position >= heap_size)
	{
		cout << "error" << "  " <<  position << "  " << heap_size << endl;
		return;
	}

	heap_size--;
	if (position == heap_size)
	{
		map_delete(heap[heap_size].vtx);
	}
	else if (heap[position].cost > heap[heap_size].cost)
	{
		vertex tmp = heap[position];
		
		heap[position] = heap[heap_size];
		PosMap[heap[heap_size].vtx] = position;
		map_delete(tmp.vtx);
		sift_up(position);
	}
	else if (heap[position].cost < heap[heap_size].cost)
	{
		vertex tmp = heap[position];	
		heap[position] = heap[heap_size];
		PosMap[heap[heap_size].vtx] = position;
		map_delete(tmp.vtx);
		sift_down(position, heap_size);
	}
//	PosMap[heap[position].vtx] = PosMap[heap[heap_size].vtx];
}

vertex get_min()
{
	vertex tmp = heap[0];
	--heap_size;
	heap[0] = heap[heap_size];
	PosMap[heap[heap_size].vtx] = 0;
	map_delete(tmp.vtx);
	sift_down(0, heap_size);
	return tmp;
}

void push(vertex obj)
{
	if (PosMap.count(obj.vtx))
	{
		if (heap[PosMap[obj.vtx]].cost <= obj.cost)
		{
			return;
		}
		heap_delete(PosMap[obj.vtx]);
	}
	heap_add(obj);
}

void Dijkstra(int start, int target)
{
	vertex v1(start, 0, "");
	push(v1);
	while (heap_size > 0)
	{
		/*vertex current = get_min();*/
		vertex current = heap[0];
		int node = current.vtx;
		if (node == target)
		{
			break;
		}
		closelist.insert(node);
		heap_delete(0);
		
		string tag = current.tag;
		for(unsigned int j = 0; j < adj[node].size(); j++)
		{
			if (closelist.count(adj[node][j].to))
			{
				continue;
			}
			char c = adj[node][j].tag;
			char t[2] = {0};
			t[0] = c;
			string tmp(t);
			string nextTag = current.tag + tmp;

			int count = sunday(text.c_str(), nextTag.c_str());
			if (count == 0)
			{
				continue;
			}

			ll new_cost = current.cost + count * adj[node][j].weight;
			
			push(vertex(adj[node][j].to, new_cost, nextTag));
		}
	}

	cout << heap[0].cost << endl;
}



int main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		cin >> x >> y >> z >> tag;
		add_edge(x, y, z, tag);
		add_edge(y, x, z, tag);
	}
	cin >> text;

	Dijkstra(1, n);

	system("pause");
	return 0;
}

