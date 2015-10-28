#include <stdio.h>
#include <stdlib.h>

typedef struct Heapstruct 
{
	int *Elements;
	int size;
	int capacity;
}Heap;

Heap *MaxHeap;
Heap *MinHeap;

Heap* Create(int MaxSize)
{
	Heap* H = (Heap*)malloc( sizeof(struct Heapstruct) );
	H->Elements =(int*) malloc( MaxSize * sizeof(int) );
	H->size = 0;
	H->capacity = MaxSize;
	return H;
}

void InsertMaxHeap(Heap* H, int item)
{
	int i = H->size++;
	int p = (i-1)/2;
	for (; i > 0 && H->Elements[p] < item; )
	{
		H->Elements[i] = H->Elements[p];
		i = p;
		p = (i-1)/2;
	}
	H->Elements[i] = item;
}

int DeleteMaxHeap(Heap* H)
{
	int MaxItem = H->Elements[0];
	int tmp = H->Elements[--H->size];
	int p = 0;
	int s = 2 * p + 1;
	while (s < H->size)
	{
		if (s < H->size-1 && H->Elements[s] < H->Elements[s+1])
		{
			s += 1;
		}
		if (H->Elements[s] > tmp)
		{
			H->Elements[p] = H->Elements[s];
			p = s;
			s = 2 * p + 1;
		}
		else
			break;
	}
	H->Elements[p] = tmp;

	return MaxItem;
}

void InsertMinHeap(Heap* H, int item)
{
	int i = H->size++;
	int p = (i-1)/2;
	for (; i > 0 && H->Elements[p] > item; )
	{
		H->Elements[i] = H->Elements[p];
		i = p;
		p = (i-1)/2;
	}
	H->Elements[i] = item;
}

int DeleteMinHeap(Heap* H)
{
	int MaxItem = H->Elements[0];
	int tmp = H->Elements[--H->size];
	int p = 0;
	int s = 2 * p + 1;
	while (s < H->size)
	{
		if (s < H->size-1 && H->Elements[s] > H->Elements[s+1])
		{
			s += 1;
		}
		if (H->Elements[s] < tmp)
		{
			H->Elements[p] = H->Elements[s];
			p = s;
			s = 2 * p + 1;
		}
		else
			break;
	}
	H->Elements[p] = tmp;

	return MaxItem;
}

int main()
{
	int N;
	scanf("%d", &N);
	MaxHeap = Create(N);
	MinHeap = Create(N);
	int t1, t2;
	scanf("%d", &t1);
	printf("%.1f\n", (float)t1);
	scanf("%d", &t2);
	printf("%.1f\n", (float)(t1+t2)/2);
	if (t1 > t2)
	{
		MaxHeap->Elements[0] = t2;
		MinHeap->Elements[0] = t1;
		MaxHeap->size++;
		MinHeap->size++;
	}
	else
	{
		MaxHeap->Elements[0] = t1;
		MinHeap->Elements[0] = t2;
		MaxHeap->size++;
		MinHeap->size++;
	}

	for (int i = 0; i < N-2; i++)
	{
		scanf("%d", &t1);
		if (t1 < MaxHeap->Elements[0])
		{
			InsertMaxHeap(MaxHeap, t1);
		}
		else
		{
			InsertMinHeap(MinHeap, t1);
		}
		if (MaxHeap->size - MinHeap->size > 1)
		{
			int tmp = DeleteMaxHeap(MaxHeap);
			InsertMinHeap(MinHeap, tmp);
		}
		else if (MinHeap->size - MaxHeap->size > 1)
		{
			int tmp = DeleteMinHeap(MinHeap);
			InsertMaxHeap(MaxHeap, tmp);
		}
		if (MaxHeap->size == MinHeap->size)
		{
			printf("%.1f\n", (float)(MaxHeap->Elements[0] + MinHeap->Elements[0])/2);
		}
		else if (MaxHeap->size > MinHeap->size)
		{
			printf("%.1f\n", (float)MaxHeap->Elements[0]);
		}
		else
		{
			printf("%.1f\n", (float)MinHeap->Elements[0]);
		}
	}

	return 0;
}