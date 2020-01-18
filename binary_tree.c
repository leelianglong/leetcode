#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/****************** 二叉树结构定义 ****************/
typedef struct BTNode {
    int data;
    struct BTNode* lchild;
    struct BTNode* rchild;
} BinaryNode, *BinaryTree;
/****************** 二叉树结构定义 ****************/

/****************** 栈的结构定义 *****************/
#define  STATCK_LENGTH           1000
typedef struct {
    int top;
    BinaryTree* data; /* 这里需要使用二叉树指针的指针 */
} Stack;
/****************** 栈的结构定义 *****************/

/****************** 队列结构定义 *****************/
typedef struct QNode {
    BinaryTree* data;
    struct QNode* next;
} QueueNode,*QueueList;

typedef struct LQ {
    QueueList front, rear; // 对头插入，队尾删除
} LinkQueue;
/****************** 队列结构定义 *****************/

/***************************************栈基本操作**************************************/
bool InitStack(Stack* para)
{
    if (para == NULL) {
        return false;
    }
    para->data = (BinaryTree*)malloc(STATCK_LENGTH * sizeof(BinaryTree));
    if (para->data == NULL) {
        return false;
    }
    memset(para->data, 0, STATCK_LENGTH * sizeof(BinaryTree));
    para->top = -1;
    return true;
}

/*
下面实现的栈是向上增长：
一开始top在最底段，每次入栈，top先增加，把元素放到栈顶。
出栈时，先从栈顶拿出元素，然后栈顶指针top再减减。
*/
bool PushStack(Stack* para, BinaryTree data)
{
    if (para == NULL) {
        return false;
    }
    if (para->top > STATCK_LENGTH - 1) {
        return false;
    }
    para->data[++para->top] = data;
    return true;
}

bool PopStack(Stack* para, BinaryTree* data)
{
    if (para == NULL) {
        return false;
    }
    if (para->top < 0) {
        return false;
    }
    *data = para->data[para->top--];
    return true;
}

bool CheckStackIsEmpty(Stack* para)
{
    return para->top == -1 ? true : false;
}
/***************************************栈基本操作**************************************/

/**************************************队列基本操作**************************************/
bool InitQueue(LinkQueue* lq)
{
    lq->front = lq->rear = (QueueList)malloc(sizeof(QueueNode));
    if (lq->front == NULL) {
        return false;
    }
    lq->front->next = NULL;
    return true;
}

void DestoryQueue(LinkQueue* lq)
{
    while (lq->front) {
        lq->rear = lq->front->next;
        free(lq->front);
        lq->front = lq->rear;
    }
}

