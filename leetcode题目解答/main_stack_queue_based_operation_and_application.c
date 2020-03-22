#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW_COLUM 100

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryLink;

#if 0
typedef struct BTNode{
	int val;
	struct BTNode* left;
	struct BTNode* right;
} BinaryTreeNode,*BinaryLink;
#endif

typedef BinaryLink QElement;
typedef struct QNode
{
    QElement data;
    struct QNode *next;
} Queue;
typedef struct
{
    Queue *front;
    Queue *rear;
} QueueLink;

typedef BinaryLink StackElement;
typedef struct STNode
{
    int top;
    StackElement data[MAX_ROW_COLUM];
} StackNode, *LinkStack;

/*使用递归法创建二叉树 */
int CreateBinaryTree(BinaryLink *bt)
{
    //int data[] = {1, 2, 4, 999, 999, 999, 3, 999, 5, 999, 999, 999, 999, 999, 999}; // 1,2,3,4,nu,nu,5
	int data[] = {3,9,999,999,20,15,999,999,7,999,999,999,999,999,999};
    static int i = 0;
    if (data[i] == 999)
    {
        i++;
        *bt = NULL;
        return 0;
    }
    if (bt == NULL)
    {
        printf("bt is null");
        return 0;
    }
    (*bt) = (BinaryLink)malloc(sizeof(BinaryTreeNode));
    if (*bt == NULL)
    {
        printf("malloc fail");
        return 0;
    }
    (*bt)->val = data[i];
    i++;
    CreateBinaryTree(&(*bt)->left);
    CreateBinaryTree(&(*bt)->right);
    return 1;
}

/* 递归法遍历二叉树 */
void PreVisit(BinaryLink bt)
{
    if (bt)
    {
        printf("%4d", bt->val);
        PreVisit(bt->left);
        PreVisit(bt->right);
    }
}

/*************************下面队列的相关操作************************/
int InitQueue(QueueLink *ql)
{
    if (ql == NULL)
    {
        return 0;
    }
    (*ql).rear = (*ql).front = (Queue *)malloc(sizeof(Queue));
    if ((*ql).front == NULL)
    {
        return 0;
    }
    (*ql).front->next = NULL;
    return 1;
}

/* 从队头开始删除 */
int DestoryQueue(QueueLink *ql)
{
    while ((*ql).front)
    {
        (*ql).rear = (*ql).front->next;
        free((*ql).front);
        (*ql).front = (*ql).rear;
    }
    return 1;
}

int ClearQueue(QueueLink *ql)
{
    Queue *p, *q;

    (*ql).rear = (*ql).front;
    p = (*ql).front->next;
    (*ql).front->next = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    return 1;
}

int CheckQueue(QueueLink ql)
{
    return (ql.front == ql.rear) ? 1 : 0;
}

int GetQueueLength(QueueLink ql)
{
    int i = 0;
    Queue *p = NULL;

    p = ql.front;
    while (ql.rear != p)
    {
        i++;
        p = p->next;
    }
    return i;
}

/*队尾插入,队尾的下一个指针指向NULL*/
int InsertQueueNode(QueueLink *ql, QElement data)
{
    Queue *p;

    p = (Queue *)malloc(sizeof(Queue));
    if (p == NULL)
    {
        return 0;
    }
    p->data = data;
    p->next = NULL; /* 队尾的下一个指针指向NULL */
    (*ql).rear->next = p;
    (*ql).rear = p;
    return 1;
}

/* 删除结点是从队头删除 */
int DeleteQueueNode(QueueLink *ql, QElement *data)
{
    Queue *p;
    if ((*ql).front == (*ql).rear)
    {
        return 0;
    }
    p = (*ql).front->next;
    *data = p->data;
    (*ql).front->next = p->next;
    if ((*ql).rear == p)
    {
        (*ql).rear = (*ql).front;
    }
    free(p);
    return 1;
}

int QueueVisit(QueueLink ql)
{
    Queue *p;
    p = ql.front->next;
    while (p)
    {
        printf("%4d", p->data->val);
        p = p->next;
    }
    return 1;
}

/**************************下面是栈的基本操作****************************************/
int InitStack(LinkStack *ls)
{
    int i;
    if (ls == NULL)
    {
        return 0;
    }
    (*ls) = (LinkStack)malloc(sizeof(StackNode));
    for (i = 0; i < MAX_ROW_COLUM; i++)
    {
        (*ls)->data[i] = NULL;
    }
    (*ls)->top = -1;
    return 0;
}

int PushStack(LinkStack *ls, StackElement data)
{
    if (ls == NULL)
    {
        return 0;
    }
    if ((*ls)->top >= MAX_ROW_COLUM - 1)
    {
        return 0;
    }
    (*ls)->top++;
    (*ls)->data[(*ls)->top] = data;
    return 1;
}

