### 剑指 Offer II 064. 神奇的字典
#### 思路
1. 使用字符串长度为key.注意使用一个二维数组来存储字符串长度一样的字符串，并且使用一个变量来记录当前长度的字符串有几个。详见数据结构定义
2. 据题意要求，长度不相等的字符串肯定不符合要求。长度一样的情况，分为完全一样和不一样的字符数超过2个的。完全一样时有一个特殊用例详见代码注释。
```
#define SIZE 100
typedef struct {
    char buff[SIZE][SIZE + 1];
    int cnt;
} HashData;

struct HashObj {
    int key;
    HashData data;
    UT_hash_handle hh;
};

typedef struct {

} MagicDictionary;

/** Initialize your data structure here. */
struct HashObj* users;
MagicDictionary* magicDictionaryCreate() {
    users = NULL;
    return NULL;
}

void magicDictionaryBuildDict(MagicDictionary* obj, char ** dictionary, int dictionarySize) {
    for (int i = 0; i < dictionarySize; i++) {
        int length = strlen(dictionary[i]);
        struct HashObj* find;
        int key = length;
        HASH_FIND_INT(users, &key, find);
        if (find == NULL) {
            struct HashObj* add = (struct HashObj*)malloc(sizeof(struct HashObj));
            add->key = length;
            int cnt = add->data.cnt = 0;
            strcpy(add->data.buff[cnt], dictionary[i]);
            HASH_ADD_INT(users, key, add);
        } else {
            find->data.cnt++;
            int tmpCnt = find->data.cnt;
            strcpy(find->data.buff[tmpCnt], dictionary[i]);
        }
    }
}

bool moreThanTwoDiff(char* a, char* b, int size)
{
    int cnt = 0;
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            cnt++;
        }
        if (cnt >= 2) {
            return true;
        }
    }
    return false;
} 

bool magicDictionarySearch(MagicDictionary* obj, char * searchWord) {
    int key = strlen(searchWord);
    struct HashObj* find;
    HASH_FIND_INT(users, &key, find);
    if (find == NULL) {
        return false;
    }

    for (int i = 0; i <= find->data.cnt; i++) {
        if (strcmp(find->data.buff[i], searchWord) == 0) { 
            continue; // 这里完全一样时不能直接退出false，应对字典中有一个和searchWord完全一样，还有一个长度一样，但是只差一个不一样的场景。
        }
        if (!moreThanTwoDiff(find->data.buff[i], searchWord, key)) {
            return true;
        }
    }
    return false;
}

void magicDictionaryFree(MagicDictionary* obj) {
    struct HashObj* cur;
    struct HashObj* tmp;
    HASH_ITER(hh, users, cur, tmp) {
        HASH_DEL(users, cur);
        free(cur);
    }
}

/**
 * Your MagicDictionary struct will be instantiated and called as such:
 * MagicDictionary* obj = magicDictionaryCreate();
 * magicDictionaryBuildDict(obj, dictionary, dictionarySize);
 
 * bool param_2 = magicDictionarySearch(obj, searchWord);
 
 * magicDictionaryFree(obj);
*/
```