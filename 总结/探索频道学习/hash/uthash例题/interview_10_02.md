### 思路
1. 首先想到使用作为key， 最初我想到使用map数组作为key, 感觉不是很好表示，参考题解，异位词，排序完他们一定是一样的，所以可以把这个作为key
2. 这里内容要存什么，我之前只存储个次数，这里存储了更多的信息。这里我们像一次扫描，就把相应的结果找到，从例子可以看到，异位词可以有多个，每个又是字符串，所以可以使用二级指针来存储。
这里用二维数组也是可以，但是不确定分配多大空间，所以设置成指针，需要的时候，用多少分配多少。
3. 我们要返回原来的词，所以在添加节点时，可以复制一份出来，排序作为key,把原来的字符串不要改变，因为最终还要返回。一遍扫描完后使用HASH_ITER把节点取出来即可返回。
4. 记得把users 设置成全局变量，在主函数开始的地方，设置成NULL。


### 代码
```
#define KEY_LENGTH 26
#define COUNT 10000

struct HashObj {
    char key[KEY_LENGTH];
    char** res;
    int strNum;
    UT_hash_handle hh;
};

struct HashObj* users;

int cmp(const void* a, const void* b)
{
    char* aa = (char*)a;
    char* bb = (char*)b;
    return strcmp(aa, bb);
}

void AddNode(char* str)
{
    int length = strlen(str) + 1;
    char* tmp = (char*)malloc(sizeof(char) * length);
    memset(tmp, 0, sizeof(char) * length);
    strcpy(tmp, str);
    qsort(tmp, strlen(tmp), sizeof(char), cmp);
    //printf("\n %s--->%s", str, tmp);
    struct HashObj* find = NULL;
    HASH_FIND_STR(users, tmp, find);
    if (find == NULL) {
        find = (struct HashObj*)malloc(sizeof(struct HashObj));
        strcpy(find->key, tmp);
        find->res = (char**)malloc(sizeof(char*) * COUNT);
        find->res[0] = (char*)malloc(sizeof(char) * KEY_LENGTH);
        memset(find->res[0], 0, sizeof(char) * KEY_LENGTH);
        strcpy(find->res[0], str);
        find->strNum = 1;
        HASH_ADD_STR(users, key, find);
    } else {
        find->res[find->strNum] = (char*)malloc(sizeof(char) * KEY_LENGTH);
        memset(find->res[find->strNum], 0, sizeof(char) * KEY_LENGTH);
        strcpy(find->res[find->strNum], str);
        find->strNum++;
    }
}


char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    users = NULL;
    *returnColumnSizes = (int*)malloc(sizeof(int) * COUNT);
    memset(*returnColumnSizes, 0, sizeof(int) * COUNT);
    char*** res = (char***)malloc(sizeof(char**) * COUNT);
    if (strsSize == 0) {
        return res;
    }

    for (int i = 0; i < strsSize; i++) {
        AddNode(strs[i]);
    }
    *returnSize = HASH_COUNT(users);
    struct HashObj* cur, *tmp;
    int i = 0;
    HASH_ITER(hh, users, cur, tmp) {
        res[i] = cur->res;
        (*returnColumnSizes)[i] = cur->strNum;
        i++;
    }
    return res;
}
```
