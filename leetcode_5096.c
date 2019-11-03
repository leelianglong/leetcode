#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
* ������ı��������ʹ������һ������ret���洢ÿ�θ��ݹ���Դ����arr�仯������ݡ�
* ������һ��󣬽�ret�е�����ȫ��������arr�У�
* �˳��������ǣ�ret�е����ݺ�arr�е�������ȫһ����
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