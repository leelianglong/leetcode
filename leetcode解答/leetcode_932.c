#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* beautifulArray(int N, int* returnSize){
    if (returnSize == NULL) {
        return NULL;
    }
    if (N < 1) {
        *returnSize = 0; // 如果这里不设置成0，会导致空指针访问。
        return NULL;
    }
    int* tmp = (int*)malloc(sizeof(int) * 2000);
    memset(tmp, 0, sizeof(int) * 2000);
    int* res = (int*)malloc(sizeof(int) * N);
    memset(res, 0, sizeof(int) * N);
    tmp[0] = 2;
    tmp[1] = 1;
    tmp[2] = 4;
    tmp[3] = 3; // 这个是N=4的初始 漂亮数组。
    int i;
    int j;
    for (i = 1; i < 150; i *= 2) {
        for (j = 0; j < 4 * i; j++) {
            tmp[4*i + j] = tmp[j] * 2; // 初始是漂亮数组，乘以2后依然是漂亮数组，这里就变成偶数了。
            tmp[j] = tmp[j] * 2 - 1; // 漂亮数组减一个还是漂亮数组，这里是奇数。
        }  // 这里2个等号，相当于把奇数和偶数漂亮数组都放在一起，组成最终的漂亮数组
    }

    int k = 0;
    for (i = 0; i < 2000; i++) {
        if (k < N && tmp[i] != 0 && tmp[i] <= N) { // 从漂亮数组中删除一些值，它依然是漂亮数组。过滤到非法值。
            res[k++] = tmp[i];
        }
    }
    *returnSize = N;
    return res;
}

#define DESC(X)           1
#if DESC(分治法解答)
/* 下面是正统的分治法*/
int* GetBeautifulArray(int num, int* size)
{
    int* outArray = NULL;
    int* leftArray = NULL;
    int* rightArray = NULL;
    int leftSize = 0;
    int rightSize = 0;
    int i;

    if (num == 1) {
        outArray = (int *)malloc(sizeof(int));
        outArray[0] = 1;
        *size = 1;
        return outArray;
    }

    leftArray = GetBeautifulArray((num + 1) / 2, &leftSize);
    rightArray = GetBeautifulArray(num / 2, &rightSize);
    *size = leftSize + rightSize;
    outArray = (int *)malloc(sizeof(int) * (*size));
    for (i = 0; i < leftSize; i++) {
        outArray[i] = leftArray[i] * 2 - 1;
    }
    for (i = 0; i < rightSize; i++) {
        outArray[i + leftSize] = rightArray[i] * 2;
    }
    free(leftArray);
    free(rightArray);
    return outArray;
}

int* beautifulArray1(int N, int* returnSize)
{
    return GetBeautifulArray(N, returnSize);
}
#endif
int main(void)
{
    int returnSize = 0;
    int* result = beautifulArray(8, &returnSize);
    int i;
    for (i = 0; i < returnSize; i++) {
        printf("%2d", result[i]);
    }
    system("pause");
}