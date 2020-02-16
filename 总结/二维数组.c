#include <stdio.h>
#include <stdlib.h>

#define ALLOC_SIZE   1000

int** ReturnTwoDimensionArray(int* returnSize, int** returnColSize)
{
    int i;
    int j;
    int counter = 0;
    int** res = (int**)malloc(ALLOC_SIZE * sizeof(int));
    *returnColSize = (int*)malloc(ALLOC_SIZE * sizeof(int));

    for (i = 0; i < ALLOC_SIZE; i++) {
        #if 1   //����2�ַ����ڴ�Ĳ���ֵ�ķ�������ȷ��
        res[(*returnSize)++] = (int*)malloc((i + 1) * sizeof(int));
        (*returnColSize)[i] = (i + 1);
        #else
        *(res + (*returnSize)) = (int*)malloc((i + 1) * sizeof(int));
        *((*returnColSize) + i) = (i + 1);
        #endif
        for (j = 0; j < (i + 1); j++) {
            *(*(res + (*returnSize)) + j) = counter++;
            printf("%4d", *(*(res + (*returnSize)) + j));
        }
        (*returnSize)++;
        printf("\r\n");
    }
    return res;
}


int main(void)
{
    int i;
    int j;
    int num = 0;
#if 1  
    int returnSize = 0;
    int (*colArra)[ALLOC_SIZE] = NULL; //�ؼ�����������һ��ָ�룬ָ��һ�����飬����ȡ��ַ���룬������ĺ����л�����ڴ�����ָ�롣
    int **result = ReturnTwoDimensionArray(&returnSize, &colArra);
    for (i = 0; i < returnSize; i++) {
        printf("\r\ncol = %4d\r\n", (*colArra)[i]);
        for (j = 0; j < (*colArra)[i]; j++) { //�����ڷ���ʱҪע�� (*colArra)[i]  �� *colArra[i] ������ǰ��ָ��������еĵ�һ��Ԫ�أ�����ָ��ĵ�ַ�� ������ַ + ALLOC * i��
            printf("%4d", *(*(result + i) + j));
        }
        printf("\r\n");
    }
#endif
    system("pause");
}