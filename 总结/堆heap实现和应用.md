## 概念
1. 最大堆和最小堆都是一颗完全二叉树。该树中的某个节点的值总是大于或者不大于其左右子节点。可以使用数组来存储这个完全二叉树，因为数组的下标和二叉树的节点存在一一对应的映射关系。即如果跟节点索引是i, 那么它的左子树的索引就是 2 * i + 1， 右子树的索引就是 2 * i + 2.
2. 如果完全二叉树的所有子树的最大值在堆顶，就是大根堆。反之是小根堆。
3. 数组首元素存储的是根节点。
4. 堆一般提供2个操作，插入 和 删除，以小根堆为例。 
5. 插入操作就是拿当前元素和其父节点比较，如果比父节点小，则直接把当前节点和父节点对调，反之，可以直接插入； 
6. 删除操作，就是删除堆顶元素，是将树中租后一个节点替换到被删除的根节点，然后自顶向下，递归调整使其符合最小堆要求。
7.  一个参考帖子：https://blog.csdn.net/Sun_student/article/details/86658649

## 实现

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 * 大顶堆的概念就是父亲节点的值大于孩子节点的值
 * 下面算法实现大根堆。 这里跟的索引是0，
 * 左子树的索引是 2*i + 1
 * 右子树的索引是 2*i + 2.
 * 下面提供2中操作，往大根堆中添加一个数，使其还是大根堆；从大根堆中删除一个数，还继续保持大根堆。
 * */
typedef struct {
    int capacity;
    int curSize;
    int* data;
} Heap;

#define SWAP(arr, a, b) do {\
    int tmp = arr[a];\
    arr[a] = arr[b];\
    arr[b] = tmp;\
} while (0)
#define  MAX_LENTH 10000
bool IsEmpty(Heap* obj)
{
    return obj->curSize == 0;
}

bool IsFull(Heap* obj)
{
    return obj->curSize == MAX_LENTH;
}

Heap* InitHeap()
{
    Heap* obj = (Heap*)malloc(sizeof(Heap));
    obj->capacity = MAX_LENTH;
    obj->curSize = 0;
    obj->data = (int*)malloc(sizeof(int) * MAX_LENTH);
    memset(obj->data, 0, sizeof(int) * MAX_LENTH);
    return obj;
}

// 从index位置往上找，找父节点，跟父节点比较，如果比父节点大，则彼此交换。
void InsertHeap(Heap* obj, int index)
{
    while (obj->data[index] > obj->data[(index - 1)/2]) {
        SWAP(obj->data, index, (index - 1) / 2);
        index = (index - 1) / 2;
    }
}

void Push(Heap* obj, int value)
{
    if (obj->curSize == MAX_LENTH) {
        return;
    }
    obj->data[obj->curSize] = value;
    InitHeap(obj, obj->curSize);
    obj->curSize++;
}

// 从index节点往下找，不断下沉，当我的孩子不再比我大，或者没有孩子节点时，就停止
void Heapify(Heap* obj, int index)
{
    int left = index * 2 + 1;
    while (left < obj->curSize) { // 左孩子不越界。
        //左右孩子谁大，把谁的下标给largest。left + 1 就是右孩子坐标
        int largest = left + 1 < obj->curSize && obj->data[left + 1] > obj->data[left] ? left + 1 : left;
        largest = obj->data[largest] > obj->data[index] ? largest : index;
        if (largest == index) {
            break;
        }
        SWAP(obj->data, largest, index);
        index = largest;
        left = index * 2 + 1;
    }
}

int Pop(Heap* obj)
{
    int ans = obj->data[0];
    obj->curSize--;
    SWAP(obj->data, 0, obj->curSize);
    Heapify(obj, 0);
    return  ans;
}
int main() {
    printf("hello world");
    return 0;
}

