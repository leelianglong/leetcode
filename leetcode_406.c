#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int cmp(const void* a, const void* b)
{
    return (*(int**)a)[0] - (*(int**)b)[0];
}

int** reconstructQueue(int** people, int peopleSize, 
    int* peopleColSize, int* returnSize, int** returnColumnSizes){
    if (people == NULL || peopleSize <= 0 || peopleColSize == NULL
        || returnSize == NULL || returnColumnSizes == NULL) {
            return NULL;
        }
    int** res = (int**)malloc(sizeof(int*)* peopleSize);
    int i;
    for (i = 0; i < peopleSize; i++) {
        res[i] = (int*)malloc(sizeof(int) * peopleColSize[i]);
        memset(res[i], -1, sizeof(int) * peopleColSize[i]);
    }    

    qsort(people, peopleSize, sizeof(int*), cmp);
    for (i = 0; i < peopleSize; i++) {
        int index = people[i][1] + 1;
        for (int j = 0; j < peopleSize; j++) {
            if (res[j][0] == -1 || 
                res[j][0] == people[i][0] && (--index == 0)) {
                    res[j][0] = people[i][0];
                    res[j][1] = people[i][1];
                    break;
            }
        }
    }
    *returnSize = peopleSize;
    *returnColumnSizes = peopleColSize;
    return res;
}

int main(void)
{
    int testData[6][2] = {
        {7,0},
        {4,4},
        {7,1},
        {5,0},
        {6,1},
        {5,2},
    };
    int** input = (int**)malloc(sizeof(int*) * 6);
    int i;
    int j;
    for (i = 0; i < 6; i++) {
        input[i] = (int*)malloc(sizeof(int) * sizeof(testData[0]));
    }
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 2; j++) {
            input[i][j] = testData[i][j];
        }
    }
    int peopleSize = sizeof(testData) / sizeof(testData[0]);
    int peopleColSize[6] = {2, 2, 2, 2, 2, 2};
    int returnSize = 0;
    int* returnColumnSize[6] = {NULL};
    int** result = reconstructQueue(input, peopleSize, peopleColSize,
        &returnSize, returnColumnSize);
    for (i = 0; i < returnSize; i++) {
        for (j = 0; j < 2; j++) {
            printf("%2d", result[i][j]);
        }
        printf("\r\n");
    }
    system("pause");
}