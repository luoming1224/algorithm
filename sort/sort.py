def Bubble_sort(L, N):
    for i in range(0, N-1)[::-1]:
        for j in range(0, i+1):
            if L[j] > L[j+1]:
                t = L[j]
                L[j] = L[j+1]
                L[j+1] = t

def select_sort(L, N):
    for i in range(0, N-1):
        min = L[i]
        index = i
        for j in range(i+1, N):
            if L[j] < min:
                min = L[j]
                index = j
        if index != i:
            L[index] = L[i]
            L[i] = min


def insert_sort(L, N):
    for i in range(1, N):
        j = i
        tmp = L[i]
        while j > 0 and tmp < L[j-1]:
            L[j] = L[j-1]
            j -= 1
        L[j] = tmp


def partition(L, left, right):
    pivot = L[right]
    j = left
    for i in range(left, right):
        if L[i] < pivot :
            tmp = L[j]
            L[j] = L[i]
            L[i] = tmp
            j += 1
    L[right] = L[j]
    L[j] = pivot
    return j

def quick_sort(L, left, right):
    if left < right:
        q = partition(L, left, right)
        quick_sort(L, left, q-1)
        quick_sort(L, q+1, right)


def adjust_heap(L, i, size):
    tmp = L[i]
    j = i * 2 + 1
    while j < size:
        if j + 1 < size and L[j] < L[j+1]:
            j += 1
        if tmp < L[j]:
            L[i] = L[j]
            i = j
            j = i * 2 + 1
        else:
            break
    L[i] = tmp

def heap_sort(L, size):
    for i in range(0, (size/2))[::-1]:
        adjust_heap(L, i, size)

    for j in range(0, size)[::-1]:
        L[0], L[j] = L[j], L[0]
        adjust_heap(L, 0, j)



if __name__ == '__main__':
    L = [3,2,9,4,8,5,7,6,1]
    heap_sort(L, 9)
    print L