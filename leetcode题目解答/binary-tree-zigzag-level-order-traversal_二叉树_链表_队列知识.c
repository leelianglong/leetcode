#include <stdio.h>
#include <stdlib.h>
/*
给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：
给定二叉树 [3, 9, 20, null, null, 15, 7],

 3
/ \
9  20
   / \
  15  7
返回锯齿形层次遍历如下：

[
    [3],
    [20, 9],
    [15, 7]
]

来源：力扣（LeetCode）
链接：https ://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
构造一个栈结构
*/

#define STACK_LENGTH   100
typedef void(*vist)(int);

typedef struct BTNode {
    int data;
    struct BTNode* lchild;
    struct BTNode* rchild;
} BinaryNode, * BinaryTree;

typedef struct {
    int top;
    BinaryTree data[100];
}Stack;

typedef struct QNode {
    int data;
    struct QNode* next;
}QueueNode,*QueueList;

//下面是队列的结构，队列只允许在对头插入元素，队尾删除。
typedef struct LQ {
    QueueList front, rear;
}LinkQueue;


// 栈相关操作
int InitStack(Stack* para)
{
    int i;
    if (para == NULL) {
        return -1;
    }
    para->top = -1;
    for (i = 0; i < STACK_LENGTH; i++) {
        para->data[i] = NULL;
    }
    return 0;
}

int PushStack(Stack* para, BinaryTree data)
{
    if (para == NULL) {
        return -1;
    }
    if (para->top > STACK_LENGTH - 1) {
        return -1;
    }
    para->top++;
    para->data[para->top] = data;
    return 0;
}

int PopStack(Stack* para, BinaryTree* data)
{
    if (para == NULL) {
        return -1;
    }
    if (para->top < 0) {
        return -1;
    }
    *data = para->data[para->top];
    para->top--;
    return 0;
}

int StackIsEmpty(Stack para)
{   
    return para.top == -1 ? 1 : 0;
}


//二叉树的相关操作
int DestoryBinaryTree(BinaryTree bt)
{
    if (bt) {
        if (bt->lchild) {
            DestoryBinaryTree(bt->lchild);
        }
        if (bt->rchild) {
            DestoryBinaryTree(bt->rchild);
        }
        free(bt);
        bt = NULL;
    }
}

int CreatBinary(BinaryTree* bt)
{
    int data[] = {1,2,4,999,999,5,999,999,3,6,999,999,7,999,999,999,999,999,999,999};
    static int i = 0;
    if (data[i] == 999) {
        *bt = NULL;
        i++;
        return 0;
    }
    (*bt) = (BinaryTree)malloc(sizeof(BinaryNode));
    if (*bt == NULL) {
        return 0;
    }
    (*bt)->data = data[i];
    i++;
    CreatBinary(&(*bt)->lchild);
    CreatBinary(&(*bt)->rchild);
}

// 二叉树为空返回1
int  BinaryTreeIsEmpty(BinaryTree bt)
{
    return bt == NULL ? 1 : 0; 
}

int GetBinaryTreeDeepth(BinaryTree bt)
{
    int i, j;
    if (bt == NULL) {
        return 0;
    }
    if (bt->lchild) {
        i = GetBinaryTreeDeepth(bt->lchild);
    }
    else
    {
        i = 0;
    }

    if (bt->rchild) {
        j = GetBinaryTreeDeepth(bt->rchild);
    }
    else
    {
        j = 0;
    }
    return i > j ? i + 1 : j + 1;
}


void print(int data)
{
    printf("%4d", data);
}

void PreOrderTraverse(BinaryTree bt, vist p)
{
    if (bt) {
        p(bt->data);
        PreOrderTraverse(bt->lchild,p);
        PreOrderTraverse(bt->rchild,p);
    }
}

void MiddleOrderTraverse(BinaryTree bt,vist p)
{
    if (bt) {
        MiddleOrderTraverse(bt->lchild,p);
        p(bt->data);
        MiddleOrderTraverse(bt->rchild,p);
    }
}

void PostOrderTraverse(BinaryTree bt,vist p)
{
    if (bt) {
        PostOrderTraverse(bt->lchild,p);
        PostOrderTraverse(bt->rchild,p);
        p(bt->data);
    }
}

void MiddleOrderByStack(BinaryTree bt)
{
    Stack para = { 0 };
    InitStack(&para);
    while (bt || !StackIsEmpty(para))
    {
        if (bt) {
            PushStack(&para, bt);
            bt = bt->lchild;
        }
        else
        {
            PopStack(&para, &bt);
            printf("%4d", bt->data);
            bt = bt->rchild;
        }
    }
    printf("\n");
}


//队列相关操作
int InitQueue(LinkQueue* lq)
{
    lq->front = lq->rear = (QueueList)malloc(sizeof(QueueNode));
    if (lq->front == NULL) {
        return 0;
    }
    lq->front->next = NULL;
}

void DestoryQueue(LinkQueue* lq)
{
    while (lq->front) {
        lq->rear = lq->front->next;
        free(lq->front);
        lq->front = lq->rear;
    }
}

int QueueIsEmpty(LinkQueue lq)
{
    return lq.rear == lq.front ? 1 : 0;
}

int GetQueueLength(LinkQueue lq)
{
    int i = 0;
    QueueList p = lq.front;
    while (lq.rear != p) {
        i++;
        p = p->next;
    }
    return i;
}

int InsertQueue(LinkQueue* lq, int data)
{
    QueueList p;
    p = (QueueList)malloc(sizeof(QueueNode));
    if (p == NULL) {
        return 0; 
    }
    p->data = data;
    p->next = NULL;
    lq->rear->next = p;
    lq->rear = p;
    return 1;
}

int DelQueue(LinkQueue* lq, int* data)
{
    QueueList p;
    if (lq->rear == lq->front) {
        return 0;
    }
    p = lq->front->next;
    *data = p->data;
    lq->front->next = p->next;
    if (lq->rear == p) {
        lq->rear = lq->front;
    }
    free(p);
    return 1;
}

void VisitQueue(LinkQueue lq)
{
    QueueList p;
    p = lq.front->next;
    while (p)
    {
        printf("%4d", p->data);
        p = p->next;
    }
    printf("\r\n");
}

int main(void)
{

    int i ;
    int ret[10];
    LinkQueue lq = { 0 };

    BinaryTree bt = { 0 };
    CreatBinary(&bt);
    printf("before order");
    PreOrderTraverse(bt,print);
    printf("\r\nmiddle order:");
    MiddleOrderTraverse(bt,print);
    printf("\r\npost order:");
    PostOrderTraverse(bt, print);
    printf("\r\nthe deepth is %d", GetBinaryTreeDeepth(bt));
    printf("\r\nstack visit binary tree:");
    MiddleOrderByStack(bt);

    InitQueue(&lq);
    for (i = 1; i < 7; i++) {
        InsertQueue(&lq, i);
    }
    printf("\r\nvisit queue:\r\n");
    VisitQueue(lq);
}