#include <stdio.h>
#include <stdlib.h>


/*
����һ����������nums��һ��������k�������ж��Ƿ���԰�������黮�ֳ�һЩ��k������������ɵļ��ϡ�������ԣ��뷵��True�����򣬷���False��

���룺nums = [1,2,3,3,4,4,5,6], k = 4
�����true
���ͣ�������Էֳ� [1,2,3,4] �� [3,4,5,6]��

���룺nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
�����true
���ͣ�������Էֳ� [1,2,3] , [2,3,4] , [3,4,5] �� [9,10,11]��

���룺nums = [3,3,2,2,1,1], k = 3
�����true

���룺nums = [1,2,3,4], k = 3
�����false
���ͣ����鲻�ֳܷɼ�����СΪ 3 ��������
*/

/*
	˼·: ʹ��hash��
    1�� ������
    2�� ʹ��һ��hashmap �洢������������ֵ���ֵĴ��������haspmap�Ĵ�СҪע�⡣
    3�� �����ź�������У�����ó�������hashmap�У��ӵ�ǰ���ֵ��ʼ��K�� haspmapֵ�ǲ���0�������0���ʾ����������û�д����ֵ
        ��K���������У�
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
				return 0; /* �� nums[i]��ʼ��k����ֻҪ��1��Ϊ0��������Ҫ�� */
			}
			map[v + j]--; /* ���������ҪΪ����map[v] == 0  */
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
