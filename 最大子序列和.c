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
	ע�⣬���η���벿��Ҫʹ�ü�����ѭ����Ŀ����Ҫ������벿�����һ��Ԫ��
	���Ұ벿�ֵ�һ��Ԫ�� �ټ��Ϸֽ����ϵ�Ԫ�أ����ɵ����֡�
	Ȼ�������� �� ����󡢵����֣�������֮��ѡȡ���ġ�
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