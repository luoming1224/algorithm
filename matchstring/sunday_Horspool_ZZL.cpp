// sunday.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

int Horspool(const char* s, const char* p)		//从右向左匹配
{
	if (NULL == s || NULL == p)
	{
		return 0;
	}
	int slen = strlen(s);
	int plen = strlen(p);

	int next[256] = {0};
	for (int i = 0; i < 256; i++)
	{
		next[i] = plen;
	}
	for (int j = 0; j < plen; j++)
	{
		next[(int)p[j]] = plen - 1 - j;
	}

	int pos = 0;
	while (pos < (slen-plen+1))
	{
		int k = plen-1;
		for (; k >= 0; k--)
		{
			if (p[k] != s[pos+k])
			{
				pos += next[(int)s[pos+plen-1]];
				break;
			}
		}
		if (k == -1)
		{
			return pos;
		}
	}
	return -1;
}

int sunday(const string& s, const string& p)			//从左向右匹配
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
			count++;
			if (pos + plen >= slen)
			{
				flag = true;
				break;
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

int zzl(const char* s, const char* p)
{
	if (NULL == s || NULL == p)
	{
		return 0;
	}
	int slen = strlen(s);
	int plen = strlen(p);

	std::vector<int> vecPos;
	for (int i = 0; i < slen-plen+1; i++)
	{
		if (s[i] == p[0])
		{
			vecPos.push_back(i);
		}
	}

	int size = vecPos.size();
	for (int i = 0; i < size; i++)
	{
		int pos = vecPos[i];
		int j = 1;
		for (; j < plen; j++)
		{
			if (s[pos+j] != p[j])
			{
				break;
			}
		}
		if (j == plen)
		{
			return pos;
		}
	}
	return -1;
}

int main()
{
// 	std::string src = "abcdefghijklmn";
// 	std::string pat = "lmn";
// 	int ret = Horspool(src.c_str(), pat.c_str());
	
	ifstream myfile("D:\\Downloads\\teststring.txt");
	char buffer[1005] = {0};
	myfile.getline(buffer, 1005);
	myfile.close();

	string s(buffer);
	printf("%d\n", s.length());

	int reta = sunday(s, "a");
	int retb = sunday(s, "b");
	int retab = sunday(s, "ab");
	int retabb = sunday(s, "abb");
	

	printf("%d %d %d %d\n", reta, retb, retab, retabb);
	system("pause");
	return 0;
}

