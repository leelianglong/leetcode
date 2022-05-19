### 题目 leetcode 729
### 分析
1. 注意下面1维判重的写法。
2. 也可以尝试使用插旗法思路来判重，参考 leetcode 731
### 代码
```

typedef struct {
    int s;
    int e;
} Key;

struct Hash {
    Key key;
    UT_hash_handle hh;
};

typedef struct {
    struct Hash* hash;
} MyCalendar;


MyCalendar* myCalendarCreate() {
    struct Hash* users = NULL;
    MyCalendar* obj = (MyCalendar*)calloc(1, sizeof(MyCalendar));
    obj->hash = users;
    return obj;
}

bool myCalendarBook(MyCalendar* obj, int start, int end) {
    bool repeat = false;
    struct Hash* cur, *tmp;
    HASH_ITER(hh, obj->hash, cur, tmp) {
        if (cur->key.s <= start && cur->key.e > start 
            || end > cur->key.s && end < cur->key.e 
            ||  start <= cur->key.s && end >= cur->key.e){
            repeat = true;
            break;
        }
    }

    if (!repeat) {
        struct Hash* add = (struct Hash*)calloc(1, sizeof(struct Hash));
        add->key.s = start;
        add->key.e = end;
        HASH_ADD(hh, obj->hash, key, sizeof(Key), add);
    }
    return !repeat;
}

void myCalendarFree(MyCalendar* obj) {
    if (obj == NULL) {
        return;
    }
    struct Hash* cur, *tmp;
    HASH_ITER(hh, obj->hash, cur, tmp) {
        HASH_DEL(obj->hash, cur);
        free(cur);
    }
    free(obj);
}

/**
 * Your MyCalendar struct will be instantiated and called as such:
 * MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, start, end);
 
 * myCalendarFree(obj);
*/
```
