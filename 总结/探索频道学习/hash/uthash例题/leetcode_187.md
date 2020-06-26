### 题目 leetcode 187
题目意思是 要求目标字符串长度是10， 并且在指定的字符串中重复出现。

思路：这里要求的是子串，所以从头开始，每次移动一个字符，取10个字符，依次判断这些子串是否有重复的，有重复的就放在返回列表中

这里直接使用UTHash来判断子串是否有重复出现。

hash结构如下：
struct HashStr {
    char key[11];
    int times;
    UT_hash_handle hh;
};

这里要注意 key需要11，因为要用来存储 10个字符的字符串。

这里的key是固定的数组，所以 使用接口 ：

HASH_FIND_STR(users, 要查找的字符串的地址， 存储查找结构的节点）

HASH_ADD_STR(users， key, 要添加的节点)

// 对hash进行遍历
HASH_ITER(hh, users, cur, tmp) {

}

每次使用完hash 要把所有的hash节点进行释放。


注意： 
每次取字符串的起点位置 要包含 strlen(s) - 10,见下面的 for (int i = 0; i <= strlen(s) - 10; i++) 

注意用例："AAAAAAAAAAA"。


### 代码
```
#define MAX_REPEAT_PAIR    1000

struct HashStr {
    char key[11];
    int times;
    UT_hash_handle hh;
};

struct HashStr* users;

char ** findRepeatedDnaSequences(char * s, int* returnSize){
    *returnSize = 0;
    if (s == NULL || strlen(s) < 10) {
        return NULL;
    }
    struct HashStr* findKey;
    char** result = (char**)malloc(sizeof(char*) * MAX_REPEAT_PAIR);

    for (int i = 0; i <= strlen(s) - 10; i++) {
        char tempArr[11] = {0};
        strncpy(tempArr, &s[i], 10);
        HASH_FIND_STR(users, tempArr, findKey);
        if (findKey == NULL) {
            struct HashStr* tmp = (struct HashStr*)malloc(sizeof(struct HashStr));
            strcpy(tmp->key, tempArr);
            tmp->times = 1;
            HASH_ADD_STR(users, key, tmp);
        } else {
            findKey->times++;
        }
        memset(tempArr, 0, sizeof(char) * 11);
    }

    struct HashStr* cur;
    struct HashStr* tmp;

    HASH_ITER(hh, users, cur, tmp) {
        if (cur->times > 1) {
            result[*returnSize] = (char*)malloc(sizeof(char) * 11);
            memset(result[*returnSize], 0, sizeof(char) * 11);
            strcpy(result[*returnSize], cur->key);
            (*returnSize)++;
        }
    }

    HASH_ITER(hh, users, cur, tmp) {
        HASH_DEL(users, cur);
        free(cur);
    }
    return result;
}
```
