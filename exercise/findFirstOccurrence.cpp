#include <iostream>

/**
*  一组已经排序的数，数字可能有重复，找出某个数字第一次出现的位置
*
**/
using namespace std;

int findFirstOccurrence(int A[], int size, int num) {
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


int main(int argc, char **argv) {
/**
 * A[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; //find 1; position = 0
 * A[10] = {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; //find 1; position = 1
 * A[10] = {-1, -1, 1, 1, 1, 1, 1, 1, 1, 1}; //find 1; position = 2
 * A[10] = {-1, 1, 1, 1, 1, 1, 1, 1, 1, 3}; //find 3; position = 9
 */
    int A[10] = {-1, -1, 0, 0, 1, 1, 2, 3, 3, 3};

    int position = findFirstOccurrence(A, 10, 5);

    cout << "position: " << position << endl;



    return 0;
}
