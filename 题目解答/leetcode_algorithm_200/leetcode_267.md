## 题目
```
给定一个字符串 s ，返回 其重新排列组合后可能构成的所有回文字符串，并去除重复的组合 。

你可以按 任意顺序 返回答案。如果 s 不能形成任何回文排列时，则返回一个空列表。

示例 1：

输入: s = "aabb"
输出: ["abba", "baab"]
示例 2：

输入: s = "abc"
输出: []
1 <= s.length <= 16
s 仅由小写英文字母组成
```
### 思路
1. 通过回溯，枚举出字符串的全排列
2. 通过hash来去重
3. 然后在判断是否是回文
4. 当前方案会超时，只能过部分用例

### 代码
```
#define CNT 10000000
char** res;
int resSize;
int len;

#define KEY_LEN 17
struct HashObj {
    char key[KEY_LEN];
    int times;
    UT_hash_handle hh;
};
struct HashObj* users;

void backTrace(char* s, int idx, char* tmp, int cnt, int* vis)
{
    if (cnt == len) {
        res[resSize] = (char*)calloc(cnt + 1, sizeof(char));
        strcpy(res[resSize], tmp);
        //printf("%s\n", tmp);
        resSize++;
        return;
    }
    for (int i = 0; i < len; i++) {
        if (vis[i]) {
            continue;
        }
        vis[i] = 1;
        tmp[cnt] = s[i];
        cnt++;
        backTrace(s, i + 1, tmp, cnt, vis);
        vis[i] = 0;
        cnt--;
    }
}

bool check(char* s)
{
    int j = len - 1;
    int i = 0;
    for (i = 0, j = len - 1; i < j; i++, j--) {
        if (s[i] != s[j]) {
            return false;
        }
    } 
    return true;
}

char ** generatePalindromes(char * s, int* returnSize){
    res = (char**)calloc(CNT, sizeof(char*));
    resSize = 0;
    len = strlen(s);
    char* tmp = (char*)calloc(len + 1, sizeof(char));
    int* vis = (int*)calloc(len, sizeof(int));
    backTrace(s, 0, tmp, 0, vis);

    users = NULL;
    for (int i = 0; i < resSize; i++) {
        struct HashObj* find;
        HASH_FIND_STR(users, res[i], find);
        if (find == NULL) {
            struct HashObj* add = (struct HashObj*)calloc(1, sizeof(struct HashObj));
            strcpy(add->key, res[i]);
            add->times = 1;
            HASH_ADD_STR(users, key, add);
        } else {
            find->times++;
        }
    }

    int strCnt = HASH_COUNT(users);
    *returnSize = 0;
    char** result = (char**)calloc(strCnt, sizeof(char*));
    struct HashObj* cur, *tmpNode;
    HASH_ITER(hh, users, cur, tmpNode) {
        if (check(cur->key)) {
            result[*returnSize] = (char*)calloc(len + 1, sizeof(char));
            strcpy(result[*returnSize], cur->key);
            (*returnSize)++;
        }
        HASH_DEL(users, cur);
        free(cur);
    }
    return result;
}
```
