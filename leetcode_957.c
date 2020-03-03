#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
    Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
    Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
    Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
    Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
    Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
    Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
    Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
 */

int JudgeSame(int* a, int* b)
{
    for (int i = 0; i < 8; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

void Print(int times, int* cells)
{
    printf("\r\nday %d: ", times);
    for (int i = 0; i < 8; i++) {
        printf("%2d", cells[i]);
    }
    printf("\r\n");
}

int* prisonAfterNDays(int* cells, int cellsSize, int N, int* returnSize){
    if (cells == NULL || cellsSize <= 0 || N < 0
        || returnSize == NULL) {
        return NULL;
    }
    int i;
    int j;
    int tmp[8] = {0};
    int firstOne[8] = {0};
    for (i = 1; i <= N; i++) {
        for (j = 1; j < cellsSize - 1; j++) {
            tmp[j] = cells[j - 1] == cells[j + 1] ? 1 : 0;
        }
        for (j = 0; j < cellsSize; j++) {
            cells[j] = tmp[j];
        }

        if (i == 1) {
            memcpy(firstOne, cells, sizeof(int) * 8); // 记录第一天的状态
        }
        if (i > 1 && JudgeSame(firstOne, cells)) {
            printf("\r\nfind the same %d\r\n", i);
            break;
        }
        Print(i, cells);
    }
    int day = N % (i - 1);
    for (i = 0; i < day; i++) {
        for (j = 1; j < cellsSize - 1; j++) {
            tmp[j] = cells[j - 1] == cells[j + 1] ? 1 : 0;
        }
        for (j = 1; j < cellsSize; j++) {
            cells[j] = tmp[j];
        }
    }

    *returnSize = cellsSize;
    return cells;
}

/*
 * [1,0,0,1,0,0,1,0]
    1000000000
    预期输出：[0,0,1,1,1,1,1,0]
 * */
int main() {
    int test[] = {1,0,0,1,0,0,1,0};
    int size = 0;
    int i;
    int* result = prisonAfterNDays(test, sizeof(test) / sizeof(test[0]), 17, &size);
    for (i = 0; i < size; i++) {
        printf("%2d", result[i]);
    }
    return 0;
}
