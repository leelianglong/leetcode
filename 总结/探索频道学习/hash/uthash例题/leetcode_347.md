### 题目 leetcode 347

思路： 常规的HASH 算法，注意几个接口的使用 

HASH_ADD_INT()

HASH_FIND_INT()

HASH_ITER()

HASH_DEL()

使用 UTHash解题时，应该在结束后删除hash中的所有节点。否则可能会导致多个用例一起执行时，出现错误。

### 代码
```
struct HashTable {
     int key;
     int times;
     UT_hash_handle hh;
 };

struct HashTable* users;

int Cmp(const void* a, const void* b)
{
    return ((struct HashTable*)b)->times - ((struct HashTable*)a)->times;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    if (numsSize <= 0) {
        return NULL;
    }
    *returnSize = 0;
    int* result = (int*)malloc(sizeof(int) * k);
    memset(result, 0, sizeof(int) * k);

    struct HashTable* findKey;
    for (int i = 0; i < numsSize; i++) {
        int searchNum = nums[i];
        HASH_FIND_INT(users, &searchNum, findKey);
        if (findKey == NULL) {
            struct HashTable* tmp = (struct HashTable*)malloc(sizeof(struct HashTable));
            tmp->key = searchNum;
            tmp->times = 1;
            HASH_ADD_INT(users, key, tmp);
        } else {
            findKey->times++;
        }
    }

    HASH_SORT(users, Cmp);

    struct HashTable* cur;
    struct HashTable* tmp;

    HASH_ITER(hh, users, cur, tmp) {
        result[*returnSize] = cur->key;
        (*returnSize)++;
        if (*returnSize >= k) {
            break;
        }
    }
    HASH_ITER(hh, users, cur, tmp) {
        HASH_DEL(users, cur);
        free(cur);
    }
    *returnSize = k;
    return result;
}
```