bool QueueIsEmpty(LinkQueue lq)
{
    return lq.rear == lq.front ? true : false;
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

bool InsertQueue(LinkQueue* lq, BinaryTree data)
{
    QueueList p;
    p = (QueueList)malloc(sizeof(QueueNode));
    if (p == NULL) {
        return false; 
    }
    p->data = data;
    p->next = NULL;
    lq->rear->next = p; //起初队尾节点的下一个是null，这里新创建一个节点就接上。
    lq->rear = p; //新创建的节点变成队尾。
    return true;
}

bool DelQueue(LinkQueue* lq, BinaryTree* data)
{
    QueueList p;
    if (lq->rear == lq->front) {
        return false;
    }
    p = lq->front->next;
    *data = p->data;
    lq->front->next = p->next;
    if (lq->rear == p) {
        lq->rear = lq->front;
    }
    free(p);
    return true;
}
/**************************************队列基本操作**************************************/




/* 
创建二二叉树：
这种是以前序方式来创建二叉树，在构造数据时，一定要把叶子节点的左子树和右子树都设置成结束符。
才能按照预期生成二叉树。就是把二叉树构造成满二叉树，所有的叶子阶段的都是 结束符。
注意：递归调用也是函数每次重入一次，该函数中的局部变量也会在重入的时候消失，如果需要在整个
函数退出之前都需要保持的变量，要设置成全局变量，或者静态局部变量，或者使用指针传入。
当前函数在多次调用时，要记得把counter清零。
*/
void CreatBinary(BinaryTree* bt, int* data, int* counter)
{
    if (data[(*counter)] == 999) {
        *bt = NULL;
        (*counter)++;
        return;
    }
    (*bt) = (BinaryTree)malloc(sizeof(BinaryNode));
    if (*bt == NULL) {
        return;
    }
    (*bt)->data = data[(*counter)];
    (*counter)++;
    CreatBinary(&(*bt)->lchild, data, counter);
    CreatBinary(&(*bt)->rchild, data, counter);
}

/*
二叉树销毁
*/
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

/*
二叉树判空
*/
bool BinaryTreeIsEmpety(BinaryTree bt)
{
    return bt == NULL ? true : false;
}

/*
获取二叉树的深度(递归方案)
*/
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

/*
获取树深度的另一种简单递归版本写法,先计算左子树的深度，再计算右子树的深度，然后取其中较大的，最后
再加上根节点的深度1，就是整个二叉树的深度
*/
int dfs_deepth(BinaryTree bt) 
{
    if (bt == NULL) {
        return 0;
    }
    int leftDeepth = dfs_deepth(bt->lchild) + 1;
    int rightDeepth = dfs_deepth(bt->rchild) + 1;
    return (leftDeepth > rightDeepth ? leftDeepth : rightDeepth);
}

int GetBinaryTreeDeepthV1(BinaryTree bt)
{
    if (bt == NULL) {
        return 0;
    }
    return dfs_deepth(bt);
}

/*
统计叶子节点的个数
*/
int dfs_leaf_count(BinaryTree bt, int* counter)
{
    if (bt == NULL) {
        return 0;
    }
    if (bt->lchild == NULL && bt->rchild == NULL) {
        return (*counter)++;
    }
    if (bt->lchild) {
        dfs_leaf_count(bt->lchild, counter);
    }
    if (bt->rchild) {
        dfs_leaf_count(bt->rchild, counter);
    }
}

int GetLeafCounter(BinaryTree bt) {
    static int counter = 0;
    if (bt == NULL) {
        return 0;
    }
    dfs_leaf_count(bt, &counter);
    return counter;
}

/*
统计二叉树所有节点个数
*/
int GetNodeCounter(BinaryTree bt)
{
    int leftHigh = 0;
    int rightHigh = 0;
    BinaryTree left = bt;
    BinaryTree right = bt;
    if (bt == NULL) {
        return 0;
    }
    while (left) {
        left = left->lchild;
        leftHigh++;
    }

    while (right) {
        right = right->rchild;
        rightHigh++;
    }

    if (leftHigh == rightHigh) {
        return (int)(1 << rightHigh) - 1; // 左右子树一样高，是满二叉树，节点个数 = 2^n - 1;
    } 
    return 1 + GetNodeCounter(bt->lchild) + GetNodeCounter(bt->rchild);
}

/*
前序遍历，递归版本
*/
void PreOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    saveData[(*counter)++] = bt->data;   
    PreOrderTraverse(bt->lchild, saveData, counter);
    PreOrderTraverse(bt->rchild, saveData, counter);
}

/*
二叉树的前序遍历(非递归版本，栈实现)，先把栈顶元素入栈，然后出栈，再把右子树入栈，再把左子树入栈，然后再出栈，一直循环到栈为空。
*/
int* PreOrderTraverseByStack(BinaryTree bt, int* counter)
{
    Stack binaryTree = {0};
    int* saveData = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (saveData == NULL) {
        return NULL;
    }
    memset(saveData, 0, STATCK_LENGTH * sizeof(int));
    InitStack(&binaryTree);
    PushStack(&binaryTree, bt);

    while (!CheckStackIsEmpty(&binaryTree)) {
        PopStack(&binaryTree, &bt);
        saveData[(*counter)++] = bt->data;
        if (bt->rchild) {
            PushStack(&binaryTree, bt->rchild);
        }
        if (bt->lchild) {
            PushStack(&binaryTree, bt->lchild);
        }
    }
    return saveData;
}

/*
二叉树的中序遍历(递归版本)
*/
void MiddleOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    MiddleOrderTraverse(bt->lchild, saveData, counter);
    saveData[(*counter)++] = bt->data;
    MiddleOrderTraverse(bt->rchild, saveData, counter);
}

/**
 * 中序非递归遍历，（左子树，根节点，右子树），要首先找到左子树的左叶子节点，所以要把所有左子树入栈，等所有的左子树入栈后，取栈顶元素，
 * 遍历右子树
 * */
