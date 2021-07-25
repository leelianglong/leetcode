### leetcode 442
#### 思路
1. 找出出现2次的元素
2. 数字范围是从[1,n]的。
3. 可以看出，每个元素都对应一个位置，如果某个元素重复了，可以一次遍历元素把它作为索引，并把该索引对应的元素乘以-1， 那么第二次遇到他时，它对应的元素就是负数了。
#### 代码
```
int* findDuplicates(int* nums, int numsSize, int* returnSize){
    int* res = (int*)malloc(sizeof(int) * numsSize);
    memset(res, 0, sizeof(int) * numsSize);
    *returnSize = 0;
    for (int i = 0; i < numsSize; i++) {
        int tmp = abs(nums[i]);
        if (nums[tmp - 1] < 0) {
            res[*returnSize] = tmp;
            (*returnSize)++;
            continue; 
        }
        nums[tmp - 1] *= -1; 
    }
    return res;
}
```