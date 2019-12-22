#include <stdio.h>
#include <stdlib.h>

int CheckEvenNumber(unsigned int data)
{
	if (data / 10000 != 0) {
		return 0;
	} else if (data / 10000 == 0 && data / 1000 != 0) {
		return 1;
	} else if (data / 1000 == 0 && data / 100 != 0) {
		return 0;
	} else if (data / 100 == 0 && data / 10 != 0) {
		return 1;
	} else {
		return 0;
	}
}


int findNumbers(int* nums, int numsSize){
	int i;
	int count = 0;
	if (nums == NULL || numsSize <= 0) {
		return 0;
	}
	
	for (i = 0; i < numsSize; i++) {
		if (CheckEvenNumber(nums[i])) {
			count++;
		}
	}
	return count;
}




int main(void)
{
	int nums[] = {12,345,2,6,7896};
	int count = findNumbers(nums, sizeof(nums) / sizeof(nums[0]));
	printf("the result is %d", count);
}