int* MiddleOrderTraverseByStack(BinaryTree bt, int* counter)
{
    Stack binaryTree = {0};
    int* saveData = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (saveData == NULL) {
        return NULL;
    }
    memset(saveData, 0, STATCK_LENGTH * sizeof(int));
    InitStack(&binaryTree);
    while (bt != NULL || binaryTree.top != -1) {
        while (bt != NULL) { // 先把左子树全部入栈
            PushStack(&binaryTree, bt);
            bt = bt->lchild;
        }
        if (binaryTree.top != -1) { // 左子树入栈结束后，取栈顶元素，输出栈顶元素，遍历右子树
            PopStack(&binaryTree, &bt);
            saveData[(*counter)++] = bt->data;
            bt = bt->rchild;
        }
    }
    return saveData;
}

/*
二叉树的后序遍历(递归版本)
*/
void PostOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    PostOrderTraverse(bt->lchild, saveData, counter);
    PostOrderTraverse(bt->rchild, saveData, counter);
    saveData[(*counter)++] = bt->data;
}

/*******************************************************************************
思路：
1、在进行后序遍历的时候是先要遍历左子树，然后在遍历右子树，最后才遍历根节点。所以在非递归的实现中要先把根节点入栈
2、再把左子树入栈直到左子树为空，此时停止入栈。此时栈顶就是需要访问的元素，所以直接取出访问p。在访问结束后，还要判断被访
   问的节点p是否为栈顶节点的左子树
3、如果是的话那么还需要访问栈顶节点的右子树，所以将栈顶节点的右子树取出赋值给p
4、如果不是的话则说明栈顶节点的右子树已经访问完了，那么现在可以访问栈顶节点了，所以此时将p赋值为null
*******************************************************************************/
int* PostOrderTraversByStack(BinaryTree bt, int* counter)
{
    Stack binaryTree = {0};
    BinaryTree haveAccess = NULL; // 用来标记右子树是否访问到了，在访问到的情况下，才能访问根节点。
    int* saveData = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (saveData == NULL) {
        return NULL;
    }
    memset(saveData, 0, STATCK_LENGTH * sizeof(int));
    InitStack(&binaryTree);
    while (bt != NULL || binaryTree.top != -1)
    {
        while (bt != NULL) { // 遍历完所有左子树
            PushStack(&binaryTree, bt);
            bt = bt->lchild;
        }
        PopStack(&binaryTree, &bt);
        if (bt->rchild == NULL || haveAccess == bt->rchild) {
            saveData[(*counter)++] = bt->data;
            haveAccess = bt;
            bt = NULL;
        } else {
            PushStack(&binaryTree, bt); //在回到根节点时，再次把根节点入栈
            bt = bt->rchild;
        }
    }
    return saveData;
}


/*
二叉树的层次遍历
*/
int* LevelTraverse(BinaryTree bt, int* counter)
{
    int* res = (int*)malloc(STATCK_LENGTH * sizeof(int));
    if (res == NULL) {
        return NULL;
    }
    LinkQueue lq = {0};
    InitQueue(&lq);
    InsertQueue(&lq, bt);
    while (GetQueueLength(lq)) {
        DelQueue(&lq, &bt);
        res[(*counter)++] = bt->data;
        if (bt->lchild) {
            InsertQueue(&lq, bt->lchild);
        }
        if (bt->rchild) {
            InsertQueue(&lq, bt->rchild);
        }
    }
    return res;
}

int main(void)
{
    int data[] = {1,2,4,999,999,5,999,999,3,6,999,999,7,999,999,999,999,999,999,999}; // 使用这种方法创建二叉树，需要在最后一个节点数据后面右足够的999.
    int counter = 0;
    int i;
    int saveData[10] = {0};
    BinaryTree root = NULL;
    int accessCounter = 0;
    int* result = NULL;

    CreatBinary(&root, data, &counter);
    PreOrderTraverse(root, saveData, &accessCounter);
    printf("\r\n前序遍历：递归\r\n");
    for(i = 0; i < accessCounter; i++) {
        printf("%4d", saveData[i]);
    }
    int deepth = GetBinaryTreeDeepth(root);
    int leafCount = GetLeafCounter(root);
    accessCounter = 0;
    result = PostOrderTraversByStack(root, &accessCounter);
    printf("\r\n前序遍历：非递归\r\n");
    for (i = 0; i < accessCounter; ++i) {
        printf("%4d", result[i]);
    }
    counter = GetNodeCounter(root);
    printf("\r\nnode is %u\r\n", counter);

    printf("\r\nlevel traverse\r\n");
    counter = 0;
    result = LevelTraverse(root, &counter);
    for (i = 0; i < counter; ++i) {
        printf("%4d", result[i]);
    }
    system("pause");
}
