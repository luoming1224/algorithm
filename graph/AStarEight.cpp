// AStarEight.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

void swap(int *a, int *b)   
{   
	int temp = *a;   
	*a = *b;   
	*b = temp;   
}   

int d[]={1,3,-1,-3};

struct node   
{     
	int data[9];   
	int zeroPos;   
	int distanceToOri;   
	int distanceToDis;   
	node *parent;   
  
	node(){}   
	node(node* tnode)
	{
		for (int i = 0; i < 9; i++)
		{
			data[i] = tnode->data[i];
		}
		zeroPos = tnode->zeroPos;
		distanceToDis = tnode->distanceToDis;
		distanceToOri = tnode->distanceToOri;
		parent  = tnode->parent;
	}
	node(int *data, int zeroPos, node *parent, int disToOri, int disToDis)   
		:zeroPos(zeroPos),parent(parent),distanceToOri(disToOri),   
		distanceToDis(disToDis)   
	{   
		memcpy(this -> data, data,sizeof(int)*9);   
	}   
	void setParent(node *parent)   
	{   
		this -> parent = parent;   
	}   
	int getRight()   
	{   
		return distanceToDis + distanceToOri;   
	}   
	
	bool operator<(node tnode)
	{
		return getRight() > tnode.getRight();
	}
/*
	node& operator=(const node& tnode)
	{
		if(this == &tnode) return *this;
		for (int i = 0; i < 9; i++)
		{
			data[i] = tnode.data[i];
		}
		zeroPos = tnode.zeroPos;
		distanceToOri = tnode.distanceToOri;
		distanceToDis = tnode.distanceToDis;
		parent = tnode.parent;
	}
*/
};  
typedef std::vector<node*> vecNode;
vecNode openList;   
vecNode closeList;  

bool check(node* tnode, int i)
{
	int spac = tnode->zeroPos;
	if(i==0 && spac%3==2 || i==1 && spac>5   
		|| i==2 && spac%3==0 || i==3 && spac<3)  
		return 0;  
	return 1;
}

void Extend(node* tnode, int i)
{
	int spac = tnode->zeroPos;
	int tmp = spac + d[i];
	tnode->data[spac] = tnode->data[tmp];
	tnode->data[tmp] = 0;
	tnode->zeroPos = tmp;
}

bool compareNode(node* node1, node* node2)
{
	if (NULL == node1 || NULL == node2)
	{
		return false;
	}
	for (int i = 0; i < 9; i++)
	{
		if (node1->data[i] != node2->data[i])
		{
			return false;
		}
	}
	return true;
}

bool inCloseList(node* _node)
{
	vecNode::iterator it = closeList.begin();
	vecNode::iterator end = closeList.end();
	for (; it != end; ++it)
	{
		if (compareNode(_node, *it))
		{
			return true;
		}
	}
	return false;
}

node* findinOpenList(node* _node)
{
	vecNode::iterator it = openList.begin();
	vecNode::iterator end = openList.end();
	for (; it != end; ++it)
	{
		if (compareNode(_node, *it))
		{
			return *it;
		}
	}
	return NULL;
}

int calDistanceToDis(node* cur, node* fin)
{
	int ret = 0;
	for (int i = 0; i < 9; i++)
	{
		if (cur->data[i] != fin->data[i])
		{
			ret++;
		}
	}
	return ret;
}

node* findNext()
{
	vecNode::iterator it = openList.begin();
	node* result = NULL;
	int nsize = openList.size();
	if (nsize == 1)
	{
		result = *it;
		closeList.push_back(result);
		openList.clear();
	}
	else if (nsize > 1)
	{
		vecNode::iterator end = openList.end();
		vecNode::iterator minNode = openList.begin();
		int minRight = (*minNode)->getRight();
		++it;
		for (; it != end; ++it)
		{
			int cur = (*it)->getRight();
			if (cur < minRight)
			{
				minRight = cur;
				minNode = it;
			}
		}
		result = *minNode;
		closeList.push_back(result);
		openList.erase(minNode);
	}
	return result;
}

int getSpacePostion(int A[])
{
	for (int i = 0; i < 9; i++)
	{
		if (A[i] == 0)
		{
			return i;
		}
	}
}

void printPath(node* distination, int* first)
{
	std::vector<int *> path;   
	if(distination != NULL && distination -> parent != NULL)   
	{   
		node *temp = distination;   
		while(temp -> parent != NULL)   
		{   
			path.push_back(temp -> data);   
			temp = temp -> parent;   
		}   
	}   
	path.push_back(first);   
	std::vector<int *>::iterator it = path.end();   
	--it;   
	std::vector<int *>::iterator begin = path.begin();   
	for( ; it != begin; --it)   
	{   
		for(int i = 0; i < 9; ++i)   
		{   
			printf(" %d",(*it)[i]);   
			if( (i + 1) % 3 == 0)   
				printf("\n");   
		}   
		printf("\n");   
	}   
	for(int i = 0; i < 9; ++i)   
	{   
		printf(" %d",(*it)[i]);   
		if( (i + 1) % 3 == 0)   
			printf("\n");   
	}
}

void recoverResource()
{
	vecNode::iterator it1 = openList.begin();
	for (; it1 != openList.end(); ++it1)
	{
		delete *it1;
	}
	openList.clear();

	vecNode::iterator it2 = closeList.begin();
	for (; it2 != closeList.end(); ++it2)
	{
		delete *it2;
	}
	closeList.clear();
}

 void processCur(node *cur, node* fin)
 {
	 for (int i = 0; i < 4; i++)
	 {
		 if (check(cur, i))
		 {
			 node* tmp = new node(cur->data, cur->zeroPos, cur->parent, cur->distanceToOri, cur->distanceToDis);
			 Extend(tmp, i);
			 if (!inCloseList(tmp))
			 {
				 node* temp = NULL;
				 if ( (temp = findinOpenList(tmp)) == NULL )
				 {
					 tmp->distanceToOri = cur->distanceToOri + 1;
					 tmp->distanceToDis = calDistanceToDis(tmp, fin);
					 tmp->parent = cur;
					 openList.push_back(tmp);
				 }
				 else
				 {
					int ftemp = temp->distanceToOri + temp->distanceToDis;
					int gtmp = cur->distanceToOri + 1;
					int htmp = calDistanceToDis(tmp, fin);
					if (gtmp + htmp < ftemp)
					{
						temp->distanceToOri = gtmp;
						temp->distanceToDis = htmp;
						temp->parent = cur;
					}
					delete tmp;
				 }
			 }
			 else
				 delete tmp;
		 }
	 }
 }

void AStar(int grid[], int target[])
{
	int zeroPos = getSpacePostion(grid);
	int finZeroPos = getSpacePostion(target);
	node *ori = new node(grid,zeroPos,NULL,0,0); 
	openList.push_back(ori);
	node *finish = new node(target,finZeroPos,NULL,0,0);

	node *distination = NULL;  
	int first[9];   
	memcpy(first,grid,sizeof(int)*9); 

	while (openList.size() > 0)
	{
		if( (distination = findinOpenList(finish)) != NULL)   
		{   
			break;   
		}   
		node* temp = findNext();
		if (NULL != temp)
		{
			processCur(temp, finish);
		}
	}

	printPath(distination, first);
	
}

int main()
{
	int ori[9] = {1,2,5,7,6,4,0,8,3};   
	int tar[9] = {7,1,5,8,2,4,6,0,3};  
	AStar(ori, tar);
	recoverResource();
	system("pause");
	return 0;
}

