#coding=utf8
def merge(left, right):    
	i, j = 0, 0    
	result = []    
	while i < len(left) and j < len(right):        
		if left[i] <= right[j]:            
			result.append(left[i])            
			i += 1        
		else:            
			result.append(right[j])            
			j += 1    
	result += left[i:]    
	result += right[j:]    
	return result 
	
def merge_sort(lists):    # 归并排序    
	if len(lists) <= 1:        
		return lists    
	num = len(lists) / 2    
	left = merge_sort(lists[:num])    
	right = merge_sort(lists[num:])    
	return merge(left, right)



def Merge(L, T, first, mid, last):
    i = first
    leftEnd = mid - 1
    Num = last - first + 1
    while (first <= leftEnd and mid <= last):
        if L[first] <= L[mid]:
            T[i] = L[first]
            i += 1
            first += 1
        else:
            T[i] = L[mid]
            i += 1
            mid += 1

    while first <= leftEnd:
        T[i] = L[first]
        i += 1
        first += 1
    while mid <= last:
        T[i] = L[mid]
        i += 1
        mid += 1

    for k in range(0, Num):
        L[last] = T[last]
        last -= 1


def MSort(L, T, left, right):
    if left < right:
        mid = (left + right) / 2
        MSort(L, T, left, mid)
        MSort(L, T, mid + 1, right)
        Merge(L, T, left, mid + 1, right)


def Merge_Sort(L):
    N = len(L)
    T = []
    for i in range(0, N):
        T.append(0)

    MSort(L, T, 0, N - 1)


if __name__ == '__main__':
    L = [3, 2, 4, 6, 5, 1]
    print L
    T = merge_sort(L)
    print T
    Merge_Sort(L)
    print L

		
		
		
		
		
		
		
		
		
		