```

### 堆的另一种实现
#### 思路
1. 堆中的元素从位置1开始放，0位置不放元素。这样我们计算已知父亲节点的位置，计算孩子节点的位置使用位运算符，parent << 1(左孩子位置), (parent<< 1  | 1), 这就是右孩子的位置。 如果知道孩子节点位置，计算父亲节点位置 child >> 1.
2. 给元素往堆中插入时，先把heapSize++， 就放在堆的最末尾，然后，就从最末尾往上看，笔记它根自己父节点的大小关系，再根据大小根堆，来判断是否调整
3. 删除一个元素时，总是从根节点删除，可以把堆最默认的元素拿去顶替根节点元素，并把堆大小heapsize的计数减1，然后把该元素逐步下沉，找到合适位置(这里合适的位置一定是较大孩子的位置)。
4. 注意每次插入 和 删除操作，都涉及到对堆内的元素重新排布使其成为堆。 所以要获取堆顶元素时，不能硬编码，需要使用gettop()接口来获取。
#### 代码
```
typedef struct {
    int heapSize; // 表示当前堆中元素大小
    int* buff;
    bool (*cmp)(int, int);
} Heap;

typedef struct {
    Heap* heap;
    int maxSize; // 表示只用关注的堆中的最多的元素个数
}KSmallest;

bool cmp(int a, int b)
{
    return a > b;
}

