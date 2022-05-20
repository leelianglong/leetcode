### 题目 leetcode_732
### 分析
1. 题意也就是说在添加一个区间时，判断截止目前能够添加的区间总数。
### 代码
```
struct Hash {
    int time;
    int val;
    UT_hash_handle hh;
};

typedef struct {
    struct Hash* treeMap;
} MyCalendarThree;

void AddEntry(MyCalendarThree* obj, int time, int val)
{
    struct Hash* tmp = NULL;
    HASH_FIND_INT(obj->treeMap, &time, tmp);
    if (tmp == NULL) {
        tmp = (struct Hash*)calloc(1, sizeof(struct Hash));
        tmp->time = time;
        tmp->val = val;
        HASH_ADD_INT(obj->treeMap, time, tmp);
        return; // 添加完要退出
    }
    tmp->val += val;
    return;
}

void DelEntry(MyCalendarThree* obj, int time, int val)
{
    struct Hash* tmp = NULL;
    HASH_FIND_INT(obj->treeMap, &time, tmp);
    if (tmp == NULL) {
        return;
    }
    tmp->val -= val;
    if (tmp->val == 0) {
        HASH_DEL(obj->treeMap, tmp); // 这里很关键，如果等于0了，就要把这个节点删除。
    }
    return;
}

int cmp(struct Hash* a, struct Hash* b)
{
    return a->time - b->time;
}

MyCalendarThree* myCalendarThreeCreate() {
    MyCalendarThree* obj = (MyCalendarThree*)calloc(1, sizeof(MyCalendarThree));
    obj->treeMap = NULL;
    return obj;
}

int myCalendarThreeBook(MyCalendarThree* obj, int start, int end) {
    AddEntry(obj, start, 1);
    AddEntry(obj, end, -1);
    struct Hash* cur, *tmp;
    int cnt = 0;
    int ret = 0;
    HASH_SORT(obj->treeMap, cmp);
    HASH_ITER(hh, obj->treeMap, cur, tmp){
        cnt += cur->val; // 基于731,729题目的理解，这里就是某个重叠的次数，
        ret = fmax(cnt, ret);
    }
    return ret;
}

void myCalendarThreeFree(MyCalendarThree* obj) {
    if (obj == NULL) {
        return;
    }
    HASH_CLEAR(hh, obj->treeMap);
    free(obj);
}

/**
 * Your MyCalendarThree struct will be instantiated and called as such:
 * MyCalendarThree* obj = myCalendarThreeCreate();
 * int param_1 = myCalendarThreeBook(obj, start, end);
 
 * myCalendarThreeFree(obj);
*/
```
