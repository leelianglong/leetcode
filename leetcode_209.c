#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ELEMENT(a, b) (a > b ? b : a)
int minSubArrayLen(int s, int* nums, int numsSize){
    if (nums == NULL || numsSize <= 0) {
        return 0;
    }
    int left = 0;
    int right = 0;
    int curSum = 0;
    int minLen = INT_MAX;

    for (right = 0; right < numsSize; right++) {
        curSum += nums[right];
        while (curSum >= s) {
            minLen = MIN_ELEMENT(minLen, right - left + 1);
            curSum -= nums[left++];
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}



int main(void)
{
    int test[] = {2,3,1,2,4,3};
    int s = 7;
    int result = minSubArrayLen(s, test, sizeof(test) / sizeof(test[0]));
    printf("\r\nresult=%d\r\n", result);
    return 0;
}