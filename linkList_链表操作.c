#include <stdio.h>
#include <stdlib.h>

struct ListNode {
      int val;
      struct ListNode *next;
 };
 
typedef struct ListNode* LinkList;

int InitLink(LinkList* list)
{
    *list = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (list == NULL) {
        return NULL;
    }
    (*list)->next = NULL;
    (*list)->val = 0;
    return 1;
}

int GetListLength(LinkList head)
{
    int i = 0;
    LinkList tmp = head->next;
    while (tmp) {
        i++;
        tmp = tmp->next;
    }
    return i;
}
//在带头节点的单链表的第i个节点之前插入元素data
int InsertNode(LinkList list, int i, int data)
{
    int j = 0;
    LinkList tmp = list, s; //这样操作保证list的head没有变化。
    while (tmp && j < i - 1) {
        tmp = tmp->next;
        j++;
    }
    if (!tmp || j > i - 1) {
        return 0;
    }
    s = (LinkList)malloc(sizeof(struct ListNode));
    if (s == NULL) {
        return 0;
    }
    s->val = data;
    s->next = NULL;
#if 0
    s->next = tmp->next;
    tmp->next = s;
#endif
    tmp->next = s;
    tmp = tmp->next;
    return 1;
}

//创建链表时注意头插法和尾插法，一般使用尾插法，链表头就是第一次插入的数据
void CreateLink(LinkList* list)
{
    int i;
    LinkList p, q;
    (*list) = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (*list == NULL) {
        return ;
    }
    (*list)->next = NULL;
    (*list)->val = 0;
    q = (*list);
    for (i = 1; i <= 1; i++) {
        p = (LinkList)malloc(sizeof(struct ListNode));
        if (p == NULL) {
            return ;
        }
        p->val = i; 
        q->next = p; // 这里是尾插法，尾插法的元素是按照插入的顺序来展示的。头插法则是倒着插的。
        q = q->next;
    }
    p->next = NULL;
}

void VisitLink(LinkList list)
{
    LinkList tmp = list;
    while (tmp) {
        printf("%4d", tmp->val);
        tmp = tmp->next;
    }
    return 1;
}
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* fake = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (fake == NULL) {
        return NULL;
    }
    fake->next = head;
    struct ListNode* q = NULL;
    int counter = 0;
    int i;
    struct ListNode* tmp = head;
    while (tmp) {
        counter++; //这个counter就是正正链表的长度
        tmp = tmp->next;
    }
    tmp = fake;
    for (i = 0; i < counter - n; i++) {
        tmp = tmp->next;
    }
    q = tmp->next;
    tmp->next = q->next;
    return fake->next;
}

int main(void)
{
    LinkList list = NULL;
    LinkList delList = NULL;
    LinkList tmp = NULL;
    int result = 0;
    int j;
#if 0
    result = InitLink(&list);
    if (!result) {
        return 0;
    }
    for (j = 1; j < 6; j++) {
        InsertNode(list, 1, j);
    }
    VisitLink(list);
#endif
    CreateLink(&list);
    VisitLink(list);
    tmp = list->next;
    delList = removeNthFromEnd(tmp, 1);
    printf("\r\ndelete elements:\r\n");
    VisitLink(delList);
}