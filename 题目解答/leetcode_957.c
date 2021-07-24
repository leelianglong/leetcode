#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool JudgeSame(int* a, int* b)
{
    for (int i = 0; i < 8; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

void Print(int times, int* cells)
{
    printf("\r\nday %d:", times);
    for (int i = 0; i < 8; i++) {
        printf("%2d", cells[i]);
    }
    printf("\r\n");
}
int* prisonAfterNDays(int* cells, int cellsSize, int N, 
    int* returnSize){
    if (cells == NULL || cellsSize <= 0 || N < 0 || returnSize == NULL) {
        return NULL;
    }
    if (N == 0) {
        *returnSize = cellsSize; 
        return cells;
    }
    int i;
    int j;
    int tmp[8] = {0};
    int firstOne[8] = {0};
    int lastOne[8] = {0};
    bool stop = false;
    for (i = 1; i <= N; i++) {
        for (j = 1; j < cellsSize - 1; j++) {
            tmp[j] = cells[j - 1] == cells[j + 1] ? 1 : 0;
        }
        for (j = 0; j < cellsSize; j++) {
            cells[j] = tmp[j];
        }

        if (i == 1) {
            memcpy(firstOne, cells, sizeof(int) * 8); 
        }
        Print(i, cells);
        if (i > 1 && JudgeSame(firstOne, cells)) {
            printf("\r\nfind the same\r\n");
            stop = true;
            break;
        }
        memcpy(lastOne, cellsSize, sizeof(int) * cellsSize);
    }

    if (stop == false) {
        *returnSize = cellsSize;
        return cells;                
    }

    int day = N % (i - 1);
    printf("\r\n day=%d N=%d i=%d\r\n", day, N, i);
    if (day == 0) {
        memcpy(cells, lastOne, sizeof(int) * cellsSize);
        *returnSize = cellsSize;
        return cells;
    }
    if (day == 1) {
        *returnSize = cellsSize;
        memcpy(cells, firstOne, sizeof(int) * cellsSize);
        return cells;
    }
    for (i = 1; i < day; i++) {
        for (j = 1; j < cellsSize - 1; j++) {
            tmp[j] = cells[j - 1] == cells[j + 1] ? 1 : 0;
        }
        for (j = 0; j < cellsSize; j++) {
            cells[j] = tmp[j];
        }
    }
    *returnSize = cellsSize;
    return cells;
}

int main(void)
{
    int test[] = {0,0,0,1,1,0,1,0};
    int returnSize = 0;
    int* result = prisonAfterNDays(test, sizeof(test) / sizeof(test[0]),
        574, &returnSize);
    for (int i = 0; i < 8; i++) {
        printf("%2d", result[i]);
    }
    printf("\r\n");
    system("pause");
}