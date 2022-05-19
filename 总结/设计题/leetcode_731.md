### 题目 leetcode 731
### 分析
1. 使用UTHash来处理区间问题。
2. 如何计算区间重叠，可以把区间的端点看成hash节点的 key值，进入区间时，把左端点的key 对应的val设置成1， 离开区间时，把右端点 key对应的value设置成-1，
3. 把hash节点按照从小到大的顺序排序
4. 每添加一个区间进来时，遍历整个hash链表，把他们key对应的value值累加起来。如果不重叠的话，进来时 +1， 离开时 -1，累加起来必定是0， 如果有重叠时，就会不是0. 当前方法很巧妙
-------
### 代码
```
struct Hash {
    int time;
    int value;
    UT_hash_handle hh;
};

typedef struct {
    struct Hash* treeMap;
} MyCalendarTwo;


MyCalendarTwo* myCalendarTwoCreate() {
    MyCalendarTwo* obj = (MyCalendarTwo*)calloc(1, sizeof(MyCalendarTwo));
    obj->treeMap = NULL;
    return obj;
}

void AddCalendar(MyCalendarTwo* obj, int time, int value)
{
    struct Hash* tmp = NULL;
    HASH_FIND_INT(obj->treeMap, &time, tmp);
    if (tmp == NULL) {
        tmp = (struct Hash*)calloc(1, sizeof(struct Hash));
        tmp->time = time;
        tmp->value = value;
        HASH_ADD_INT(obj->treeMap, time, tmp);
        return;
    }
    tmp->value += value;
    return;
}

void DelCalendar(MyCalendarTwo* obj, int time, int val)
{
    struct Hash* tmp = NULL;
    HASH_FIND_INT(obj->treeMap, &time, tmp);
    if (tmp == NULL) {
        return;
    }
    tmp->value -= val;
    if (tmp->value == 0) {
        HASH_DEL(obj->treeMap, tmp);
    }
    return;
}

int cmp(struct Hash* a, struct Hash* b)
{
    return a->time - b->time;
}


bool myCalendarTwoBook(MyCalendarTwo* obj, int start, int end) {
    AddCalendar(obj, start, 1);
    AddCalendar(obj, end, -1);
    struct Hash* cur, *tmp;
    int cnt = 0;
    bool valid = true;
    HASH_SORT(obj->treeMap, cmp);
    printf("start=%d,end=%d, count=%d\n", start, end, HASH_COUNT(obj->treeMap));
    HASH_ITER(hh, obj->treeMap, cur, tmp) {
        cnt += cur->value;
        printf("time=%d, value=%d,cnt=%d\n", cur->time, cur->value, cnt);
        if (cnt >= 3) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        printf("Del start=%d, end=%d\n", start, end);
        DelCalendar(obj, start, 1);
        DelCalendar(obj, end, -1);
    }
    return valid;
}

void myCalendarTwoFree(MyCalendarTwo* obj) {
    HASH_CLEAR(hh, obj->treeMap);
    free(obj->treeMap);
    free(obj);
}

/**
 * Your MyCalendarTwo struct will be instantiated and called as such:
 * MyCalendarTwo* obj = myCalendarTwoCreate();
 * bool param_1 = myCalendarTwoBook(obj, start, end);
 
 * myCalendarTwoFree(obj);
*/
```
