#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
* 算法思路：
* 要求序列 {a1,a2,a3,.....ai}的最长递增子序列。我们可以将把问题转换成先求出{a1,a2,a3,....a(i-1)}序列的最长递增子序列。
* 具体做法是：求出以：a1,a2,a3,...a(i-1)为结尾的所有最长递增序列，总共有i - 1 个
* 将这个i-1个序列中的元素 与 ai 进行比较
* 如果存在 某个序列m 的最大元素 aj < ai, 并且 j < i, 那么就可以把ai 放到当前序列的末尾，是最大递增序列个数 + 1
* 我们使用数组DP，其中DP[i] 表示以原来序列第i个元素结尾的最长递增序列的长度
*/
#define MAX(a, b)  (a > b ? a : b)

int* BuildDpArray(int* data, int size)
{
    int* dp = (int*)malloc(size * sizeof(int));
    int i;
    int j;

    memset(dp, 0, size);
    for (i = 0; i < size; i++) {
        dp[i] = 1; // 动态规划的初始值，每个数据至少以它开始都有一个递增序列就是它自己。
        for (j = 0; j < i; j++) {  
            if (data[j] < data[i]) {
                dp[i] = MAX(dp[i], dp[j] + 1); // 在i前面存在比data[i] 小的元素 data[j]，那么就可以把它放到当前当前序列，并把最长递增序列长度加1.
            }
        }
    }
    return dp;
}

int* GenerateLongestIncreaseSubsequenen(int* data, int dataSize, int* dp, int dpSize, int* backSize)
{
    int dpMax = 0;
    int i;
    int index = 0;
    int* list;
// 获取以各个数字为结束的最长递增序列长度的数组中，最长的递增序列长度为dpMax, 其对应的下标是 index。
    for (i = 0; i < dpSize; i++) {
        if (dp[i] > dpMax) {
            dpMax = dp[i];
            index = i; //这里表示原数组中以第index数据结尾的递增子序列是最长的。它的最大长度是dpMax.
        }
    }
// 准备把最长递增序列放到数组list中输出。
    *backSize = dpMax;
    list = (int*)malloc(dpMax * sizeof(int));
    memset(list, 0, dpMax);
    dpMax -= 1;
    list[dpMax] = data[index];//原数组中以第index的数据元素结尾子序列是最长的递增序列，这里把该元素拿处理放到输出序列的最后一个位置上。
    for (i = index; i >= 0; i--) {//然后从这个元素的位置开始，逐步遍历到第1个元素，找到合适的元素填到输出队列list中
        if (data[i] <= data[index] && dp[i] == dp[index] - 1) {
            dpMax -= 1;
            list[dpMax] = data[i];
            index = i;
        }
    }
    return list;
}

int main(void)
{
    int data[9] = {3,1,4,5,9,2,6,0};
    int* dp = BuildDpArray(data, 9);
    int i;
    int* subSequence;
    int subSequenceSize = 0;

    for (i = 0; i < 9; i++) {
        printf("%4d", dp[i]);
    }
    subSequence = GenerateLongestIncreaseSubsequenen(data, 9, dp, 9, &subSequenceSize);
    printf("\r\nsubsequence:");
    for (i = 0; i < subSequenceSize; i++) {
        printf("%4d", subSequence[i]);
    }
    system("pause");
}