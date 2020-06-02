#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    �������������ҵ�Ŀ��ֵ����ʼλ�úͽ���λ�á�Ŀ��ֵһ�������������Ŀ��ֵ��
    ����[-1,-1];
    Ҫ��ʱ�临�Ӷ���O(logn)
*/
/*
 * Note: The returned array must be malloced, assume caller calls free().
 */
int findBounds(int* nums, int numsSize, int target, bool flag)
{
    int start = 0;
    int end = numsSize - 1;
    int mid;
    int position;

    while (start <= end) {
        mid = (end + start) >> 1;
        if (target < nums[mid]) {
            end = mid - 1;
        } else if (target > nums[mid]) {
            start = mid + 1;
        } else { //�ؼ��㣬���ҵ���ȵ�Ԫ�غ��Ȳ�Ҫֱ���˳����ֱ�������� �� �ұߣ��ҵ��߽���Ԫ��
            position = (flag) ? mid -1 : mid + 1;
            if (position < 0 || position > numsSize - 1 || target != nums[position]) {
                return mid;
            } else {
                if (flag) { 
                    end = position; //��midΪ�磬������ң�
                } else {
                    start = position;//��midΪ�磬���ұ��ң�
                }
            }
        }
    }
    return -1;
}
int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    int* arra = (int*)malloc(sizeof(int) * 2);
    memset(arra, 0, sizeof(int) * 2);
    if (arra == NULL) {
        return NULL;
    }
    if (nums == NULL || numsSize <= 0) {
        arra[0] = -1;
        arra[1] = -1;
        *returnSize = 2;
        return arra;
    }
    arra[0] = findBounds(nums, numsSize, target, true);
    arra[1] = findBounds(nums, numsSize, target, false);
    printf("\r\nposition=%u %u\r\n", arra[0], arra[1]);
    *returnSize = 2;
    return arra;
}

int main(void)
{
    int test[] = {1,2,3,4,5,7,8,8,8,10};
    int* result = NULL;
    int returnSize = 0;
    result = searchRange(test, 10, 8, &returnSize);
    printf("%4d%4d%4d", result[0], result[1], returnSize);
    system("pause");
}