#include <stdio.h>
#include <stdlib.h>


/*
给你一个整数数组nums和一个正整数k，请你判断是否可以把这个数组划分成一些由k个连续数字组成的集合。如果可以，请返回True；否则，返回False。

输入：nums = [1,2,3,3,4,4,5,6], k = 4
输出：true
解释：数组可以分成 [1,2,3,4] 和 [3,4,5,6]。

输入：nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
输出：true
解释：数组可以分成 [1,2,3] , [2,3,4] , [3,4,5] 和 [9,10,11]。

输入：nums = [3,3,2,2,1,1], k = 3
输出：true

输入：nums = [1,2,3,4], k = 3
输出：false
解释：数组不能分成几个大小为 3 的子数组
*/

/*
	思路: 使用hash；
    1、 先排序
    2、 使用一个hashmap 存储给定序列中数值出现的次数。这个haspmap的大小要注意。
    3、 按照排好序的数列，逐个拿出来，在hashmap中，从当前这个值开始的K个 haspmap值是不是0，如果有0则表示整个数列中没有从这个值
        的K个连续数列；
*/
int com(const void* a, const void* b)
{
	return *(int*)(a) - *(int*)(b);
}

int isPossibleDivide(int* nums, int numsSize, int k){
	int i;
	int v;
	int j;
	int* map = NULL;
	unsigned int size;
	if (nums == NULL || numsSize <= 0 || k <= 0) {
		return 0;
	}
	if (numsSize % k != 0) {
		return 0;
	}
	
	qsort(nums, numsSize, sizeof(int), com);
	size = (nums[numsSize - 1] + 1) > numsSize ? (nums[numsSize - 1] + 1) : numsSize; 
	map = (int*)malloc(size * sizeof(int));
	memset(map, 0, size * sizeof(int));

	for (i = 0; i < numsSize; i++) {
		map[nums[i]]++;
	}
	
	for (i = 0; i < numsSize; i++) {
		v = nums[i];
		if (map[v] == 0) { 
			continue;
		}
		for (j = 0; j < k; j++) {
			if (map[v + j] == 0) {
				return 0; /* 从 nums[i]开始的k个，只要有1个为0，则不满足要求 */
			}
			map[v + j]--; /* 这里计算主要为上面map[v] == 0  */
		}
	}
	return 1;
}


int main(void)
{
	int nums[] = {12,12,2,11,22,20,11,13,3,21,1,13};
	int result = isPossibleDivide(nums, sizeof(nums) / sizeof(nums[0]), 3);
	printf("\r\nthe result is %d", result);
}
