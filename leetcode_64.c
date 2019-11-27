#include <stdio.h>
#include <stdlib.h>


#define MIN_NUM(a, b)    (a >= b ? b : a) // 宏要使用完备的括号

/*
    使用动态规划，动态数组中存储的数字就是表示从该点到右下角的最短距离，我们从右下角开始计算。
    先计算最后一行，各个点到右下角最短值
    再计算最后一列，各个点到右下角最短值
    然后再计算中间某个点到右下角的值，计算的公式就是它本身 + 它右边或下边的较小值
    最后会把第0行第0列的值计算出来，这个值就是我们要的值。
*/
int minPathSum(int** grid, int gridSize, int* gridColSize){
    if (grid == NULL || gridColSize == NULL || gridSize < 1) {
        return -1;
    }
    int** tmp = (int** )malloc(gridSize * sizeof(int*));
    if (tmp == NULL) {
        return -1;
    }
    int i;
    int c = *gridColSize;
    for (i = 0; i < gridSize; i++) {
        *(tmp + i) = (int*)malloc(c * sizeof(int));       
        if (*(tmp + i) == NULL) {
            free(tmp);
            return -1;
        }    
    }

    int j;
    int r = gridSize - 1;
    for (j = 0; j < gridSize; j++) {
        for (i = 0; i < *gridColSize; i++) {
            *(*(tmp + j) + i) = 0;
        }
    }

    c -= 1;
    *(*(tmp + r) + c) = *(*(grid + r) + c);
    //填充最后一行
    for (i = c - 1; i >= 0; i--) {
        *(*(tmp + r) + i) = *(*(grid + r) + i) + *(*(tmp + r) + i + 1);
    }
    // 填充最后一列
    for (j = r - 1; j >= 0 ; j--) {
        *(*(tmp + j) + c) = *(*(grid + j) + c) + *(*(tmp + j + 1) + c);
    }
    for (j = r - 1; j >= 0 ; j--) {
        for (i = c - 1; i >= 0 ; i--) {
            *(*(tmp + j) + i) = MIN_NUM(*(*(tmp + j + 1) + i), *(*(tmp + j) + i + 1)) + *(*(grid + j) + i);
        }
    }
    return *(*(tmp + 0) + 0);
}

int main(void)
{
    int test[2][3] = {
        {1,2,5},
        {3,2,1},
    };
    int* a[2] = {NULL};
    a[0] = test[0];
    a[1] = test[1];
    //a[2] = test[2];
    int gridSize = 2;
    int gridColoSize = 3;
    int sum = minPathSum(a, gridSize, &gridColoSize);
    printf("result = %d", sum);
    system("pause");
}