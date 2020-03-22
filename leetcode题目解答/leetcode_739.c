
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*
 * 这是最容易想到的方法，但是会超时，分析超时的原因，可知，好多重复的元素被重复比较了，需要一种不重复比较元素的方法
 *
 * */
int* dailyTemperature1(int* T, int TSize, int* returnSize)
{
    if (T == NULL || TSize <= 0) {
        return NULL;
    }
    *returnSize = TSize;
    int* res = (int*)malloc(TSize * sizeof(int));
    if (res == NULL) {
        return NULL;
    }
    int i;
    int j;
    int tmp;
    int returnCount = 0;
    for (i = 0; i < TSize; i++) {
        tmp = T[i];
        for (j = i + 1; j < TSize; j++) {
            if (tmp < T[j]) {
                res[returnCount++] = (j - i);
                break;
            }
        }
        if (j == TSize) {
            res[returnCount++] = 0;
        }
    }
    return res;
}


/*
 * 从后往前扫描，就能避免大量重复的比较，就能避免超时。
 */
int* dailyTemperature(int* T, int TSize, int* returnSize)
{
    if (T == NULL || TSize <= 0) {
        return NULL;
    }
    *returnSize = TSize;
    int* res = (int*)malloc(TSize * sizeof(int));
    if (res == NULL) {
        return NULL;
    }
    memset(res, 0, TSize * sizeof(int));
    int i;
    int j;
    int tmp;

    for (i = TSize - 2; i >= 0; i--) {
        tmp = T[i];
        for (j = i + 1; j < TSize; j += res[j]) {
            if (tmp < T[j]) {
                res[i] = (j - i);
                break;
            } else if (res[j] == 0) {
                res[i] = 0;
                break;
            }
        }
    }
    return res;
}


int main() {
    int test [] = {73,74,75,71,69,72,76,73};
    int size = 0;

    int* result = dailyTemperature(test, sizeof(test) / sizeof(test[0]), &size);
    for (int i = 0; i < size; ++i) {
        printf("%4d", *(result + i));
    }
    return 0;
}
