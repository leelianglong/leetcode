#include <stdio.h>
#include <stdlib.h>

/*
    对于一个升序数列A，按照某个元素旋转以后得到的序列B，给定一个元素target
    在B序列中查找，是否包含这个target值。
    思路：
    二分搜索，之前二分搜索只是用到了有序数组中，在有旋转的数组中直接应用并不适用。 
    如果中间的数小于最右边的数，则右半段是有序的，若中间数大于最右边数，则左半段是有序的，我们只要在有序的半段里用首尾两个数组来判断目标值是否在这一区域内。
*/
int search(int* nums, int numsSize, int target){
    int start = 0;
    int end = numsSize - 1;
    int mid;

    if (nums == NULL || numsSize <= 0) {
        return -1;
    }

    while (start <= end) {
        mid = start + ((end - start) >> 1);  //二分查找使用这个计算mid避免溢出
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] >= nums[end]) { //中间的数大于最右边的数，说明左半部分是有序的。
            if (target >= nums[start] && nums[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        } else if (nums[mid] < nums[end]) { //中间的数小于最右边的数，说明右半部分是有序的
            if (target <= nums[end] && nums[mid] < target) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        } 
    }
    return -1;
}


int main(void)
{
    int test[] = {3,1};//{4,5,6,7,0,1,2};
    int result;
    result = search(test, 2, 0);
    printf("\r\nresult=%4d\r\n", result);
    system("pause");
}