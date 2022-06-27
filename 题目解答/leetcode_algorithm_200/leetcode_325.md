### 题目
```
给定一个数组 nums 和一个目标值 k，找到和等于 k 的最长连续子数组长度。如果不存在任意一个符合要求的子数组，则返回 0。

输入: nums = [1,-1,5,-2,3], k = 3
输出: 4 
解释: 子数组 [1, -1, 5, -2] 和等于 3，且长度最长。


输入: nums = [-2,-1,2,1], k = 1
输出: 2 
解释: 子数组 [-1, 2] 和等于 1，且长度最长。
```

### 思路
1. 首先想到前缀和，但是超时
2. 在前缀和的基础上使用hash，通过

### 代码
```
int maxSubArrayLen(int* nums, int numsSize, int k){
    int preSum[numsSize + 1];
    memset(preSum, 0, sizeof(preSum));
    for (int i = 0; i < numsSize; i++) {
        preSum[i + 1] = preSum[i] + nums[i];
    }
    int res = 0;
    for (int i = 0; i < numsSize + 1; i++) {
        for (int j = i; j < numsSize + 1; j++) {
            if (preSum[j] - preSum[i] == k) {
                res = fmax(res, j - i);
            }
        }
    }
    return res;
}


struct HashObj* users;
struct HashObj {
    long key;
    int minIdx;
    UT_hash_handle hh;
};

int HashFind(long sum)
{
    long key = sum;
    struct HashObj* find;
    HASH_FIND_INT(users, &key, find);
    if (find == NULL) {
        return -1;
    }
    return find->minIdx;
}

void HashAdd(long sum, int idx)
{
    long key = sum;
    struct HashObj* find;
    HASH_FIND_INT(users, &key, find);
    if (find == NULL) {
        struct HashObj* add = (struct HashObj*)calloc(1, sizeof(struct HashObj));
        add->key = key;
        add->minIdx = idx;
        HASH_ADD_INT(users, key, add);
        return;
    }
    if (idx < find->minIdx) {
        find->minIdx = idx;
    }
}

int maxSubArrayLen(int* nums, int numsSize, int k){
    users = NULL;
    int res = 0;
    HashAdd(0, 0); // 把前0个和加入,这个很关键
    long sum = 0;
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        sum +=  nums[i];
        j = HashFind(sum - k);
        if (j != -1) {
            res = fmax(res, i - j + 1);
        }
        HashAdd(sum, i + 1);
    }
    return res;
}

```
