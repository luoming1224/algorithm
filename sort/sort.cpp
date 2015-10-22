// sorttrain.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void BubbleSort(int A[], int n)
{
	for (int i = n-1; i >= 0; i--)
	{
		bool bFlag = true;
		for (int j = 0; j < i; j++)
		{
			if (A[j] > A[j+1])
			{
				Swap(A[j], A[j+1]);
				bFlag = false;
			}
		}
		if (bFlag)
		{
			break;
		}
	}
}

void SelectSort(int A[], int n)
{
	for (int i = 0; i < n; i++)
	{
		int tmp = A[i];
		int index = i;
		for (int j=i+1; j<n; j++)
		{
			if (A[j] < tmp)
			{
				tmp = A[j];
				index = j;
			}
		}
		if (index != i)
		{
			Swap(A[i], A[index]);
		}
	}
}

void InsertSort(int A[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int j = i;
		int tmp = A[j];
		while(j > 0 && A[j-1] > tmp)
		{
			A[j] = A[j-1];
			j--;
		}
		A[j] = tmp;
	}
}

void ShellSort(int A[], int n)
{
	for (int D = n/2; D > 0; D/=2)
	{
		for (int i = D; i < n; i++)
		{
			int j;
			int tmp = A[i];
			for (j = i; j > 0 && A[j-D] > tmp; j-=D)
			{
				A[j] = A[j-D];
			}
			A[j] = tmp;
		}
	}
}

void PercDown(int A[], int i, int n)
{
	int tmp = A[i];
	int p = i * 2 + 1;
	while(p < n)
	{
		if (p+1 < n && A[p] < A[p+1])
		{
			p+=1;
		}
		if (A[p] > tmp)
		{
			A[i] = A[p];
			i = p;
			p = i * 2 +	1;
		}
		else
			break;
	}
	A[i] = tmp;
}

void HeapSort(int A[], int n)
{
	for (int i = n/2-1; i >= 0; i--)
	{
		PercDown(A, i, n);
	}
	for (int j = n-1; j>0; j--)
	{
		int tmp = A[j];
		A[j] = A[0];
		A[0] = tmp;
		PercDown(A, 0, j);
	}
}

int Partition(int A[], int p, int r)
{
	int x = A[r];
	int i = p-1;
	for (int j = p; j <= r-1; j++)
	{
		if (A[j] <= x)
		{
			i++;
			Swap(A[i], A[j]);
		}
	}
	Swap(A[i+1], A[r]);
	return i+1;
}

int Partitions(int A[], int left, int right)
{
	int npiovt = A[right];
	int l = left, r = right-1;
	for (;;)
	{
		while (A[l] < npiovt)
		{
			l++;
		}
		while (A[r] > npiovt)
		{
			r--;
		}
		if (l < r)
		{
			Swap(A[l], A[r]);
		}
		else
			break;
	}
	Swap(A[l], A[right]);
	return l;
}


void QuickSort(int A[], int p, int r)
{
	if (p < r)
	{
		int q = Partitions(A, p, r);
		QuickSort(A, p, q-1);
		QuickSort(A, q+1, r);
	}
}

void merge(int A[], int T[], int l, int r, int rigthEnd)
{
	int letfEnd = r-1;
	int t = l;
	int num = rigthEnd - l +1;
	while(l <= letfEnd && r <= rigthEnd)
	{
		if (A[l] < A[r])
		{
			T[t++] = A[l++];
		}
		else
		{
			T[t++] = A[r++];
		}
	}
	while (l <= letfEnd)
	{
		T[t++] = A[l++];
	}
	while (r <= rigthEnd)
	{
		T[t++] = A[r++];
	}
	for (int i=num; i>0; i--,rigthEnd--)
	{
		A[rigthEnd] = T[rigthEnd];
	}
}

void MSort(int A[], int T[], int p, int r)
{
	if (p < r)
	{
		int mid = p + (r-p)/2;
		MSort(A, T, p, mid);
		MSort(A, T, mid+1, r);
		merge(A, T, p, mid+1, r);
	}
}

void MergeSort(int A[], int n)
{
	int *T = new int[n];
	if (T != NULL)
	{
		MSort(A, T, 0, n-1);
		delete[] T;
	}	
}


int main()
{
	int A[] = {3, 2, 4, 6, 5, 1};
	int n = sizeof(A)/sizeof(int);
//	MergeSort(A, n);
	QuickSort(A, 0, n-1);
	for (int i = 0; i < n; i++)
	{
		printf("%d  ", A[i]);
	}
	printf("\n");
	system("pause");

	return 0;
}

