#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct LL{
    int value;
    struct LL* next;
} LinkNode, *LinkList;

// 初始化一个无用的头结点
bool InitLinklist(LinkList* ll) 
{
    *ll = (LinkList)malloc(sizeof(LinkNode));
    if (*ll == NULL) {
        return false;
    }
    (*ll)->next = NULL;
    (*ll)->value = INT_MIN;
    return true;
}

bool InsertNode(LinkList list, int data, int index)
{
    int j = 0;
    printf("\r\n %2d %2d\r\n", data, index);
    LinkList tmp = list, s; //这样操作保证list的head没有变化。
    while (tmp && j < index) {
        tmp = tmp->next;
        j++;
    }
    s = (LinkList)malloc(sizeof(LinkNode));
    if (s == NULL) {
        return false;
    }
    s->value = data;
    if (tmp->next == NULL) {
        s->next = NULL;
        tmp->next = s;
        tmp = tmp->next;
    } else {
        LinkList p = tmp->next; // 这里是把元素插在链表的中间某个位置。
        tmp->next = s;
        s->next = p;
    }
    return true;
}


int* createTargetArray(int* nums, int numsSize, int* index, int indexSize, int* returnSize){
    if (nums == NULL || index == NULL || returnSize == NULL) {
        return NULL;
    }
    LinkList ll = NULL;
    InitLinklist(&ll);
    int i;
    for (i = 0; i < numsSize;i++) {
        InsertNode(ll, nums[i], index[i]);
    }
    int* res = (int*)malloc(sizeof(int) * numsSize);
    memset(res, 0, sizeof(int) * numsSize);
    int counter = 0;
    printf("\r\nvalue:\r\n");
    while(ll->next != NULL) {
        ll = ll->next;
        res[counter++] = ll->value;
        printf("%2d", ll->value);
    }
    *returnSize = counter;
    return res;
}




int main()
{
    int nums[] = {1,2,3,4,0};
    int index[] = {0,1,2,3,0};
    int returnSize = 0;
    int* res = createTargetArray(nums, sizeof(nums) / sizeof(nums[0]), index, sizeof(index) / sizeof(index[0]), &returnSize);
    system("pause");
}