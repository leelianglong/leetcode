#include <stdio.h>
#include <stdlib.h>

#define TEST_HEAP    printf("\r\n=============================%s=====================\r\n", __FUNCTION__)
#define HEAP_MAX_SIZE  1000
typedef int HeapType;
typedef int (*compare)(HeapType a, HeapType b);
typedef struct __HEAP{
    HeapType data[HEAP_MAX_SIZE];
    int size;
    compare cmp;
} Heap;

int Less (HeapType a, HeapType b)
{
    return a < b;
}

void InitHeap(Heap* hp, compare cmp)
{
    if (hp == NULL || cmp == NULL) {
        return ;
    }
    hp->size = 0;
    hp->cmp = cmp;
    return;
}

void Swap(HeapType* a, HeapType* b) 
{
    HeapType tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void AdjustUp(HeapType* data, int size, compare cmp, int index)
{
    if (index >= size) {
        return;
    }
    // 1、先找到当前节点对应的父节点
    int child = index;
    int parent = (child - 1) / 2;
    while (child > 0) {
        // 2、比较父节点和子节点的大小关系，如果子节点值比父节点小，交换父节点的值。
        if (cmp(data[child], data[parent])) {
            Swap(&data[child], &data[parent]);
        } else {
            break;
        }
        // 3、将当前父节点作为新的子节点，再去找子节点的父节点，循环进行比较和交换
        child = parent;
        parent = (child - 1) / 2;
    }
    return;
}

void InsertHeap(Heap* hp, HeapType value)
{
    if (hp == NULL) {
        return;
    }
    if (hp->size >= HEAP_MAX_SIZE) {
        return; 
    }
    hp->data[hp->size++] = value;
    AdjustUp(hp->data, hp->size, hp->cmp, hp->size - 1);
    return;
}

void GetHeapTop(Heap* hp, HeapType* value)
{
    if (hp == NULL) {
        return;
    }
    *value = hp->data[0];
    return;
}

void AdjustDown(HeapType* data, int size, compare cmp, int index)
{
    // 1、设定parent指向开始的位置，找到对应的子树节点
    int parent = index;
    // 2、设定一个child指向parent的左子树
    int child = parent * 2 + 1;
    // 3、判断child和child + 1的大小关系，如果child + 1的值比child的小，就让child = child + 1
    while (child < size) {
        if (child + 1 < size && cmp(data[child + 1], data[child])) {
            child = child + 1;
        }
        // 4、判断child和parent的大小关系
        if (cmp(data[child], data[parent])) {
            Swap(&data[child], &data[parent]);
        } else {
            break; // 说明调整已经完成
        }
        parent = child;
        child = parent * 2 + 1;
    }
}

void DeleteHeapTopData(Heap* hp)
{
    if (hp == NULL) {
        return;
    }
    if (hp->size == 0) {
        return;
    }
    Swap(&hp->data[0], &hp->data[hp->size - 1]);
    --hp->size;
    AdjustDown(hp->data, hp->size, hp->cmp, 0);
}

int IsHeapEmpty(Heap* hp)
{
    if (hp == NULL) {
        return 0;
    }
    return hp->size == 0 ? 1 : 0;
}

int GetHeapSize(Heap* hp)
{
    if (hp == NULL) {
        return 0;
    }
    return hp->size;
}

void DestroyHeap(Heap* hp)
{
    if (hp == NULL) {
        return;
    }
    hp->size = 0;
    return;
}

// 需要开辟额外空间的堆排序
void HeapSort1(HeapType* data, int size)
{
    Heap hp = {0};
    InitHeap(&hp, Less); // 初始化小顶堆
    // 1、先将数组里的元素插入到一个堆里面
    int i = 0;
    for (i = 0; i < size; i++) {
        InsertHeap(&hp, data[i]);
    }
    // 2、然后依次获取堆顶元素，放回原数组，并删除堆顶元素
    int outIndex = 0;
    while (IsHeapEmpty(&hp) != 1) {
        HeapType root = 0;
        GetHeapTop(&hp, &root);
        data[outIndex] = root;
        ++outIndex;
        DeleteHeapTopData(&hp);
    }
}

// 不需要开辟额外空间的堆排序
void HeapSort2(HeapType* data, int size, compare cmp)
{
    if (size == 0 || size == 1) {
        return ;
    }
    // 1、将数组的所有元素放在一个堆里，循环结束之后，就调整一个小堆
    int i = 0;
    for (i = 0; i < size; i++) {
        AdjustUp(data, i, cmp, i);
    }
    // 2、依次去堆顶元素
    while (i > 0) {
        Swap(&data[0], &data[i - 1]);
        --i;
        AdjustDown(data, i, cmp, 0);
    }
}

void HeapPrintChar(Heap* hp, const char* msg)
{
    printf("\r\n%s\r\n", msg);
    int i = 0;
    for (; i < hp->size; i++) {
        printf("[%lu]: %4d", i, hp->data[i]);
    }
    printf("\n");
}

void TestInit(void)
{
    TEST_HEAP;
    Heap hp = {0};
    InitHeap(&hp, Less);
    printf("\r\nheap->size expect 0,actual %lu\r\n", hp.size);
    printf("\r\nheap->cmp expect is %p,actual %p\r\n", Less, hp.cmp);
}

void TestInsert(void)
{
    TEST_HEAP;
    Heap hp;
    InitHeap(&hp,Less);
    InsertHeap(&hp, 10);
    InsertHeap(&hp, 12);
    InsertHeap(&hp, 16);
    InsertHeap(&hp, 8);
    InsertHeap(&hp, 4);
    InsertHeap(&hp, 2);
    HeapPrintChar(&hp, "insert 6 elements");
}

void TestRoot(void)
{
    TEST_HEAP;
    Heap hp;
    InitHeap(&hp,Less);
    InsertHeap(&hp, 10);
    InsertHeap(&hp, 12);
    InsertHeap(&hp, 16);
    InsertHeap(&hp, 8);
    InsertHeap(&hp, 4);
    InsertHeap(&hp, 2);
    HeapType value;
    GetHeapTop(&hp, &value);
    printf("\r\nroot element expect 2,actual is %4d\r\n", value);
}

void TestErase(void)
{
    TEST_HEAP;
    Heap hp;
    InitHeap(&hp,Less);
    InsertHeap(&hp, 10);
    InsertHeap(&hp, 12);
    InsertHeap(&hp, 16);
    InsertHeap(&hp, 8);
    InsertHeap(&hp, 4);
    InsertHeap(&hp, 2);
    DeleteHeapTopData(&hp);

    HeapPrintChar(&hp, "delete one element");
}

void TestSort(void)
{
    TEST_HEAP;
    int data[] = {0,1,4,2,54,32};
    HeapSort2(data, sizeof(data)/sizeof(data[0]), Less);
    int i = 0;
    for (; i < sizeof(data)/sizeof(data[0]); i++) {
        printf("%4d", data[i]);
    }
    printf("\n");
}


int main(void)
{
    TestInit();
    TestInsert();
    TestRoot();
    TestErase();
    TestSort();
    system("pause");
}