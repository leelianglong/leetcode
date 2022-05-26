### 题目 leetcode 1845
### 分析
1. 题目要求每次返回最小的座位号，数量比较具体，第一次直接使用数组管理数据，超时
2. 每次返回最小的座位号，可以使用小根堆来管理数据，获取座位时，表示就是把堆顶元素返回，并删除堆顶元素。释放座位时，就是往堆里插入一个元素。插入和删除时都需要对堆上的元素进行调整使其满足堆的要求。
3. 当前堆在底层使用数组时，元素从1开始存储。方便父子节点坐标换算。
4. 细节见代码注释
-----
### 代码
```
typedef struct {
    int* heap;
    int heapSize;
    bool (*cmp)(int, int);
} SeatManager;

bool cmp(int a, int b)
{
    return a > b;
}

static void swap(int* a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 从下往上找
void push(SeatManager* obj, int x)
{
    int child = ++obj->heapSize; // heapSize++ 就表示把节点添加到堆中了， 这里也同时是孩子节点坐标.
    obj->heap[child] = x;
    int parent = child >> 1;
    while (parent) {
        if (obj->cmp(obj->heap[child], obj->heap[parent])) { // 如果孩子不大于父亲节点，即找到插入点，退出，
            break;
        }
        swap(&obj->heap[child], &obj->heap[parent]);
        child = parent; // 当前节点来到父节点
        parent = child >> 1;
    }
}

// 从上往下找。
void pop(SeatManager* obj)
{
    swap(&obj->heap[1], &obj->heap[obj->heapSize]); // 吧最后一个元素和第一个元素交换，目的是想删除第一个元素。
    obj->heapSize--; // 删除了最后一个元素
    int parent = 1;
    int child = parent << 1; 
    while (child <= obj->heapSize) {
        if (child + 1 <= obj->heapSize) { // 有右孩子的情况
            if (obj->cmp(obj->heap[child], obj->heap[child + 1])) {
                child++;
            }
        }
        if (obj->cmp(obj->heap[child], obj->heap[parent])) {
            break;
        }
        swap(&obj->heap[parent], &obj->heap[child]);
        parent = child;
        child = parent << 1; // 继续下移
    } 
}

int top(SeatManager* obj)
{
    return obj->heap[1];
}

SeatManager* seatManagerCreate(int n) {
    SeatManager* obj = (SeatManager*)calloc(1, sizeof(SeatManager));
    obj->heap = (int*)calloc((n + 1), sizeof(int));
    obj->cmp = cmp;
    obj->heapSize = 0;
    for (int i = 1; i <= n; i++) {
        push(obj, i);
    }
    return obj;
}

int seatManagerReserve(SeatManager* obj) {
    int res = top(obj);
    pop(obj);
    return res;
}

void seatManagerUnreserve(SeatManager* obj, int seatNumber) {
    push(obj, seatNumber);
}

void seatManagerFree(SeatManager* obj) {
    free(obj->heap);
    free(obj);
}
```