void initHeap(Heap* obj, int k, bool (*cmp)(int, int))
{
    obj->buff = (int*)malloc(sizeof(int) * (k + 1)); // 堆中的元素从1位置开始放起。
    memset(obj->buff, 0, sizeof(int) * (k + 1));
    obj->heapSize = 0;
    obj->cmp = cmp;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 把一个元素添加到堆中，使其堆结构保持正确(当前是大根堆）
void push(Heap* obj, int x)
{
    obj->heapSize++;
    obj->buff[obj->heapSize] = x;
    int child = obj->heapSize;
    int parent = child >> 1; // 这里准备上浮
    while (parent) { //  表示 还没有到达堆顶 parent = 0。
        if (obj->cmp(obj->buff[parent], obj->buff[child])) { // 当父亲节点大于孩子节点时就停止交换。
            break;
        }
        swap(&obj->buff[parent], &obj->buff[child]);
        child = parent;// 继续向上推进
        parent = child >> 1;
    }
}

// 删除根节点元素，使其剩余元素保持堆结构正确
void pop(Heap* obj)
{
    swap(&obj->buff[1], &obj->buff[obj->heapSize]); // 这里把堆顶元素和最后一个元素交换
    obj->heapSize--; // 堆中元素减1表示，上面交换到堆尾部的元素已经无效了
    int parent = 1;
    int child = parent << 1; // 这里准备下沉
    while (child <= obj->heapSize) { // 当前孩子节点还没有到堆的尾部
        if (child + 1 <= obj->heapSize) {
            if (obj->cmp(obj->buff[child + 1], obj->buff[child])) { // 找一下有没有更大的孩子节点
                child += 1;
            }
        }
        if (obj->cmp(obj->buff[parent], obj->buff[child])) {
            break;
        }
        swap(&obj->buff[parent], &obj->buff[child]);
        parent = child;
        child = parent << 1; // 这里继续下沉
    }
}

int getTop(Heap* obj) {
    return obj->buff[1];
}

int print(int* buff, int size)
{
    for (int i = 1; i <= size; i++) {
        printf("%d ", buff[i]);
    }
}

int main(void)
{
    printf("hello world\n");
    int test[] = {1,2,3,4,5,6,7,8,9,10};
    int k = 5;
    KSmallest* obj = (KSmallest*)malloc(sizeof(KSmallest));
    obj->maxSize = k;
    obj->heap = (Heap*)malloc(sizeof(Heap));
    initHeap(obj->heap, k + 1, cmp); //  注意这里也要是 k + 1
    for (int i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
        push(obj->heap, test[i]);
        printf("top=%u\n", getTop(obj->heap));
        print(obj->heap->buff, obj->heap->heapSize);
        printf("\n");
        if (obj->heap->heapSize > obj->maxSize) {
            printf("enter %d\n", test[i]);
            pop(obj->heap);
        }
        printf("real content:\n");
        print(obj->heap->buff, obj->heap->heapSize);
        printf("\n");
    }
    system("pause");
    return 0;
}
```
### 1046. 最后一块石头的重量
#### 思路
1. 建立大根堆，然后每次取出堆顶2个元素，然后，使其做差值，再添加到堆中。 最后判断堆中元素是否1，如果是1，则直接返回堆顶元素，否则返回0
2. 在取出元素时，要先获取堆顶元素后，执行 pop()接口，然后在获取堆顶元素 再执行pop（）， 不能直接硬编码成获取堆中前2个元素。 
#### 代码
1. 正确解法
```
typedef struct {
    int heapSize;
    int* buff;
    bool (*cmp)(int, int);
} Heap;

typedef struct {
    Heap* heap;
    int maxSize;
} KSmallest;

bool cmp(int a, int b)
{
    return a > b;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void init (Heap* obj, int k, bool (*cmp)(int, int))
{
    obj->buff = (int*)malloc(sizeof(int) * (k + 1));
    memset(obj->buff, 0, sizeof(int) * (k + 1));
    obj->heapSize = 0;
    obj->cmp = cmp;
}

void push(Heap* obj, int x)
{
    obj->heapSize++;
    obj->buff[obj->heapSize] = x;
    int child = obj->heapSize;
    int parent = child >> 1;

    while (parent) {
        if (obj->cmp(obj->buff[parent], obj->buff[child])) {
            break;
        }
        swap(&obj->buff[parent], &obj->buff[child]);
        child = parent;
        parent = child >> 1;
    }
}

void pop(Heap* obj)
{
    swap(&obj->buff[1], &obj->buff[obj->heapSize]);
    obj->heapSize--;
    int parent = 1;
    int child = parent << 1;
    while (child <= obj->heapSize) {
        if (child + 1 <= obj->heapSize) {
            if (obj->cmp(obj->buff[child + 1], obj->buff[child])) {
                child += 1;
            }
        }
        if (obj->cmp(obj->buff[parent], obj->buff[child])) {
            break;
        }
        swap(&obj->buff[parent], &obj->buff[child]);
        parent = child;
        child = parent << 1;
    }
}

int getTop(Heap* obj)
{
    return obj->buff[1];
}

void print(Heap* obj)
{
    for (int i = 1; i <= obj->heapSize; i++) {
        printf("%d ", obj->buff[i]);
    }
}

int lastStoneWeight(int* stones, int stonesSize){
    if (stonesSize < 2) {
        return stones[0];
    }
    if (stonesSize < 3) {
        return abs(stones[1] - stones[0]);
    }
    KSmallest* obj = (KSmallest*)malloc(sizeof(KSmallest));
    obj->heap = (Heap* )malloc(sizeof(Heap));
    obj->maxSize = stonesSize;

    init(obj->heap, stonesSize + 1, cmp);
    for (int i = 0; i < stonesSize; i++) {
        push(obj->heap, stones[i]);
    }
    while (obj->heap->heapSize > 1) {
        int a1 = getTop(obj->heap);
        pop(obj->heap);
        int a2 = getTop(obj->heap);
        pop(obj->heap);
        int diff = a1 - a2;
        if (diff > 0) {
            push(obj->heap, diff);
        }
    }
    return obj->heap->heapSize == 1 ? obj->heap->buff[1] : 0;
}
```
2. 不正确解法
```
typedef struct {
    int heapSize;
    int* buff;
    bool (*cmp)(int, int);
} Heap;

typedef struct {
    Heap* heap;
    int maxSize;
} KSmallest;

bool cmp(int a, int b)
{
    return a > b;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void init (Heap* obj, int k, bool (*cmp)(int, int))
{
    obj->buff = (int*)malloc(sizeof(int) * (k + 1));
    memset(obj->buff, 0, sizeof(int) * (k + 1));
    obj->heapSize = 0;
    obj->cmp = cmp;
}

void push(Heap* obj, int x)
{
    obj->heapSize++;
    obj->buff[obj->heapSize] = x;
    int child = obj->heapSize;
    int parent = child >> 1;

    while (parent) {
        if (obj->cmp(obj->buff[parent], obj->buff[child])) {
            break;
        }
        swap(&obj->buff[parent], &obj->buff[child]);
        child = parent;
        parent = child >> 1;
    }
}

void pop(Heap* obj)
{
    swap(&obj->buff[1], &obj->buff[obj->heapSize]);
    obj->heapSize--;
    int parent = 1;
    int child = parent << 1;
    while (child <= obj->heapSize) {
        if (child + 1 <= obj->heapSize) {
            if (obj->cmp(obj->buff[child + 1], obj->buff[child])) {
                child += 1;
            }
        }
        if (obj->cmp(obj->buff[parent], obj->buff[child])) {
            break;
        }
        swap(&obj->buff[parent], &obj->buff[child]);
        parent = child;
        child = parent << 1;
    }
}

void print(Heap* obj)
{
    for (int i = 1; i <= obj->heapSize; i++) {
        printf("%d ", obj->buff[i]);
    }
}

int lastStoneWeight(int* stones, int stonesSize){
    if (stonesSize < 2) {
        return stones[0];
    }
    if (stonesSize < 3) {
        return abs(stones[1] - stones[0]);
    }
    KSmallest* obj = (KSmallest*)malloc(sizeof(KSmallest));
    obj->heap = (Heap* )malloc(sizeof(Heap));
    obj->maxSize = stonesSize;

    init(obj->heap, stonesSize + 1, cmp);
    for (int i = 0; i < stonesSize; i++) {
        push(obj->heap, stones[i]);
    }

    while (obj->heap->heapSize > 1) {
        int a1 = obj->heap->buff[1];
        int a2 = obj->heap->buff[2];  // 这里是硬编码了。。。 [7,5,8]这样的用例就有问题
        int diff = a1 - a2;
        pop(obj->heap);
        pop(obj->heap);
        if (diff > 0) {
            push(obj->heap, diff);
        }
    }
    return obj->heap->heapSize == 1 ? obj->heap->buff[1] : 0;
}
```



## 应用
### leetcode 378
#### 代码
```
typedef struct {
    int val;
    int x;
    int y;
} point;

bool cmp(point a, point b)
{
    return a.val >= b.val;
}

void swap(point* a, point* b)
{
    point t = *a;
    *a = *b;
    *b = t;
}

void push(point* heap, int* size, point* p)
{
    heap[++(*size)] = *p;
    int s = *size;
    while (s > 1) { // 堆中元素大于1个，把这个新进来的元素放在合适的位置。
        if (cmp(heap[s], heap[s >> 1])) {
            break;
        }
        swap(&heap[s], &heap[s >> 1]);
        s >>= 1;
    }
}

void pop(point* heap, int* size)
{
    heap[1] = heap[(*size)--];
    int p = 1;
    int s = 2;

    while (s <= *size) {
        if (s <*size && !cmp(heap[s + 1], heap[s])) {
            s++;
        }
        if (cmp(heap[s], heap[p])) {
            break;
        }
        swap(&heap[s], &heap[p]);
        p = s;
        s = p << 1;
    }
}

int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k){
    point heap[matrixSize + 1];
    int size = 0;
    for (int i = 0; i < matrixSize; i++) {
        point p = {matrix[i][0],i,0}; // 矩阵第i行首元素
        push(heap, &size, &p);// 把第i行首元素入堆
    }

    for (int i = 0; i < k - 1; i++) {
        point now = heap[1];
        pop(heap, &size);
        if (now.y != matrixSize - 1) {
            point p = {matrix[now.x][now.y + 1], now.x, now.y + 1};
            push(heap, &size, &p);
        }
    }
    return heap[1].val;
}
```


### 剑指 Offer II 059. 数据流的第 K 大数值
#### 思路
1. 维护一个长度为k的优先队列，最小的元素在队头。
2. 这个优先队列使用堆来实现。
#### 代码
```
struct Heap {
    int heapSize; // 表示当前堆中已经收集的元素个数。
    int* heap; // 存储元素
    bool (*cmp)(int, int); // 比较指针，在往堆中添加元素或者删除元素时，用于调整。
};

void init(struct Heap* obj, int n, bool (*cmp)(int,int))
{
    obj->heap = (int*)malloc(sizeof(int) * (n + 1));
    obj->heapSize = 0;
    obj->cmp = cmp;
}

bool cmp(int a, int b)
{
    return a > b;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 需要把x添加到堆中。添加的时候，是先填到最后面，然后从下往上看，逐渐找到它应该的位置。
void push(struct Heap* obj, int x)
{
    int p = ++(obj->heapSize); // 当前heapsize先加1。可见在0位置是没有存储节点。这个heapsize就是从1开始来计算的。
    int q = p >> 1; // q实际上就是p父节点的位置。
    obj->heap[p] = x; // 先存储x到p位置，然后在当前位置往上看，看它与父亲节点的大小关系，再根据大小根堆，左不同的处理。
    while (q) { // 父节点位置，如果为0了，也说明到顶了，不需要交换了。
        if (!obj->cmp(obj->heap[q], obj->heap[p])) {
            break; // 表示 父节点小于当前节点，则停下来，这里创建的是小根堆。
        }
        swap(&obj->heap[q], &obj->heap[p]); // 当前节点和父节点交换。
        p = q; // 然后当前节点来到父节点
        q = p >> 1; // 继续计算父节点。
    }
}

// 删除的时候，实际上删除的是对顶元素，然后，把堆最后的元素，从上往下计算找到合适的位置。
void pop(struct Heap* obj) {
    swap(&obj->heap[1], &obj->heap[(obj->heapSize)--]); 
    int p = 1; // 当前节点
    int q = p << 1; // 是p的孩子节点
    while (q <= obj->heapSize) { // 在该孩子节点位置小于堆中元素的情况下
        if (q + 1 <= obj->heapSize) { // 这个表示p的右孩子也有的情况下。
            if (obj->cmp(obj->heap[q], obj->heap[q + 1])) {
                q++; // 如果左孩子比有孩子还大，孩子节点就走到右孩子节点上。
            }
        }
        // 当前q是孩子节点中较大的。
        if (!obj->cmp(obj->heap[p], obj->heap[q])) {
            break; // 如果父亲节点p 不大于 孩子节点 q， 就停止
        }
        swap(&obj->heap[q], &obj->heap[p]); // 这里是把父亲节点p 和 较大的孩子节点进行交换
        p = q; // 重新下移。
        q = p << 1;
    }
}

int top(struct Heap *obj)
{
    return obj->heap[1]; // 堆顶元素是位置1上的值。
}

typedef struct {
    struct Heap* heap;
    int maxSize;
} KthLargest;

void kthLargestFree(KthLargest* obj);
int kthLargestAdd(KthLargest* obj, int val);
KthLargest* kthLargestCreate(int k, int* nums, int numsSize);

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
    memset(obj, 0, sizeof(KthLargest));
    obj->heap = (struct Heap*)malloc(sizeof(struct Heap));
    init(obj->heap, k + 1, cmp);
    obj->maxSize = k;
    for (int i = 0; i < numsSize; i++) {
        kthLargestAdd(obj, nums[i]);
    }
    return obj;
}

int kthLargestAdd(KthLargest* obj, int val) {
    push(obj->heap, val);
    if (obj->heap->heapSize > obj->maxSize) {
        pop(obj->heap);
    }
    return top(obj->heap);
}

void kthLargestFree(KthLargest* obj) {
    free(obj->heap->heap);
    free(obj->heap);
    free(obj);
}

```

### 剑指 Offer II 061. 和最小的 k 个数对
#### 思路
1. 把每个数值对看成堆中的元素存起来。
2. 这里求最小的K个元素对，所以要使用大根堆。
3. 往堆中添加元素时，如果当前元素比它的父节点大，则需要把它和它的父节点进行交换，直到没有父节点或者不在比父节点大的时候
4. 堆的删除都是删除堆顶元素，把最后一个元素拿上来，清除了堆顶的元素，然后把这个元素逐步下沉，当前这个元素作为父节点，然后往下看，查看它的左右孩子是否有比他大的，如果有的话，需要把它和它较大的孩子节点进行交换。交换完了，再继续下沉。上一步如果没有孩子节点比它大，就直接停止。
5. 在调试堆的代码时，可以把堆顶元素打印出来，然后添加或删除时，都查看一下堆顶元素，看看是否符合预期
6. 堆的数据结构中，要保存元素外，还需要保存当前堆中的元素个数。
7. 堆中的元素是从位置1开始放的。注意初始化堆的大小以及何时进行删除堆顶的操作
#### 代码
```
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct {
    int x;
    int y;
} Pos;

typedef struct {
    int heapSize;
    Pos* pos;
    bool (*cmp)(int, int);
} Heap;

bool cmp(int a, int b)
{
    return a > b;
}

void swap(Pos* a, Pos* b)
{
    Pos tmp = *a;
    *a = *b;
    *b = tmp;
}

void init(Heap* obj, int size, bool (*cmp)(int, int))
{
    obj->pos = (Pos*)malloc(sizeof(Pos) * (size + 1));
    memset(obj->pos, 0, sizeof(Pos) * (size + 1));
    obj->heapSize = 0; // 当前没有元素
    obj->cmp = cmp;
}

// 下堆中添加一个元素。自底向上
void push(Heap* obj, int x, int y)
{
    int child = ++obj->heapSize; // 这个要先++。
    int parent = child >> 1;
    obj->pos[child].x = x;
    obj->pos[child].y = y;
    while (parent) {
        int valP = obj->pos[parent].x + obj->pos[parent].y;
        int valC = obj->pos[child].x + obj->pos[child].y;
        if (!obj->cmp(valC, valP)) {
            break;
        }
        swap(&obj->pos[child], &obj->pos[parent]);
        child = parent;
        parent = child >> 1;
    }
}

// 删除堆顶元素，自上而下。
void pop(Heap* obj)
{
    swap(&obj->pos[1], &obj->pos[obj->heapSize--]);
    int parent = 1;
    int child = parent << 1;

    while (child <= obj->heapSize) {
        if (child + 1 <= obj->heapSize) {
            int valLchild = obj->pos[child].x + obj->pos[child].y;
            int valRchild = obj->pos[child + 1].x + obj->pos[child + 1].y;
            if (obj->cmp(valRchild, valLchild)) {
                child++;
            }
        }
        int valP = obj->pos[parent].x + obj->pos[parent].y;
        int valC = obj->pos[child].x + obj->pos[child].y;
        if (!obj->cmp(valC, valP)) {
            break;
        }
        swap(&obj->pos[child], &obj->pos[parent]);
        parent = child;
        child = parent << 1;
    }
}

typedef struct {
    Heap* heap;
    int maxSize;
} KSmallest;

int getTop(Heap* obj)
{
    return obj->pos[1].x + obj->pos[1].y;
}

int** kSmallestPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int k, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * k);
    memset((*returnColumnSizes), 0, sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    int** res = (int**)malloc(sizeof(int*) * k);
    for (int i = 0; i < k; i++) {
        res[i] = (int*)malloc(sizeof(int) * 2);
        memset(res[i], 0, sizeof(int) * 2);
    }

    KSmallest* obj = (KSmallest*)malloc(sizeof(KSmallest));
    obj->maxSize = k;
    obj->heap = (Heap*)malloc(sizeof(Heap));
    init(obj->heap, k + 1, cmp);
    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums2Size; j++) {
            push(obj->heap, nums1[i], nums2[j]);
            if (obj->heap->heapSize > obj->maxSize) { // 当元素大于需要的k个时，就需要删除了
                pop(obj->heap);
            }
        }
    }

    for (int i = 1; i <= obj->heap->heapSize; i++) {
        res[*returnSize][0] = obj->heap->pos[i].x;
        res[*returnSize][1] = obj->heap->pos[i].y;
        (*returnSize)++;
    }

    return res;
}
```
