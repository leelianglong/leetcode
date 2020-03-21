#include <stdio.h>
#include <stdlib.h>

/*
* 单链表的循环链表最后一个节点不是指向空 而是指向头节点
*/

typedef int ElementType;
typedef struct __LINK_NODE {
    ElementType data;
    struct __LINK_NODE* next;
} LinkNode, *LinkList;

/*初始化循环链表*/
int InitCycleList(LinkList* ll)
{
    (*ll) = (LinkList)malloc(sizeof(LinkNode));
    if (*ll == NULL) {
        return 0;
    }
    (*ll)->next = *ll; //指针域指向头节点
    return 1;
}

int DestoryCycleList(LinkList* ll)
{
    LinkList q, p = (*ll)->next; // p指向头节点
    while (p != *ll) {
        q = p->next;
        free(p);
        p = q;
    }
    free(*ll);
    (*ll)->next = NULL;
    return 1;
}

int ClearCycleList(LinkList* ll)
{
    LinkList p, q;
    (*ll) = (*ll)->next; // L 指向头节点
    p = (*ll)->next; // p 指向第一个节点
    while (p != *ll) {
        q = p->next;
        free(p);
        p = q;
    }
    (*ll)->next = *ll; // 头节点指针域指向自身
    return 1;
}

int IsCycleListEmpty(LinkList ll) 
{
    return ll->next == ll ? 1 : 0; //头尾一样说明空了
}

int GetCycleListLength(LinkList ll)
{
    int i = 0;
    LinkList p = ll->next;
    while(p != ll) {
        i++;
        p = p->next;
    }
    return i;
}

// 在循环队列的第i个元素前插入元素data
int InsertCycleList(LinkList* ll, int i, ElementType data)
{
    LinkList p = (*ll)->next; // p指向头节点
    LinkList s;
    int j = 0;

    if (i <= 0 || i > GetCycleListLength(*ll) + 1) {
        return 0; // 不能在第i个元素之前插入
    }
    while(j < i - 1) {
        p = p->next;
        j++;
    }
    s = (LinkList)malloc(sizeof(LinkNode));
    s->data = data;
    s->next = p->next;
    p->next = s;
    if (p == *ll) {
        *ll = s;
    }
    return 1;
}

//删除循环链表L的第i个元素
int DeletecycleList(LinkList* ll, int i, ElementType* data)
{
    LinkList p = (*ll)->next; // p指向头节点
    LinkList q;
    int j = 0;

    if (i <= 0 || i > GetCycleListLength(*ll)) {
        return 0;
    }

    while (j < i - 1) {
        p = p->next;
        j++;
    }
    q = p->next;
    p->next = q->next;
    *data = q->data;
    if (*ll == q) {
        *ll = p;
    }
    free(q);
    return 1;
}

int PrintCycleList(LinkList ll) 
{
    LinkList p = ll->next->next;
    while (p != ll->next) { //因为是循环链表，使P从链表头的下一个开始遍历，直到和链表头相等时则结束
        printf("%4d", p->data);
        p = p->next;
    }
}

int main(void)
{
    LinkList ll;
    ElementType data;
    int j;
    int status = 0;
    status = InitCycleList(&ll);
    printf("初始化链表ll status=%d (1:成功； 0:失败）\r\n", status);
    status = IsCycleListEmpty(ll);
    printf("链表ll是否空 status=%d(1: 空； 0 : 非空)\r\n", status);
    for (j = 1; j <= 10; j++) {
        InsertCycleList(&ll, j, rand() % 100);
    }
    status = GetCycleListLength(ll);
    printf("LL中的数据元素有 %d 个\r\n", status);
    PrintCycleList(ll);
    printf("\n");
    status = DeletecycleList(&ll, 2, &data);
    printf("删除的第2个元素是%d\r\n", data);
    printf("剩余的链表元素是：");
    PrintCycleList(ll);
}