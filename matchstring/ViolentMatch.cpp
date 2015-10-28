// ViolentMatch.cpp : 
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ViolentMatch(char* s, char* p)
{
	if (s == NULL || p == NULL)
	{
		return -1;
	}

	int slen = strlen(s);
	int plen = strlen(p);
	int i =0,  j = 0;
	while (i < slen && j < plen)
	{
		if (p[j] == s[i])
		{
			j++;
			i++;
		}
		else
		{
			j = 0;
			i = i - (j - 1);
		}
	}
	if (j == plen)
	{
		return i - j;
	}
	return -1;
}

int violent_Match(char* s, char* p)
{
	if (s == NULL || p == NULL)
	{
		return -1;
	}
	int slen = strlen(s);
	int plen = strlen(p);
	for (int i = 0; i < slen; i++)
	{
		int j = 0;
		for (; j < plen; j++)
		{

			if (s[i+j] != p[j])
			{
				break;
			}
		}
		if (j == plen)
		{
			return i;
		}
	}
	return -1;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char *s = "abcdef";
	char *p = "fe";
	int ret = ViolentMatch(s, p);
	printf("ret[%d]\n", ret);
	system("pause");
	return 0;
}

