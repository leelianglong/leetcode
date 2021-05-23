#### 思路
1.  题目要求除自身以外的所有元素的乘积。 想办法得到 乘积 = 左边数字乘积 * 右边数字乘积。关键在于k的应用，详见注释。
#### 代码
```
int* productExceptSelf(int* nums, int numsSize, int* returnSize){
    int* res = (int* )malloc(sizeof(int) * numsSize);
    memset(res, 0, sizeof(int) * numsSize);
    *returnSize = 0;
    int  k = 1;

    for (int i = 0; i < numsSize; i++) {
        res[i] = k;
        k = k * nums[i]; // res[i] 中存储的是 i 当前元素之前的所有元素的乘积累积，同时k把前面所有元素乘积累积起来了。
    }
    k = 1;
    for (int i = numsSize - 1; i >= 0; i--) {
        res[i] *= k; // k记录了右边个数乘积的累积，然后把它们乘起来。
        k *= nums[i];
    }
    *returnSize = numsSize;
    return res;
}
```