#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
* 该问题的暴力解决，使用另外一个数组ret来存储每次根据规则源数组arr变化后的数据。
* 当遍历一遍后，将ret中的数据全部拷贝到arr中；
* 退出的条件是：ret中的数据和arr中的数据完全一样。
*/
int* transformArray(int* arr, int arrSize, int* returnSize){
    if (arr == NULL || returnSize == NULL || arrSize <= 0) {
        return NULL;
    }
    int i;
    int* ret = (int*)malloc(sizeof(int) * arrSize);
    if (ret == NULL) {
        return ret;
    }
    memset(ret, 0, sizeof(int) * arrSize);
    ret[0] = arr[0];
    ret[arrSize - 1] = arr[arrSize - 1];
    while (true) {
        for (i = 1; i < arrSize - 1; i++) {
            if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
                ret[i] = arr[i] - 1;
            } else if (arr[i] < arr[i - 1] && arr[i] < arr[i + 1]) {
                ret[i] = arr[i] + 1;
            } else {
                ret[i] = arr[i];
            }
        }
        for (i = 0; i < arrSize; i++) {
            if (ret[i] != arr[i]) {
                memcpy(arr, ret, sizeof(int) * arrSize);
                break;
            }
        }
        if (i == arrSize) {
            *returnSize = arrSize;
            return ret;
        }
    }
    return NULL;
}


int main(void)
{
    int arr[] = {1,6,3,4,3,5};
    int returnSize = 0;
    int i;
    int* result = transformArray(arr, 6, &returnSize);
    printf("\r\n   result    \r\n");
    for (i = 0; i < returnSize; i++) {
        printf("%4d", result[i]);
    }
    system("pause");
}