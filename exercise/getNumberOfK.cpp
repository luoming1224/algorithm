#include <iostream>

/**
*  题目：统计一个数字：在排序数组中出现的次数。
*  举例说明
*  例如输入排序数组｛ 1, 2, 3, 3, 3, 3, 4, 5｝和数字 3 ，由于 3 在这个数组中出现了 4 次，因此输出 4 。
*  参考　http://wiki.jikexueyuan.com/project/for-offer/question-thirty-eight.html
*
**/
using namespace std;

int findFirstOccurrence(int A[], int size, int num) {
    if (A == nullptr || size < 0)
        return -1;
    int l = 0, r = size - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (A[m] < num) {
            l = m + 1;
        } else if (A[m] > num) {
            r = m -1;
        } else {
            if (m > 0 && A[m-1] != num || m == 0) {
                return m;
            }
            r = m - 1;
        }
    }
    return -1;
}

int findLastOccurrence(int A[], int size, int num) {
    if (A == nullptr || size < 0)
        return -1;
    int l = 0, r = size - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (A[m] < num) {
            l = m + 1;
        } else if (A[m] > num) {
            r = m -1;
        } else {
            if (m + 1 < size && A[m+1] != num || m == size - 1) {
                return m;
            }
            l = m + 1;
        }
    }
    return -1;
}

int getNumberOfK(int A[], int size, int num) {
    if (A == nullptr || size < 0)
        return -1;
    int first = findFirstOccurrence(A, size, num);
    int last = findLastOccurrence(A, size, num);
    if (first > -1 && last > -1) {
        return last - first + 1;
    }
    return 0;
}


int main(int argc, char **argv) {
// 查找的数字出现在数组的中间
    int data1[] = {1, 2, 3, 3, 3, 3, 4, 5};
    cout << getNumberOfK(data1, sizeof(data1)/sizeof(int), 3) << endl; // 4
    // 查找的数组出现在数组的开头
    int data2[] = {3, 3, 3, 3, 4, 5};
    cout << getNumberOfK(data2, sizeof(data2)/sizeof(int), 3) << endl; // 4
    // 查找的数组出现在数组的结尾
    int data3[] = {1, 2, 3, 3, 3, 3};
    cout << getNumberOfK(data3, sizeof(data3)/sizeof(int), 3) << endl; // 4
    // 查找的数字不存在
    int data4[] = {1, 3, 3, 3, 3, 4, 5};
    cout << getNumberOfK(data4, sizeof(data4)/sizeof(int), 2) << endl; // 0
    // 查找的数字比第一个数字还小，不存在
    int data5[] = {1, 3, 3, 3, 3, 4, 5};
    cout << getNumberOfK(data5, sizeof(data5)/sizeof(int), 0) << endl; // 0
    // 查找的数字比最后一个数字还大，不存在
    int data6[] = {1, 3, 3, 3, 3, 4, 5};
    cout << getNumberOfK(data6, sizeof(data6)/sizeof(int), 0) << endl; // 0
    // 数组中的数字从头到尾都是查找的数字
    int data7[] = {3, 3, 3, 3};
    cout << getNumberOfK(data7, sizeof(data7)/sizeof(int), 3) << endl; // 4
    // 数组中的数字从头到尾只有一个重复的数字，不是查找的数字
    int data8[] = {3, 3, 3, 3};
    cout << getNumberOfK(data8, sizeof(data8)/sizeof(int), 4) << endl; // 0
    // 数组中只有一个数字，是查找的数字
    int data9[] = {3};
    cout << getNumberOfK(data9, sizeof(data9)/sizeof(int), 3) << endl; // 1
    // 数组中只有一个数字，不是查找的数字
    int data10[] = {3};
    cout << getNumberOfK(data10, sizeof(data10)/sizeof(int), 4) << endl; // 0


    return 0;
}
