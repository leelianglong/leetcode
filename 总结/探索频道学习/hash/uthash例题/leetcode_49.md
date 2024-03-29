### 题目 leetcode 49

思路：使用UThash，记录每个异位词出现的位置 和 个数。遍历完整个字符串数组后，在以异位词的种类申请返回行数， 再以每个异位词的个数，申请每一行要放的个数。之前已经记录了每个异位词的位置，这里直接

拷贝到最终结果中即可。

注意：由于使用的UThash, 不支持把一段内存作为key,所以不能直接把所有的字符串进行hash转换（hash[str[i]++）后 这里就先使用快排，把异位词排序后，就得到同样的字符串，把这个字符串作为key。

然后使用基本的HASh操作，HASH_FIND_STR()  HASH_ADD_STR() HASH_COUNT()， 完成操作。

对于UThash 的结构，可以使用结构体作为data，这样使UThash更方便操作。


### 代码
```
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define MAX_COUNTER  100
#define MAX_STRLEN   26
typedef struct {
    int times;
    int pos[MAX_COUNTER];
    int curPos;
} HashData;

struct HashStr {
    char key[MAX_STRLEN]; 
    HashData data;
    UT_hash_handle hh;
};

struct HashStr* users;

int cmp(const void* a , const void* b)
{
    char* aa = (char*)a;
    char* bb = (char*)b;

    return strcmp(aa, bb);
}

char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    if (strsSize <= 0) {
        return NULL;
    }
    char*** result = (char***)malloc(sizeof(char**) * strsSize);
    users = NULL;
    struct HashStr* findKey = NULL;
    char* sortStr = (char*)malloc(sizeof(char) * MAX_STRLEN);
    memset(sortStr, 0, sizeof(char) * MAX_STRLEN);
    for (int i = 0; i < strsSize; i++) {
        strcpy(sortStr, strs[i]);
        qsort(sortStr, strlen(strs[i]), sizeof(char), cmp);
        HASH_FIND_STR(users, sortStr, findKey);
        if (findKey == NULL) {
            struct HashStr* tmpNode = (struct HashStr*)malloc(sizeof(struct HashStr));
            memset(tmpNode->data.pos, 0, sizeof(int) * MAX_COUNTER);
            tmpNode->data.curPos = 0;
            tmpNode->data.pos[tmpNode->data.curPos] = i;
            strcpy(tmpNode->key, sortStr);
            tmpNode->data.times = 1;
            HASH_ADD_STR(users, key, tmpNode);
        } else {
            findKey->data.times++;
            findKey->data.curPos++;
            findKey->data.pos[findKey->data.curPos] = i;
        }
    }
    struct HashStr* cur;
    struct HashStr* tmp;
    int strnum = HASH_COUNT(users);
    *returnColumnSizes = (int*)malloc(sizeof(int*) * strnum);
    
    HASH_ITER(hh, users, cur, tmp) {
        result[*returnSize] = (char**)malloc(sizeof(char*) * cur->data.times);
        #if 0
        printf("\n times=%d:", cur->data.times);
        for (int j = 0; j < cur->data.times; j++) {
            printf(" %d,", cur->data.pos[j]);
        }
        #endif
        for (int i = 0; i < cur->data.times; i++) {
            result[*returnSize][i] = (char*)malloc(sizeof(char) * 26);
            memset(result[*returnSize][i], 0, sizeof(char) * 26);
            strcpy(result[*returnSize][i], strs[cur->data.pos[i]]);
            //printf("\n %s", strs[cur->data.pos[i]]);
        }
        (*returnColumnSizes)[*returnSize] = cur->data.times;
        (*returnSize)++;
    }
 
    return result;
}
```
### 再次重写
1. 注意在查找和添加时，要使用key 来存储key. 使用其他值，uthash报错。注意key 和 data的规划。
```
#define KEY_LEN 101
#define COUNT 10000

typedef struct {
    int pos[KEY_LEN];
    int curCnt;
} HashData;

typedef struct {
    char key[KEY_LEN];
    HashData data;
    UT_hash_handle hh;
} HashObj;

int cmp(const void* a, const void* b)
{
    return *(char*)a - *(char*)b;
}

char *** groupAnagrams(char ** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    char*** res = (char***)malloc(sizeof(char**) * COUNT);
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * COUNT);
    memset(*returnColumnSizes, 0, sizeof(int) * COUNT);
    HashObj* user = NULL;

    char tmpSave[KEY_LEN] = {0};
    for (int i = 0; i < strsSize; i++) {
        memset(tmpSave, 0, sizeof(tmpSave));
        strcpy(tmpSave, strs[i]);
        qsort(tmpSave, strlen(strs[i]), sizeof(strs[i][0]), cmp);
        HashObj* find = NULL;
        char key[KEY_LEN] = {0};
        strcpy(key, tmpSave);
        HASH_FIND_STR(user, key, find);
        if (find == NULL) {
            HashObj* add = (HashObj*)malloc(sizeof(HashObj));
            strcpy(add->key, tmpSave);
            add->data.curCnt = 0;
            add->data.pos[add->data.curCnt] = i;
            HASH_ADD_STR(user, key, add);
        } else {
            find->data.curCnt++;
            find->data.pos[find->data.curCnt] = i;
        }
    }
    HashObj* tmp;
    HashObj* cur;
    HASH_ITER(hh, user, cur, tmp) {
        (*returnColumnSizes)[*returnSize] = (cur->data.curCnt + 1);
        res[*returnSize] = (char**)malloc(sizeof(char**) * (cur->data.curCnt + 1));
        for (int i = 0; i <= cur->data.curCnt; i++) {
            res[*returnSize][i] = (char*)malloc(strlen(cur->key) + 1);
            memset(res[*returnSize][i], 0, (strlen(cur->key) + 1));
            strcpy(res[*returnSize][i], strs[cur->data.pos[i]]);
        }
        (*returnSize)++;
        HASH_DEL(user, cur);
        free(cur);
    }
    return res;
}
```