#include <stdio.h>
#include <stdlib.h>

/*
* 堆的基本概念：
* 1、堆底插入元素，堆顶删除元素；
* 2、堆中的元素不是按照先来后到的顺序排列的，而是按照规则，大顶堆的规则是大的元素在前面，小的元素在后面
*    小顶堆刚好相反，小的元素在前面，大的元素在后面。
* 3、堆的逻辑结构实际上是一个完全二叉树。
* 堆的存储：
* 堆中的元素有优先级先后顺序，可以使用数组来存储，方便快速访问每个节点。堆的数组表示实际上就是堆的层级遍历结果。
* 对于每一个小标为i的元素，其左子节点的下标是 2*i, 右子节点的下标是2*i + 1, 其父节点是 i/2;
* 这里的i从1开始。
*/

#define INIT_VALUE -1
typedef struct __heap {
    int capacity; 
    int index;  /* 表示当前堆中的元素个数 */
    int* data;
} Heap;


/* 创建一个空堆: 参数表示堆中的元素个数 */
Heap* CreateHeap(int max) 
{
    int i;
    Heap* tmp = (Heap*)malloc(sizeof(Heap));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->capacity = max;
    tmp->index = 0;
    tmp->data = (int* )malloc((tmp->capacity + 1) * sizeof(int));
    if (tmp->data == NULL) {
        free(tmp);
        return NULL;
    }
    tmp->data[0] = INIT_VALUE; /* 堆顶初始设置成-1 */
    return tmp;
}

int IsHeapFull(Heap* tmp)
{
    return (tmp->capacity == tmp->index);
}
/*
* 堆的插入操作：
* 1、将新元素加到堆的末尾
* 2、按照优先顺序，将新元素与其父节点比较，如果新元素小于父节点则将两者交换位置
* 3、不断进行第2步操作，直到不需要交换新元素和父节点，或者达到堆顶
*/
Heap* InsertHeap(Heap* tmp, int data)
{
    int tmpData;
    if(IsHeapFull(tmp)) {
        return tmp;
    }
    int i;
    for (i = ++tmp->index; tmp->data[i] > data; i /= 2) {
        tmp->data[i] = tmp->data[i/2];
    }
    tmp->data[i] = data;

    if (data < tmp->data[i/2]) {
        tmpData = data;
        data = tmp->data[i/2];
        tmp->data[i/2] = tmpData;
    }
    return tmp;
}

int IsHeapEmpty(Heap* tmp) 
{
    return (tmp->index == 0);
}

/*
* 堆的删除操作：
* 1、删除堆顶元素（通常是将堆顶元素放置在数组的末尾）
* 2、比较左右子节点，将小的元素上调
* 3、不断进行步骤2，直到不需要调整或者调整到堆底
*/
Heap* DeleteMin (Heap* heap) {

    if (IsHeapEmpty(heap)) {
        printf("empty heap!\n");
        return NULL;
    }

    int minElement = heap->data[1]; //堆顶元素最小
    int lastElement = heap->data[heap->index--];

    int i, childIndex;
    for (i = 1; 2*i <= heap->index; i = childIndex)
    {
        childIndex = 2*i;

        //get the bigger child node
        if (heap->data[childIndex] != heap->index 
         && heap->data[childIndex] > heap->data[childIndex+1])
            childIndex++;

        if (lastElement > heap->data[childIndex])
            heap->data[i] = heap->data[childIndex];
        else
            break;
    }
    heap->data[i] = lastElement;

    return heap;
}

/**************************************************************************************/
typedef struct {
    int s[20000];
    int k;
    int index;
} KthLargest;

void minHeap(KthLargest* obj, int num) {
    //已存在k个数，且小顶堆的堆顶元素 大于等于 新元素，则不进行处理.因为是小堆，堆顶的元素最小，
    // 最小的元素都大于新元素，说明新的元素在现有堆中没有位置了。所以不用处理。

    int flag;
    if (obj->k == obj->index + 1 && obj->s[0] >= num) { //这里+1，因为堆元素从1开始。
        return;
    } else if (obj->k == obj->index + 1 && obj->s[0] < num) {
        flag = 1;
        obj->s[0] = num; // 把新元素放在堆顶？
    } else {
        flag = 2;
        obj->s[++obj->index] = num; // 没有存在k个元素时，把新元素放在堆尾部。
    }

    //第一个数不需要进行最小堆堆化处理
    if (obj->index == 0) {
        return;
    }

    //heapify
    int i,temp;
    if (flag == 2) {
        i = obj->index; // 对目前所有的元素进行堆化处理。
        while ((i - 1) / 2 >= 0) { // 堆顶元素还没有到达第1个元素。
            temp = (i - 1) / 2;
            if (obj->s[temp] > obj->s[i]) { //堆顶元素大于第i个元素
                int data = obj->s[temp];
                obj->s[temp] = obj->s[i];
                obj->s[i] = data;
                i = (i - 1) / 2;
            } else {
                break;
            }
        }
    } else {
        i = 0;
        while (1) {
            int left = i * 2 + 1;
            int right = i * 2 + 2;  // 是左右子节点
            temp = i; //tmp是堆顶
            if (left <= obj->index && obj->s[temp] > obj->s[left]) {
                temp = left; //堆顶点往左节点下沉
            }
            if (right <= obj->index && obj->s[temp] > obj->s[right]) {
                temp = right; //堆顶点往右节点下沉
            }
            if (temp == i) {
                break;
            }
            int data = obj->s[temp];
            obj->s[temp] = obj->s[i];
            obj->s[i] = data; // 顶点与第i个节点交换

            i = temp;
        }
    }
}

KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest *kL = (KthLargest *)malloc(sizeof(KthLargest));
    kL->k = k;
    kL->index = -1;

    int i;
    for (i = 0; i < numsSize; i++) {
        minHeap(kL, nums[i]);
    }
    return kL;
}

int kthLargestAdd(KthLargest* obj, int val) {
    minHeap(obj, val);
    return obj->s[0];
}

void kthLargestFree(KthLargest* obj) {
    obj->index = -1;
}

/*******************************************************************************************/


int main(void)
{
    int max = 10;
    int i;
    int k = 3;
    int data[] = {4,5,8,2};
    KthLargest* exam = NULL;
    Heap* test =  CreateHeap(max);
    int result;

    for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        test = InsertHeap(test, data[i]);
    }
    test = InsertHeap(test, 25);
   // test = DeleteMin(test);
    //test = DeleteMin(test);
    //test = DeleteMin(test);
    for (i = 1; i <= test->index; i++) {
        printf("%4d", test->data[i]);
    }
    exam = kthLargestCreate(k, data, 4);
    result = kthLargestAdd(exam, 3);
    printf("\r\n %4d\r\n", result);
    result = kthLargestAdd(exam, 5);
    printf("\r\n %4d\r\n", result);
    result = kthLargestAdd(exam, 10);
    printf("\r\n %4d\r\n", result);
    result = kthLargestAdd(exam, 9);
    printf("\r\n %4d\r\n", result);
    result = kthLargestAdd(exam, 4);
    printf("\r\n %4d\r\n", result);
    system("pause");
}