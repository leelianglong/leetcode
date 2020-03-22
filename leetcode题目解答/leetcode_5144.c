#include <stdio.h>
#include <stdlib.h>

/*
* 题目已经告诉矩阵最大行列是100.
*/
#define ALLOC_SIZE  3
#define MAX_SIZE    101
#define ROW_M       101
#define COW_N       101

int** matrixBlockSum(int** mat, int matSize, int* matColSize, int K, int* returnSize, 
    int** returnColumnSizes){
    if (mat == NULL || matSize <= 0 || matColSize == NULL || returnSize == NULL 
        || returnColumnSizes == NULL) {
            return NULL;
        }
    int i;
    int j;
    int m;
    int p;
    int q;
    int rMin = 0;
    int rMax = 0;
    int cMin = 0;
    int cMax = 0;
    *returnColumnSizes = (int*)malloc(MAX_SIZE * sizeof(int));
    int **res = (int**)malloc(ROW_M * sizeof(int*));
    for (m = 0; m < matSize; m++) {
        res[m] = (int*)malloc(COW_N * sizeof(int));
        memset(res[m], 0, COW_N * sizeof(int));
    }

    for (i = 0; i < matSize; i++) {
        (*returnColumnSizes)[i] = *matColSize;
        for (j = 0; j < *matColSize; j++) {
            rMin = (i - K) >= 0 ? (i - K) : 0;
            rMax = (i + K) >= matSize ? (matSize - 1) : (i + K);
            cMin = (j - K) >= 0 ? (j - K) : 0;
            cMax = (j + K) >= *matColSize ? (*matColSize - 1) : (j + K);
            for (p = rMin; p <= rMax; p++) {
                for (q = cMin; q <= cMax; q++) {
                    *(*(res + i) + j) +=  *(*(mat + p) + q);
                }
            }
        }
        *(matColSize++);
    }
    *returnSize = matSize;
    return res;
}

int** ReturnTwoDimensionArray(int* returnSize, int** returnColSize)
{
    int i;
    int j;
    int counter = 1;
    int** res = (int**)malloc(ALLOC_SIZE * sizeof(int*));
    *returnColSize = (int*)malloc(ALLOC_SIZE * sizeof(int));

    for (i = 0; i < ALLOC_SIZE; i++) {
        res[i] = (int*)malloc(ALLOC_SIZE * sizeof(int));
        (*returnColSize)[i] = ALLOC_SIZE;
        (*returnSize)++;
        for (j = 0; j < ALLOC_SIZE; j++) {
            *(*(res + i) + j) = counter++;
        }
    }
    return res;
}

int main(void)
{
    int (*returnColSize)[ALLOC_SIZE] = NULL;
    int (*returnColSizeNew)[MAX_SIZE] = NULL;
    int returnSize = 0;
    int returnSizeNew = 0;
    int **res = ReturnTwoDimensionArray(&returnSize, &returnColSize);
    int i;
    int j;

    for (i = 0; i < returnSize; i++) {
        for (j = 0; j < (*returnColSize)[i]; j++) {
            printf("%4d", *(*(res + i) + j));
        }
        printf("\n");
    }
    int** resMatrix = matrixBlockSum(res, returnSize, returnColSize, 1, 
        &returnSizeNew, &returnColSizeNew);
    for (i = 0; i < returnSizeNew; i++) {
        for (j = 0; j < (*returnColSizeNew)[i]; j++) {
            printf("%4d", *(*(resMatrix + i) + j));
        }
        printf("\n");
    }
    system("pause");
}