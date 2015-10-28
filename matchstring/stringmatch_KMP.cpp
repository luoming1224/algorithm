// stringmatch.cpp : 
//

#include "stdafx.h"
#include <stdlib.h>

int next[7] = {0};

void GetNextval(char* p, int next[])
{
	int pLen = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < pLen - 1)
	{
		if (k == -1 || p[j] == p[k])
		{
			++j;
			++k;
			if (p[j] != p[k])
				next[j] = k;   
			else
				next[j] = next[k];
		}
		else
		{
			k = next[k];
		}
	}
}

int KmpSearch(char* s, char* p)
{
	int i = 0;
	int j = 0;
	int sLen = strlen(s);
	int pLen = strlen(p);
	while (i < sLen && j < pLen)
	{   
		if (j == -1 || s[i] == p[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == pLen)
		return i - j;
	else
		return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char *s = "BBC ABCDAB ABCDABCDABDE";
	char *p = "ABCDABD";
//	int ret = KmpSearch(s, p);
	int ret = violentMatch(s, p);
	printf("%d\n", ret);
	system("pause");
	return 0;
}

