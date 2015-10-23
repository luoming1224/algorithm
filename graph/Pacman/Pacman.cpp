// Pacman.cpp : 
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

int r0, c0;
int dr,dc;
int row, column;
char **gmap;

struct node 
{
	int r;
	int c;
	int f;
	int h;
	node* parent;
//	node(){}
	node(int nr, int nc, node* p, int nf, int nh)
		:r(nr), c(nc), parent(p), f(nf), h(nh)
	{
	
	}

	~node(){init();}

	void init()
	{
		r = c = f = h = 0;
		parent = NULL;
	}

	int calcHeuristic()
	{
		int dist = abs(dr - r) + abs(dc - c);
		return dist;
	}

	bool operator<(const node& tnode)
	{
		if (f + h > tnode.f + tnode.h)
		{
			return true;
		}
		return false;
	}
	
};

typedef vector<node*>	vecNode;
vecNode			openlist;
vecNode			closelist;

void recoverResource()
{
	vecNode::iterator it1 = openlist.begin();
	for (; it1 != openlist.end(); ++it1)
	{
		delete *it1;
		*it1 = NULL;
	}
	openlist.clear();

	vecNode::iterator it2 = closelist.begin();
	for (; it2 != closelist.end(); ++it2)
	{
		delete *it2;
		*it2 = NULL;
	}
	closelist.clear();

	for (int i = 0; i < row; i++)
	{
		delete[] gmap[i];
		gmap[i] = NULL;
	}
	delete[] gmap;
	gmap = NULL;
}

//UP(0), LEFT(1), RIGHT(2) and DOWN(3) 

node* inOpenlist(node* _node)
{
	vecNode::iterator it = openlist.begin();
	vecNode::iterator end = openlist.end();
	for (; it != end; ++it)
	{
		if ((*it)->r == _node->r && (*it)->c == _node->c)
		{
			return *it;
		}
	}
	return NULL;
}

bool inCloselist(node* _node)
{
	vecNode::iterator it = closelist.begin();
	vecNode::iterator end = closelist.end();
	for (; it != end; ++it)
	{
		if ((*it)->r == _node->r && (*it)->c == _node->c)
		{
			return true;
		}
	}
	return false;
}

node* findPrioNode()
{
	vecNode::iterator it = openlist.begin();
	node* result = NULL;
	int nsize = openlist.size();
	if (nsize == 1)
	{
		result = *it;
		closelist.push_back(result);
		openlist.clear();
	}
	else if (nsize > 1)
	{
		vecNode::iterator end = openlist.end();
		vecNode::iterator minNode = openlist.begin();
		int minDist = (*minNode)->f + (*minNode)->h;
		++it;
		for (; it != end; ++it)
		{
			int cur = (*it)->f + (*it)->h;
			if (cur < minDist)
			{
				minDist = cur;
				minNode = it;
			}
		}
		result = *minNode;
		closelist.push_back(result);
		openlist.erase(minNode);
	}
	return result;
}

void AStar()
{
//	node oriNode(r0, c0, 0, 0);
//	queNode.push(oriNode);
	node* oriNode = new node(r0, c0, NULL, 0, 0);
	oriNode->h = oriNode->calcHeuristic();
	openlist.push_back(oriNode);
	node* finNode = new node(dr, dc, NULL, 0, 0);
	node *distination = NULL;  
	while (openlist.size() > 0)
	{
		if ( (distination = inOpenlist(finNode)) != NULL )
		{
			break;
		}
		node* _node = findPrioNode();

		for (int i = 0; i < 4; i++)
		{
			node* tmpNode = new node(_node->r, _node->c, _node->parent, _node->f, _node->h);
			if (i == 0)
			{
				tmpNode->r = tmpNode->r - 1;
		
				if (tmpNode->r < 0 || (tmpNode->r >= 1 && gmap[tmpNode->r][tmpNode->c] == '%'))
				{
					delete tmpNode;
					continue;
				}
			}
			else if (i == 1)
			{
				
				tmpNode->c = tmpNode->c - 1;
				if (tmpNode->c < 0 || gmap[tmpNode->r][tmpNode->c] == '%')
				{
					delete tmpNode;
					continue;
				}
			}
			else if (i == 2)
			{
				
				tmpNode->c = tmpNode->c + 1;
				if (tmpNode->c >= column || gmap[tmpNode->r][tmpNode->c] == '%')
				{
					delete tmpNode;
					continue;
				}
			}
			else if (i == 3)
			{
				tmpNode->r = tmpNode->r + 1;
				
				if (tmpNode->r >= row || gmap[tmpNode->r][tmpNode->c] == '%')
				{
					delete tmpNode;
					continue;
				}
			}

			if (!inCloselist(tmpNode))
			{
				tmpNode->f = _node->f + 1;
				tmpNode->h = tmpNode->calcHeuristic();
//				queNode.push(tmpNode);
				node *temp = NULL;
				if ((temp = inOpenlist(tmpNode)) == NULL)
				{
					tmpNode->parent = _node;
					openlist.push_back(tmpNode);
				}
				else
				{
					if (tmpNode->f + tmpNode->h < temp->f + temp->h)
					{
						temp->f = tmpNode->f;
						temp->h = tmpNode->h;
						temp->parent = _node;
					}
					delete tmpNode;
				}
			}
			
		}
	}

	vecNode path;

	if(distination != NULL && distination -> parent != NULL)   
	{   
		node *temp = distination;   
		while(temp -> parent != NULL)   
		{   
			path.push_back(temp);   
			temp = temp -> parent;   
		}   
	}
	printf("%d\n", distination->f);
	path.push_back(oriNode);
	vecNode::iterator it = path.end();
	--it;
	vecNode::iterator begin = path.begin();
	for (; it != begin; --it)
	{
		printf("%d %d\n", (*it)->r, (*it)->c);
	}
	printf("%d %d\n", (*it)->r, (*it)->c);

}

int main()
{
	scanf("%d %d", &r0, &c0);
	scanf("%d %d", &dr, &dc);
	scanf("%d %d\n", &row, &column);
	char tmp;
	gmap = new char *[row];
	for (int i = 0; i < row; i++)
	{
		gmap[i] = new char[column];
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			scanf("%c", &gmap[i][j]);
		}
		scanf("%c", &tmp);
	}
	
	AStar();

	recoverResource();

	system("pause");
	return 0;
}

