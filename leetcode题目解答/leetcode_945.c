#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT(a, b) ((a) > (b) ? (a) : (b))

int minIncrementForUnique(int* A, int ASize){
    if (A == NULL) {
        return 0;
    }
    int i;
    int max = -1;
    int hash[40001] = {0};
    for (i = 0; i < ASize; i++) {
        hash[A[i]]++;
        max = MAX_ELEMENT(A[i], max);
    }
    int counter = 0;
    int j = 0;
    for (i = 0; i <= max; i++) {
        if (hash[i] > 1) {
            int step = hash[i] - 1; // 当前这个值重复了多少次。
            counter += step;
            hash[i + 1] += step;// 把这个重复的数据移到下一个位置上。
        }
    }
    // 当靠近最大值附近有多个重复的数据时，根据上面的算法，在hash[max+1]这里会有堆积。
    // 下面的操作就是把这些堆积展开所需要的步数。
    int calcu = hash[max + 1] - 1;
    counter += ((calcu + 1 ) * calcu / 2);
    return counter;
}


int main(void)
{
    int test[] = {3,2,6,6,6,7};
    int result = minIncrementForUnique(test, sizeof(test) / sizeof(test[0]));
    printf("\r\nres = %d\r\n", result);
    system("pause");
}
