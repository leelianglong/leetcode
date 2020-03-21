#include <stdio.h>
#include <stdlib.h>

/*下面是暴力解法，结果是对的，但是时间超时了*/
int majorityElement1(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }
    int commonCounter = numsSize / 2;
    int i;
    int j;
    int* save = malloc(sizeof(int) * numsSize);
    if (save == NULL) {
        return -1;
    }
    memset(save, 0, sizeof(int) * numsSize);
    for (i = 0; i < numsSize; i++) {
        for (j = 0; j < numsSize; j++) {
            if (nums[i] == nums[j]) {
                (*(save+i))++;
            }
        }
    }
    for (j = 0; j < numsSize; j++) {
        if (*(save + j) > commonCounter) {
            return nums[j];
        }
    }
    return -1;
}

/*
* 下面采用分治法，递归求解，最终的子问题是区间只剩下
* 一个元素，那么它就是众数.
*/

int CalculateRepeatTime(int* nums, int data, int low, int high)
{
    int i;
    int counter = 0;
    
    for (i = low; i <= high; i++) {
        if (nums[i] == data) {
            counter++;
        }
    }
    return counter;
}

int CalculateMaxComonElement(int* nums, int low, int high)
{
    if (low == high) {
        return nums[low];
    }

    int mid = (high - low) / 2 + low;
    int leftMax = CalculateMaxComonElement(nums, low, mid);
    int rightMax = CalculateMaxComonElement(nums, mid + 1, high);
    if (leftMax == rightMax) {
        return leftMax;
    }

    int leftRepeatTime = CalculateRepeatTime(nums, leftMax, low, high);
    int rightRepeatTime = CalculateRepeatTime(nums, rightMax, low, high);

    return leftRepeatTime > rightRepeatTime ? leftMax : rightMax;
}

int majorityElement(int* nums, int numsSize)
{
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }
    return CalculateMaxComonElement(nums, 0, numsSize - 1);
}

int main(void)
{
    int arra[] = {2,2,2,1,1,1,2,3};
    int result = majorityElement(arra, sizeof(arra)/sizeof(arra[0]));
    printf("\r\nthe common number is %4d\r\n", result);
    system("pause");
}