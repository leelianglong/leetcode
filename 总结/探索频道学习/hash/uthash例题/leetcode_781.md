### 题目 leetcode_781

题目的意思是，森林中每个兔子都有颜色，兔子会告诉你 森林里还有多少兔子是和自己颜色一样的，把这些答案放在数组中，根据这个数组，返回森林里最少的兔子数。

这里采用hash来做，hash的key就是一种颜色，它是多少不重要，重要的是，它能区分不同的颜色即可。val用来表示出现的次数。

这里的hash结构如下，由于需要存储的都是int的数据类型。

hash的底层是链表实现，这里定义的users就相等于是链表头，后续的查找，添加，删除都基于这个表头操作，实际上hash中存储的每个节点都具有相同的结构。

HASH_FIND_INT（） 这个宏，第一个参数是表头； 第二个参数，要查找的key, 必须是指针； 第三个参数，存储查找到的节点。

算法：对于anwers[]数组中的每个元素进行遍历，当成可以，首先查询在hash table中查找一下是否包含，如果没有包含，就申请一个节点把该key存储在hash table中

并设置val为1，作为出现的次数。

如果有包含，则先把这种key对应的出现次数加 1， 然后和当前的这个key对应的key + 1 比较大小，如果出现次数大于 (key + 1) 说明当前颜色和已经存在的颜色不一样了

需要改变总数，并且把出现的次数 val 设置成1， 因为又是一种新的颜色出现了。

这里之所以可以把answer中的值作为key，是因为只要这个值不同，那么肯定是2种不同颜色的兔子。


### 代码
```
struct Hash {
    int key;
    int val;
    UT_hash_handle hh;
};

struct Hash* users;
int numRabbits(int* answers, int answersSize){
    if (answersSize <= 0) {
        return 0;
    }
    int cnt = 0;
    users = NULL;
    struct Hash* findKey;
    for (int i = 0; i < answersSize; i++) {
        findKey = NULL;
        int key = answers[i];
        HASH_FIND_INT(users, &key, findKey);
        if (findKey == NULL) {
            cnt += key + 1;
            struct Hash* tmp = (struct Hash*)malloc(sizeof(struct Hash));
            tmp->key = key;
            tmp->val = 1;
            HASH_ADD_INT(users, key, tmp);
        } else { 
            findKey->val++;
            int  num = findKey->key + 1; 
            if (findKey->val > num) { // 处理这种类型： 1，0，1，0，1的，当第三个1来的时候，它肯定和前面的2个1 不是同一种颜色的兔子
                cnt += num;
                findKey->val = 1;
            }
        }
    }
    return cnt;
}
```
