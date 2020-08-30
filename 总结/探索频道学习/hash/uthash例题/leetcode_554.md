### 题目 leetcode 554

题目意思是要从墙上划一条线下来，计算穿过的砖的最小个数。这样如果有某一个点，刚好各层砖在这里都是砖缝，则能够通过的砖就最少是0. 

所以要求串过的砖最少，则要找到尽可能砖缝处。如何找到砖缝处？ 实际上就是不断把砖的长度加起来（前缀和）的位置就是砖缝。如果不同层的砖缝位置一样，

那么它们的前缀和也就一样。我们用这个前缀和作为key, 把它存在hash表中，以出现的次数为 val. 最终我们以这个val从大到小排序， 找出val最大值，意味着最多层的

砖缝在一起，在这个位置上划线，肯定穿过的砖最小。

注意：我们不要把每行的最后一块砖算进去，如果算进去，那么就直接从最后边划线，全都不穿过砖，这个不符合题目要求。

### 代码

```
struct HashStruct {
    int key;
    int times;
    UT_hash_handle hh;
};

struct HashStruct* users;

int Sort(struct HashStruct* a, struct HashStruct* b)
{
    return b->times - a->times;
}

int leastBricks(int** wall, int wallSize, int* wallColSize){
    if (wallSize <= 0) {
        return 0;
    }
    users = NULL;
    struct HashStruct* findKey;
    for (int i = 0; i < wallSize; i++) {
        int k = 0;
        for (int j = 0; j < wallColSize[i] - 1; j++) { // 注意这里的上限 - 1.
            k += wall[i][j];
            HASH_FIND_INT(users, &k, findKey);
            if (findKey == NULL) {
                struct HashStruct* add = (struct HashStruct*)malloc(sizeof(struct HashStruct));
                add->key = k;
                add->times = 1;
                HASH_ADD_INT(users, key, add);
            } else {
                findKey->times++;
            }
        }
    }

    HASH_SORT(users,  Sort);
    
    struct HashStruct* cur;
    struct HashStruct* tmp;
    int max = 0;
    HASH_ITER(hh, users, cur, tmp) { // 要使用这个迭代
        max = cur->times;
        break;
    }
    return wallSize - max;
}
```
