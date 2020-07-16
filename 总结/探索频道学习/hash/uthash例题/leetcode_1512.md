### 题目 leetcode 1512
思路：首先通过HASH找到所有重复的数据；第二步，要找到规律，计算重复数的对数。使用下面的递归。

struct HashTable {
    int key;
    int times;
    UT_hash_handle hh;
};

struct HashTable* users;

int calc(int data)
{
    if (data <= 1) {
        return 0;
    }
    return calc(data - 1) + data -1;
}

int numIdenticalPairs(int* nums, int numsSize){
    if (numsSize < 2) {
        return 0;
    }
    struct HashTable* findKey;
    for (int i = 0; i < numsSize; i++) {
        int search =nums[i];
        HASH_FIND_INT(users, &search, findKey);
        if (findKey == NULL) {
            struct HashTable* add = (struct HashTable*)malloc(sizeof(struct HashTable));
            add->key = search;
            add->times = 1;
            HASH_ADD_INT(users, key, add);
        } else {
            findKey->times++;
        }
    }
    struct HashTable* cur;
    struct HashTable* tmp;
    int counter = 0;
    HASH_ITER(hh, users, cur, tmp) {
        if (cur->times > 1) {
            counter += calc(cur->times);
        }
    }
    HASH_ITER(hh, users, cur, tmp) {
        HASH_DEL(users,cur);
        free(cur);
    }
    return counter;
}
