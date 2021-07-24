### leetcode 462
#### 思路
1. 要确定到相等的哪个数是什么？ 这个很关键，答案是中位数。
2. 确定中位数，排序，选择中位数
3. 从各个数据到中位数的差值的绝对值之和。

#### 代码
```
int cmp(const void* a, const void* b)
{
    int* aa = (int*)a;
    int* bb = (int*)b;
    return aa[0] - bb[0];
}

int minMoves2(int* nums, int numsSize){
    int res = 0;
    qsort(nums, numsSize, sizeof(nums[0]), cmp);
    for (int i = 0; i < numsSize; i++) {
        res += abs(nums[numsSize / 2] - nums[i]);
    }
    return res;
}
```