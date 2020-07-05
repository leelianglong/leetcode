/*
* 寻找峰值，由于给定条件最左端 和 最右端的数据都是 -OO, 另外每一个相邻数据都不相等，只要顺着 大于相邻元素的方向找，就能够找到符合条件的峰值元素。
* 对于二分查找，它找的是趋势。
*/


int findPeakElement(int* nums, int numsSize){
    if (numsSize <= 0) {
        return 0;
    }
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) {
            right = mid; // 峰值在左侧，这里mid不加1的原因是，mid所在的位置可能是 峰值
        } else if (nums[mid] < nums[mid + 1]) {
            left = mid + 1; // 可以肯定 mid不是峰值所在
        }
    }
    return left;
}
