#coding=utf8
def Partition(L, left, right):
    key = L[right]
    i = left
    j = right - 1
    while True:
        while L[i] < key:
            i += 1
        while L[j] > key:
            j -= 1
        if i < j:
            L[i], L[j] = L[j], L[i]
        else:
            break
    L[i], L[right] = L[right], L[i]
    return i

def QuickSort(L, p, r):
    if p < r:
        q = Partition(L, p, r)
        quick_sort(L, q, q-1)
        quick_sort(L, q+1, r)



def quick_sort(L, left, right):
	if left >= right:
		return
	i = left
	j = right-1
	key = L[right]
	while True:
		while L[i] < key:
			i += 1
		while L[j] > key:
			j -= 1
		if i < j:
			L[i], L[j] = L[j], L[i]
		else:
			break
	L[right] = L[i]
	L[i] = key
	
	quick_sort(L, left, i-1)
	quick_sort(L, i+1, right)
	


if __name__ == '__main__':
	L = [3, 2, 4, 6, 5, 1]
	print L
	quick_sort(L, 0, 5)
	print L

		
		
		
		
		
		
		
		
		
		