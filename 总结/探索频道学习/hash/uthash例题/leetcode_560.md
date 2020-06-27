### 题目 leetcode 560

思路：把前缀和sum存入hash表。 在存入之前，先计算一下 sum - k 在hash中是否存在，如果存在，则表示从 sum - k 对应的位置，到目前 sum对应的位置之间的数据之和是 K。把返回结果进行更新

然后在hash表中查找sum是否存在，如果不存在，则把该值添加到hash表，并把出现的频率设置成 1.

如果存在该sum，则把出现的频率 自增。

注意：最开始需要先添加一个节点 0到 hash表。 为什么要有这个？

### 代码
```
struct HashTable {
    int preSum;
    int times;
    UT_hash_handle hh;
};

struct HashTable* users;

int subarraySum(int* nums, int numsSize, int k){
    if (numsSize <= 0) {
        return 0;
    }
    int result = 0;
    int sum = 0;
    struct HashTable* add = (struct HashTable*)malloc(sizeof(struct HashTable));
    add->preSum = 0;
    add->times = 1;
    HASH_ADD_INT(users, preSum, add);

    struct HashTable* findKey;
    struct HashTable* findChange;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        int change = sum - k;
        HASH_FIND_INT(users, &change, findChange);  // 注意这里把找 sum - k 放在前面和放在 添加完 sum 之后再找是有差别的，如果放在后面到 [1] , 0 这个用例不过。
        if (findChange != NULL) {
            result += findChange->times;
        }
        int search = sum;
        HASH_FIND_INT(users, &search, findKey);
        if (findKey == NULL) {
            struct HashTable* tmp = (struct HashTable*)malloc(sizeof(struct HashTable));
            tmp->preSum = sum;
            tmp->times = 1;
            HASH_ADD_INT(users, preSum, tmp);
        } else {
            findKey->times++;
        }
    }
    struct HashTable* cur;
    struct HashTable* tmp;
    HASH_ITER(hh, users, cur, tmp) {
        HASH_DEL(users, cur);
        free(cur);
    }
    return result;
}
```
