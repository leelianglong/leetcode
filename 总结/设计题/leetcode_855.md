### 题意
1. 对于 “他必须坐在能够使他与离他最近的人之间的距离达到最大化的座位上” 这句话的理解。当前题目中是一维数组形式的座位编号。对于第一次进来首先就坐到座位0上，对于第二个考生，就应该坐到最后一个位置上
2. 对于第3个考生进来是，它既可以选择4号座位，离0号座位差3个距离， 也可以选择5号座位，离最后一个座位差3个距离。但是题目要求要选择较小座位号，所以选择4. 4 = （9 - 0） / 2
3. 根据规律，后续进来的考生的座位应该安排到当前位置和上一次位置数字之和 / 2 的位置上。
4. 本题以座位为研究对象，座位要支持任意位置插入和删除，只能采用链表实现。要通过编号查找到要操作的位置，最好使用hash。本题采用UT_hash。 它的底层也是使用链表的。
### 代码及其注释
```
struct Hash {
    int key; // 就是0---N-1，上的数字，表示具体的座位位置。
    UT_hash_handle hh;
};

typedef struct {
    int n;
    struct Hash* seats;
} ExamRoom;


ExamRoom* examRoomCreate(int n) {
    ExamRoom* obj = (ExamRoom*)calloc(1, sizeof(ExamRoom));
    obj->n = n;
    obj->seats = NULL;
    //printf("create\n");
    return obj;
}

int getPos(ExamRoom* obj)
{
    int iterNum = 0; // 遍历的次数
    int cnt = HASH_COUNT(obj->seats); // 当前hashtable中的元素
    struct Hash* cur, *tmp;
    struct Hash* last = NULL; // 用于计算前后2个座位间的距离
    int distance = 0;
    bool first = true; // 主要处理刚进来时 位置0 和 最后一个位置的座位
    int pos = 0;
    HASH_ITER(hh, obj->seats, cur, tmp) {
        iterNum++;
        if (first) { // 处理2端。
            if (cur->key - 0 > distance) {
                pos = 0; // 安排在位置0上
                distance = cur->key;
            }
            if (iterNum == cnt && ((obj->n - 1) - cur->key) > distance) {
                pos = obj->n - 1;
                distance = obj->n - 1 - cur->key;
            }            
            first = false;
            last = cur;
            continue;
        }
        // 处理中间位置上的座位安排，最短距离就是 j - i / 2, 安排的位置也就是这个点。
        if ((cur->key - last->key) / 2 > distance) {
            pos = (cur->key + last->key) / 2;
            distance = (cur->key - last->key) / 2; // 当前位置与上一次位置的最大距离就是
        }
        if ((iterNum == cnt) && ((obj->n - 1) - cur->key) > distance) {
            pos = obj->n - 1;
            distance = (obj->n - 1) - cur->key;
        }
        last = cur;
    }
    return pos;
}

int cmp(const void* a, const void* b)
{
    struct Hash* aa = (struct Hash*)a;
    struct Hash* bb = (struct Hash*)b;
    return aa->key - bb->key;
}

int examRoomSeat(ExamRoom* obj) {
    int pos = 0;
    //printf("pos1 = %d\n", pos);
    if (HASH_COUNT(obj->seats) == 0) {
        pos = 0;
    } else {
        pos = getPos(obj);
    }
    //printf("pos3 = %d\n", pos);
    struct Hash* add = (struct Hash*)calloc(1, sizeof(struct Hash));
    add->key = pos;
    HASH_ADD_INT(obj->seats, key, add);
    HASH_SORT(obj->seats, cmp); // 每次安排座位后，都排一下序，这里是递增序列，为了确保能分配到较小座位上。
    //printf("pos2 = %d\n", pos);
    return pos;
}

void examRoomLeave(ExamRoom* obj, int p) {
    struct Hash* find;
    int key = p;
    HASH_FIND_INT(obj->seats, &key, find);
    HASH_DEL(obj->seats, find);
    free(find);
}

void examRoomFree(ExamRoom* obj) {
    struct Hash* cur, *tmp;
    HASH_ITER(hh, obj->seats, cur, tmp) {
        HASH_DEL(obj->seats, cur);
        free(cur);
    }
    free(obj);
}
```
