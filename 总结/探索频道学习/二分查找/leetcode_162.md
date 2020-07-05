### 题目 leetcode 162

当前题目注意二分查找，是查找一种趋势。顺着趋势查找答案。

### 代码
```
int findPeakElement(int* nums, int numsSize){
    if (numsSize <= 0) {
        return 0;
    }
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) {
            right = mid; // 峰值在左侧，当前mid不减1的原因是，可能mid就是峰值。
        } else if (nums[mid] < nums[mid + 1]) {
            left = mid + 1;//可以确定mid不是峰值。
        }
    }
    return left;
}
```
