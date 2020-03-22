#include <stdio.h>
#include <stdlib.h>


double findMaxAverage1(int* nums, int numsSize, int k){
    int i = 0;
    int left = 0;
    double sum = 0.0;
    double maxAvg = 0.0;
    double tmpAvg = 0.0;

    if (nums == NULL || numsSize <= 0 || k <= 0) {
        return 0;
    }
    if (numsSize == k) {
        for (i = 0; i < k; i++) {
            sum += nums[i];
        }
        return sum / k;
    }
    for (left = 0; left <= numsSize - k; left++) {
        sum = 0.0; 
        for (i = left; i < left + k; i++) {
            sum += nums[i];
        }
        tmpAvg = sum / k;
        if (left == 0) {
            maxAvg = tmpAvg;
        } else if (tmpAvg > maxAvg) {
            maxAvg = tmpAvg;
        }
    }
    return maxAvg;
}

/*
* 思路：设置一个长度为K的窗口，计算其中的平均值，然后让滑动窗口移动，逐个比较和当前窗口值的大小，如果大与当前窗口值
*       则更新窗口值，反之不更新。
*/
double findMaxAverage(int* nums, int numsSize, int k){
    int i = 0;
    double maxAvg = 0.0;
    double curWindow = 0.0;
    if (nums == NULL || numsSize <= 0 || k <= 0) {
        return 0;
    }
    for (i = 0; i < k; i++) {
        curWindow += nums[i];
    }
    maxAvg = curWindow;
    for (i = 0; i < numsSize - k; i++) {
        curWindow -= nums[i];
        curWindow += nums[i + k]; //窗口移动
        if (curWindow > maxAvg) {
            maxAvg = curWindow;
        }
    }
    return maxAvg / k;
}

int main(void) 
{
    int tmp[1] = {-1};
    double result = findMaxAverage(tmp, 1, 1);
    printf("\r\nresult = %lf\r\n", result);
    system("pause");
}