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
        #if 1   //这里2种分配内存的并赋值的方法都正确。
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
    int (*colArra)[ALLOC_SIZE] = NULL; //关键是这里，定义成一个指针，指向一个数组，这里取地址传入，在下面的函数中会分配内存给这个指针。
    int **result = ReturnTwoDimensionArray(&returnSize, &colArra);
    for (i = 0; i < returnSize; i++) {
        printf("\r\ncol = %4d\r\n", (*colArra)[i]);
        for (j = 0; j < (*colArra)[i]; j++) { //这里在访问时要注意 (*colArra)[i]  和 *colArra[i] 的区别，前者指向该数组中的第一个元素，后者指向的地址是 （基地址 + ALLOC * i）
            printf("%4d", *(*(result + i) + j));
        }
        printf("\r\n");
    }
#endif
    system("pause");
}