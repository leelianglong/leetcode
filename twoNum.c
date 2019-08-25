#include<stdio.h>
#include<stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
	int* indices = (int*)malloc(2 * sizeof(int));
	int i, j;
	if (nums == NULL || numsSize <= 0 || indices == NULL || returnSize == NULL) {
		return NULL;
	}
	int realNumSize = sizeof(*nums) / sizeof(int) > numsSize ? sizeof(*nums) / sizeof(int) : numsSize;
	for (i = 0; i < realNumSize; i++) {
		for (j = i + 1; j < realNumSize; j++) {
			if ((nums[i] + nums[j]) == target) {
				indices[0] = i;
				indices[1] = j;
				*returnSize = 2;
				return indices;
			}
		}
	}
	return NULL;
}

int main(void)
{
	int a1[10] = { 0,-1,2,3,4,5,6,7,8,9 };
	int* result = NULL;
	int resultNum = 0;
	result = twoSum(a1, 10, 1, &resultNum);
	printf("result: %d, %d", *result, *(result + 1));
}