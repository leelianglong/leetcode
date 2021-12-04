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

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* obj = (KthLargest*)malloc(sizeof(KthLargest));
    memset(obj, 0, sizeof(KthLargest));
    obj->heap = (int*)malloc(sizeof(struct Heap));
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
