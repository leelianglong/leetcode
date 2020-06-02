#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* beautifulArray(int N, int* returnSize){
    if (returnSize == NULL) {
        return NULL;
    }
    if (N < 1) {
        *returnSize = 0; // ������ﲻ���ó�0���ᵼ�¿�ָ����ʡ�
        return NULL;
    }
    int* tmp = (int*)malloc(sizeof(int) * 2000);
    memset(tmp, 0, sizeof(int) * 2000);
    int* res = (int*)malloc(sizeof(int) * N);
    memset(res, 0, sizeof(int) * N);
    tmp[0] = 2;
    tmp[1] = 1;
    tmp[2] = 4;
    tmp[3] = 3; // �����N=4�ĳ�ʼ Ư�����顣
    int i;
    int j;
    for (i = 1; i < 150; i *= 2) {
        for (j = 0; j < 4 * i; j++) {
            tmp[4*i + j] = tmp[j] * 2; // ��ʼ��Ư�����飬����2����Ȼ��Ư�����飬����ͱ��ż���ˡ�
            tmp[j] = tmp[j] * 2 - 1; // Ư�������һ������Ư�����飬������������
        }  // ����2���Ⱥţ��൱�ڰ�������ż��Ư�����鶼����һ��������յ�Ư������
    }

    int k = 0;
    for (i = 0; i < 2000; i++) {
        if (k < N && tmp[i] != 0 && tmp[i] <= N) { // ��Ư��������ɾ��һЩֵ������Ȼ��Ư�����顣���˵��Ƿ�ֵ��
            res[k++] = tmp[i];
        }
    }
    *returnSize = N;
    return res;
}

#define DESC(X)           1
#if DESC(���η����)
/* ��������ͳ�ķ��η�*/
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