int PopStack(LinkStack *ls, StackElement *data)
{
    if (ls == NULL)
    {
        return 0;
    }
    if ((*ls)->top < 0)
    {
        return 0;
    }
    *data = (*ls)->data[(*ls)->top];
    (*ls)->top--;
    return 1;
}

int CheckStackEmpty(LinkStack ls)
{
    return ls->top == -1 ? 1 : 0;
}

int GetStackDepenth(LinkStack ls) 
{
    return  ls == NULL ? 0 : ls->top + 1;
}

/***
   队列的应用：
   层次遍历二叉树
***/
int LevelOrderVisit(BinaryLink bt)
{
    QueueLink q = {0};
    QElement a = {0};
    if (bt)
    {
        InitQueue(&q);
        InsertQueueNode(&q, bt); //这里入队的是根节点。
        while (!CheckQueue(q))
        {
            DeleteQueueNode(&q, &a); //这里把根节点拿出来了。
            printf("%4d", a->val);
            if (a->left)
            {
                InsertQueueNode(&q, a->left); //如果左子树不为空，则把左子树入队，
            }
            if (a->right)
            {
                InsertQueueNode(&q, a->right); //如果右子树不为空，把右子树入队。
            }
        }
    }
    return 1;
}

/*
  队列的应用：
  一道leetcode练习题 下面是层次访问二叉树 
*/
int **levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    int front, rear, counter;
    QueueLink q = {0};
    QElement a = {0};
    int **returnArray = (int **)malloc(MAX_ROW_COLUM * sizeof(int *));
    int i, j;
    *returnColumnSizes = (int *)malloc(MAX_ROW_COLUM * sizeof(int));
    if (root == NULL)
    {
        *returnSize = 0;
        free(*returnColumnSizes);
        free(returnArray);
        return NULL;
    }

    front = rear = 0;
    *returnSize = 0;

    if (root)
    {
        InitQueue(&q);
        rear++;
        InsertQueueNode(&q, root);
    }

    while (front < rear)
    {
        if (*returnSize < MAX_ROW_COLUM)
        {
            (*returnColumnSizes)[*returnSize] = rear - front;
            returnArray[*returnSize] = (int *)malloc((*returnColumnSizes)[*returnSize] * sizeof(int));
        }

        for (counter = 0; counter < (*returnColumnSizes)[*returnSize]; counter++)
        {
            DeleteQueueNode(&q, &a);
            front++;
            returnArray[*returnSize][counter] = a->val;
            if (a->left)
            {
                InsertQueueNode(&q, a->left);
                rear++;
            }
            if (a->right)
            {
                InsertQueueNode(&q, a->right);
                rear++;
            }
        }
        (*returnSize)++;
    }
    printf("\r\nfinal returnsize=%d\r\n", *returnSize);
    return returnArray;
}

/* 自底向上输出二叉树 */
int **levelOrderBottom(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    int front, rear, counter;
    QueueLink q = {0};
    QElement a = {0};
    StackElement b = {0};
    LinkStack sl = {0};
    int tempCounter[MAX_ROW_COLUM] = {0};
    int **returnArray = (int **)malloc(MAX_ROW_COLUM * sizeof(int *));
    int i, j, k = 0;

    *returnColumnSizes = (int *)malloc(MAX_ROW_COLUM * sizeof(int));
    if (root == NULL)
    {
        *returnSize = 0;
        free(*returnColumnSizes);
        free(returnArray);
        return NULL;
    }
    front = rear = 0;
    *returnSize = 0;

    if (root)
    {
        InitQueue(&q);
        InitStack(&sl);
        InsertQueueNode(&q, root);
        rear++;
        while (!CheckQueue(q))
        {
            tempCounter[*returnSize] = rear - front;
            for (counter = 0; counter < tempCounter[*returnSize]; counter++)
            {
                DeleteQueueNode(&q, &a);
                front++;
                PushStack(&sl, a);
                if (a->right)
                {
                    InsertQueueNode(&q, a->right);
                    rear++;
                }
                if (a->left)
                {
                    InsertQueueNode(&q, a->left);
                    rear++;
                }
            }
            (*returnSize)++;
        }

        while (!CheckStackEmpty(sl))
        {
            for (i = *returnSize - 1; i >= 0; i--)
            {
                returnArray[k] = (int *)malloc(tempCounter[i] * sizeof(int));
                for (j = 0; j < tempCounter[i]; j++)
                {
                    PopStack(&sl, &b);
                    returnArray[k][j] = b->val;
                }
                (*returnColumnSizes)[k] = tempCounter[i];
                k++;
            }
        }
    }
    return returnArray;
}

