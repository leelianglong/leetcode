## 概念
1.堆就是使用数组实现完全二叉树。
2.如果完全二叉树的所有子树的最大值在堆顶，就是大根堆。反之是小根堆。

## 实现

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
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
