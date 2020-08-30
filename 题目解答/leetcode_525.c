/*
思路：使用hash记录前缀和 和 首次出现的位置。

重点思路：要利用到「前缀和」还有希望能够通过一次遍历记住结果，多半要使用到哈希表，这里做的一个处理是把所有的 0 都看成 -1，如此一来：
         如果一个区间的和是 0 ，就说明这个区间里的 0（被视为 -1） 和 1 的数量相同；
         
由于求的是最长区间，因此就需要记录前缀和的数值第 1 次出现的下标，相同的前缀再次出现，就说明这一段区间的和为 0（把 0 看成 -1 以后），在遍历的过程中，记录最长的区间的长度；

区间的问题几个思路供参考：1、滑动窗口（双指针） 2、前缀和的差 3、线段树（树状数组

作者：liweiwei1419
链接：https://leetcode-cn.com/problems/contiguous-array/solution/qian-zhui-he-chai-fen-ha-xi-biao-java-by-liweiwei1/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/


struct HashTable {
    int key;
    int pos;
    UT_hash_handle hh;
};

struct HashTable* users;

int findMaxLength(int* nums, int numsSize){
    if (numsSize <= 0) {
        return 0;
    }
    users = NULL;
    int presum = 0;
    struct HashTable* findKey;
    struct HashTable* add = (struct HashTable*)malloc(sizeof(struct HashTable));
    add->key = 0; 
    add->pos = -1;
    HASH_ADD_INT(users, key, add); // 注意这里需要先添加一个
    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            presum += 1;
        } else {
            presum -= 1;
        }
        int search = presum;
        HASH_FIND_INT(users, &search, findKey);
        if (findKey == NULL) {
            struct HashTable* tmp = (struct HashTable*)malloc(sizeof(struct HashTable));
            tmp->key = presum;
            tmp->pos = i;
            HASH_ADD_INT(users, key, tmp);
        } else {
            result = result > (i - findKey->pos) ? result : (i - findKey->pos);
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
