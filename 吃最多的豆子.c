#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b)  a > b ? a : b

int CalculateEatMaxBean(void)
{
    int i;
    int j;
    int row = 0;
    int colum = 0;
    int array[24][24] = {0};
    int dp[24][24] = {0}; /* 用于存储每一步的最大值 */

	printf("\r\nint put row and colum\r\n");
    scanf("%d,%d",&row, &colum);
    for (i = 0; i < row; i++) {
        for (j = 0; j < colum; j++) {
            scanf("%d",&array[i][j]);
        }
    }

    dp[row - 1][0] = array[row - 1][0];
    /* 先计算2个边上的和 */
    for (i = row - 1 - 1; i >= 1; i--) {
        dp[i][0] = dp[i-1][0] + array[i][0];
    }

    for (j = 1; j < colum; j++) {
        dp[row - 1][j] = dp[row - 1][j - 1] - array[row - 1][j];
    }

    for (i = row - 1 - 1; i >= 0; i--) {
        for (j = 1; j < colum; j++) {
            dp[i][j] = MAX(dp[i - 1][j], dp[i][j - 1]) + array[i][j];
        }
    }
    return dp[row][colum];
}


int main(void)
{
    int sum = CalculateEatMaxBean();
    printf("sum=%d", sum);
}