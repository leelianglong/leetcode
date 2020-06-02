#include <stdio.h>
#include <stdlib.h>


int threeMax(int a, int b, int c)
{
    if (a > b) {
        return a > c ? a : c;
    }
    return b > c ? b : c;
}

int maxSubArray(int* nums, int numsSize){
    int i,j,k;
    int sumLeft = 0;
    int sumRight = 0;
    int sumMiddleLeft = 0;
    int sumMiddleRight = 0;
    int maxLeft = 0;
    int maxRight = 0;
    int middle;
    int finalSum = 0;

    if (nums == NULL || numsSize <= 0) {
        return 0;
    }
    if (numsSize == 1) {
        return nums[0];
    }
    middle = numsSize / 2;
    sumLeft = maxSubArray(nums, middle);
    sumRight = maxSubArray(&nums[middle], numsSize - middle);

    /*
    注意，分治法左半部分要使用减法做循环。目的是要包含左半部分最后一个元素
    与右半部分第一个元素 再加上分界线上的元素，做成第三种。
    然后从左最大 、 右最大、第三种，这三者之间选取最大的。
    */
    //for (i = 0; i < middle; i++) {
    for (i = middle - 1; i >= 0; i--){ 
        sumMiddleLeft += nums[i];
        if (maxLeft < sumMiddleLeft) {
            maxLeft = sumMiddleLeft;
        }
    }

    for (j = middle + 1; j < numsSize; j++) {
        sumMiddleRight += nums[j];
        if (maxRight < sumMiddleRight) {
            maxRight = sumMiddleRight;
        }
    }

    finalSum = threeMax(sumLeft, sumRight, maxLeft + maxRight + nums[middle]);
    return finalSum;
}


int array[] = {-2, -1, -3 ,4, -1, 2, 1, -5,4};

int main(viod)
{
    int sum = maxSubArray(array, 9);
    printf("%4d", sum);
}