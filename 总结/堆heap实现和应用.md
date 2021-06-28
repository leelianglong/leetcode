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
