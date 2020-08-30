### 题目 面试16.24

题目意思：设计一个算法，找出数组中两数之和为指定值的所有整数对。一个数只能属于一个数对

实际上算法很简单，就是遍历数组，基于任意一个数a, 然后在剩余的数组中查找是否存在 (target - a), 如果存在就把这2个数字放到返回列表中。

这里关键点是，数组中的元素有重复的元素，并且一个数使用了之后，就不能再被使用。所以需要构造一个结构，能够记录下某个元素出现的次数，每次使用依次后，把该次数

减1， 这里采用hash结构来实现。

算法思路：

1、 构造hash结构，并切遍历数组，把元素存储在hash结构中。

2、 遍历hash 表，查找（a + b） = target的数队。

这里有3个接口：
添加一个节点：
HASH_ADD_INT()   参数：users（hash表头）; key（hash结构中的key）； 添加的节点（该节点的key是数组中的数子，val是1）.
```
            struct Hash* tmp = (struct Hash*)malloc(sizeof(struct Hash));
            tmp->key = key;
            tmp->val = 1;
            HASH_ADD_INT(users, key, tmp);
```

查找一个节点：
HASH_FIND_INT()  参数：users(hash表头)， &key(就是要查找的key,这里要是指针)， findKey(查找后需要返回的节点)
```
        HASH_FIND_INT(users, &key, findKey);
```

遍历hash表
HASH_ITER（） 参数： hh(hash结构需要的参数)， users(hash表头); cur(当前遍历的变量); del(相等于终止上限)
这里HASH_ITER是for循环。

```
    struct Hash* cur;
    struct Hash* del;
    HASH_ITER(hh, users, cur, del) {
    
    }
```

注意：HASH表遍历的时候，要以出现次数小于等于0为终止条件，首先要对自己的出现的次数减1.

### 代码
```
struct Hash {
    int key;
    int val;
    UT_hash_handle hh;
};

struct Hash* users;
#define MAX_PAIRS   5000

int** pairSums(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes){
    int** result = (int**)malloc(sizeof(int*) * MAX_PAIRS);
    for (int i = 0; i < MAX_PAIRS; i++) {
        result[i] = (int*)malloc(sizeof(int) * 2);// 只用存储2个数
        memset(result[i], 0, sizeof(int) * 2);
    }
    *returnSize = 0;
    if (numsSize < 0) {
        return result;
    }
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX_PAIRS);
    memset(*returnColumnSizes, 0, sizeof(int) * MAX_PAIRS);
    users = NULL;
    struct Hash* findKey;
    for (int i = 0; i < numsSize; i++) {
        int key = nums[i];
        findKey = NULL;
        HASH_FIND_INT(users, &key, findKey);
        if (findKey == NULL) {
            struct Hash* tmp = (struct Hash*)malloc(sizeof(struct Hash));
            tmp->key = key;
            tmp->val = 1;
            HASH_ADD_INT(users, key, tmp);
        } else { // 如果找到了，就把次数加1.
            findKey->val++;
        }
    }

    struct Hash* cur;
    struct Hash* del;
    HASH_ITER(hh, users, cur, del) {
        while (cur->val > 0) { // 出现次数要大于0
            cur->val--; // 进来先自减
            int a = cur->key;
            int b = target - a;
            struct Hash* search;
            HASH_FIND_INT(users, &b, search);
            if (search == NULL || search->val == 0) {
                break;
            }
            search->val--;
            result[*returnSize][0] = a;
            result[*returnSize][1] = b;
            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;
        }
    }
    return result;
}
```

