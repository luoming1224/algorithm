// BM.cpp : 
//

//#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

#define MAX_CHAR 256
#define SIZE 256
#define MAX(x,y) (x) > (y) ? (x) : (y)

void PreBmBc(const char* pattern, int bmBc[])
{
	int i = 0;
	int m = strlen(pattern);
	for (; i < MAX_CHAR; i++)
	{
		bmBc[i] = m;
	}
	for (i = 0; i < m-1; i++)
	{
		bmBc[(int)pattern[i]] = m - 1 - i;
	}
}

void suffix_old(const char* pattern, int suff[])
{
	int i, j;
	int m = strlen(pattern);
	suff[m-1] = m;
	for (i = m-2; i >= 0; i--)
	{
		j = i;
		while (j >= 0 && pattern[j] == pattern[m-1-i+j])
		{
			j--;
		}
		suff[i] = i - j;
	}
}

void PreBmGs(const char* pattern, int bmGs[])
{
	int i, j;
	int suff[SIZE];
	int m = strlen(pattern);

	suffix_old(pattern, suff);

	for (i = 0; i < m; i++)
	{
		bmGs[i] = m;
	}

	j = 0;
	for (i = m-1; i >= 0; i--)
	{
		if (suff[i] == i+1)
		{
			for (; j < m - 1 -i; j++)
			{
				if (bmGs[j] == m)
				{
					bmGs[j] = m-1-i;
				}
			}
		}
	}

	for (i = 0; i <= m-2; i++)
	{
		bmGs[m-1-suff[i]] = m - 1 - i;
	}
}

int BoyerMoore(const char* pattern, const char* text)
{
	int i, j, bmBc[MAX_CHAR], bmGs[SIZE];
	int n = strlen(text);
	int m = strlen(pattern);

	PreBmBc(pattern, bmBc);
	PreBmGs(pattern, bmGs);
	
	j = 0;
	while (j < n - m + 1)
	{
		for (i = m-1; i >= 0; i--)
		{
			if (pattern[i] != text[j+i])
			{
				break;
			}
		}
		if (i < 0)
		{
//			j += bmGs[0];
			return j;
		}
		else
		{
			j += MAX(bmBc[text[j+i]]-(m-1-i), bmGs[i]);
		}
	}

}

int main()
{
	std::string src = "abcdefghijklmn";
	std::string pat = "lmn";
	int ret = BoyerMoore(pat.c_str(), src.c_str());
	printf("%d\n", ret);
	system("pause");
	return 0;
}

