### leetcode 667
#### 思路
1. 常规UThash的使用。
2. 字符串常规标准函数使用
#### 代码
```
#define KEY_LEN 51
typedef struct {
    char keyStr[KEY_LEN];
    int val;
    UT_hash_handle hh;
} Hash;

typedef struct {
    Hash* hash;
} MapSum;

MapSum* mapSumCreate() {
    MapSum* obj = (MapSum*)malloc(sizeof(MapSum));
    obj->hash = NULL;
    return obj;
}

void mapSumInsert(MapSum* obj, char * key, int val) {
    char keyStr[KEY_LEN] = {0};
    strcpy(keyStr, key);
    Hash* find;
    HASH_FIND_STR(obj->hash, keyStr, find);
    if (find == NULL) {
        Hash* add = (Hash*)malloc(sizeof(Hash));
        strcpy(add->keyStr, keyStr);
        add->val = val;
        HASH_ADD_STR(obj->hash, keyStr, add);
    } else {
        find->val = val;
    }
}

bool match(char* prefix, char* keystr)
{
    if (strlen(keystr) < strlen(prefix)) {
        return false;
    }
    return strncmp(prefix, keystr, strlen(prefix)) == 0;
}

int mapSumSum(MapSum* obj, char * prefix) {
    int total = 0;
    Hash* cur;
    Hash* tmp;
    HASH_ITER(hh, obj->hash, cur, tmp) {
        if (match(prefix, cur->keyStr)) {
            total += cur->val;
        }
    }
    return total;
}

void mapSumFree(MapSum* obj) {
    Hash* cur;
    Hash* tmp;
    HASH_ITER(hh, obj->hash, cur, tmp) {
        HASH_DEL(obj->hash, cur);
        free(cur);
    }
    free(obj);
}

```