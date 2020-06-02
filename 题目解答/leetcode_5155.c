#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

/*
思路： 
1、对原数据进行排序
2、对排序后的数组进行去重
3、再一开始把原数据拷贝一份，然后再第二步完成之后，使用原始的数据，在排序去重的数组中查找位置
并把位置信息返回即可。
*/
int* arrayRankTransform(int* arr, int arrSize, int* returnSize){
    if (arr == NULL || returnSize == NULL) {
        return NULL;
    }
    int k;
    int* oldData = (int*)malloc(arrSize * sizeof(int));
    memset(oldData, 0, arrSize * sizeof(int));
    memcpy(oldData, arr, arrSize * sizeof(int));
    printf("olddata:");
    for (k = 0; k < arrSize; k++) {
        printf("%4d", oldData[k]);
    }
    printf("\n");
    qsort(arr, arrSize, sizeof(int), cmp);
    printf("sortdata:");
    for (k = 0; k < arrSize; k++) {
        printf("%4d", arr[k]);
    }
    printf("\n");
    int* saveTmp = (int*)malloc(sizeof(int) * (arrSize + 1));
    memset(saveTmp, 0, sizeof(int) * (arrSize + 1));

    int* res = (int*)malloc(sizeof(int) * (arrSize + 1));
    memset(res, 0, sizeof(int) * (arrSize + 1));
    int i;
    int j;
    int counter = 0;
    int saveCounter = 0;
    for (i = 1; i < arrSize; i++) {
        if (arr[i] != arr[i - 1]) {
            saveTmp[saveCounter++] = arr[i - 1];
            if (i == arrSize - 1) {
                saveTmp[saveCounter++] = arr[i];
            }
        } else if (arr[i] == arr[i - 1] && i == arrSize - 1) {
            saveTmp[saveCounter++] = arr[arrSize - 1];
        }
    }
    if (i == arrSize && saveTmp[0] == 0) {
        for (i = 0; i < arrSize; i++) {
            res[i] = 1;
        }
        *returnSize = arrSize;
        return res;
    }
    printf("\nsave data:");
    for (i = 0; i < saveCounter; i++) {
        printf("%4d", saveTmp[i]);
    }
    printf("\n");
    counter = 0;
    for (i = 0; i < arrSize; i++) {
        for (j = 0; j < saveCounter; j++) {
            if (oldData[i] == saveTmp[j]) {
                res[counter++] = j + 1;
                break;
            }
        }
    }
    printf("\n counter=%u", counter);
    *returnSize = counter;
    return res;
}

int main(void)
{
    int test[] = {4,23,-6,-15,-24,-17,6,-47,20,39,-26,9,-44,39,-50};
    int returnSize = 0;
    int* res = arrayRankTransform(test, sizeof(test) / sizeof(test[0]), &returnSize);
    printf("\n");
    for (int i = 0; i < returnSize; i++) {
       printf("%4d", res[i]);
    }
    system("pause");
}