/**锯齿形遍历二叉树 这种写法这里通过部分用例，例如 1,2,3,4，NULL，NULL，5的二叉树就不能正确返回**/
int **zigzagLevelOrderTemp(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    int front, rear, counter;
    QueueLink q = {0};
    QElement a = {0};
    int **returnArray = (int **)malloc(MAX_ROW_COLUM * sizeof(int *));
    int i, j, order = 1;

    *returnColumnSizes = (int *)malloc(MAX_ROW_COLUM * sizeof(int));
    if (root == NULL)
    {
        *returnSize = 0;
        free(*returnColumnSizes);
        free(returnArray);
        return NULL;
    }

    front = rear = 0;
    *returnSize = 0;

    if (root)
    {
        InitQueue(&q);
        rear++;
        InsertQueueNode(&q, root);
    }

    while (front < rear)
    {
        if (*returnSize < MAX_ROW_COLUM)
        {
            (*returnColumnSizes)[*returnSize] = rear - front;
            returnArray[*returnSize] = (int *)malloc((*returnColumnSizes)[*returnSize] * sizeof(int));
        }
        if (order)
        {
            for (counter = 0; counter < (*returnColumnSizes)[*returnSize]; counter++)
            {
                DeleteQueueNode(&q, &a);
                front++;
                returnArray[*returnSize][counter] = a->val;
                if (a->right)
                {
                    InsertQueueNode(&q, a->right);
                    rear++;
                }
                if (a->left)
                {
                    InsertQueueNode(&q, a->left);
                    rear++;
                }
            }
        }
        else
        {
            for (counter = 0; counter < (*returnColumnSizes)[*returnSize]; counter++)
            {
                DeleteQueueNode(&q, &a);
                front++;
                returnArray[*returnSize][counter] = a->val;
                if (a->left)
                {
                    InsertQueueNode(&q, a->left);
                    rear++;
                }
                if (a->right)
                {
                    InsertQueueNode(&q, a->right);
                    rear++;
                }
            }
        }
        (*returnSize)++;
        order = !order;
    }
    return returnArray;
}

/* 通过2个栈来实现锯齿形二叉树的遍历 */
int **zigzagLevelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    LinkStack slFirst = {0};
    LinkStack slSecond = {0};
    StackElement a = {0};
    int stackFirstCounter = 0;
    int stackSecondCounter = 0;
    int **returnArray = (int **)malloc(MAX_ROW_COLUM * sizeof(int *));
    int order = 1;

    *returnColumnSizes = (int *)malloc(MAX_ROW_COLUM * sizeof(int));
    if (root == NULL)
    {
        *returnSize = 0;
        free(*returnColumnSizes);
        free(returnArray);
        return NULL;
    }

    *returnSize = 0;

    if (root)
    {
        InitStack(&slFirst);
        InitStack(&slSecond);
        PushStack(&slFirst, root);
        while (!CheckStackEmpty(slFirst) || !CheckStackEmpty(slSecond))
        {
            if (order)
            {
				(*returnColumnSizes)[*returnSize] = GetStackDepenth(slFirst);
                returnArray[*returnSize] = (int* )malloc((GetStackDepenth(slFirst)) * sizeof(int));
                while (!CheckStackEmpty(slFirst))
                {
                    PopStack(&slFirst, &a);
					returnArray[*returnSize][stackFirstCounter++] = a->val;
                    if (a->left)
                    {
                        PushStack(&slSecond, a->left);
                    }
                    if (a->right)
                    {
                        PushStack(&slSecond, a->right);
                    }
                }
            }
            else
            {
				(*returnColumnSizes)[*returnSize] = GetStackDepenth(slSecond);
                returnArray[*returnSize] = (int* )malloc((GetStackDepenth(slSecond)) * sizeof(int));
                while (!CheckStackEmpty(slSecond))
                {
                    PopStack(&slSecond, &a);
                    returnArray[*returnSize][stackSecondCounter++] = a->val;
                    if (a->right)
                    {
                        PushStack(&slFirst, a->right);
                    }
                    if (a->left)
                    {
                        PushStack(&slFirst, a->left);
                    }
                }
            }
            stackFirstCounter = 0;
            stackSecondCounter = 0;
            (*returnSize)++;
            order = !order;
        }
    }
    return returnArray;
}

int main(void)
{
    BinaryLink bt = {0};
    QueueLink ql = {0};
    int colum[100] = {0};
    int **test = &colum;
    int returnSize = 0;
    int **returnArray = NULL;
    int i = 0;
    int j = 0;

    CreateBinaryTree(&bt);
    PreVisit(bt);
    InitQueue(&ql);
    printf("\r\naccess queue\r\n");
    LevelOrderVisit(bt);
    returnArray = zigzagLevelOrder(bt, &returnSize, test);
    printf("\r\nover\r\n");
}