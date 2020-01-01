#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/****************** 二叉树结构定义 ****************/
typedef struct BTNode {
    int data;
    struct BTNode* lchild;
    struct BTNode* rchild;
} BinaryNode, *BinaryTree;
/****************** 二叉树结构定义 ****************/

/****************** 栈的结构定义 ****************/
#define  STATCK_LENGTH           1000
typedef struct {
    int top;
    BinaryTree data;
}Stack;
/****************** 栈的结构定义 ****************/
/***************************************栈基本操作**************************************/
bool InitStack(Stack* para)
{
    if (para == NULL) {
        return false;
    }
    para->data = (BinaryTree)malloc(STATCK_LENGTH * sizeof(BinaryNode));
    if (para->data == NULL) {
        return false;
    }
    memset(para->data, 0, STATCK_LENGTH * sizeof(BinaryNode));
    para->top = -1;
    return true;
}

/*
下面实现的栈是向上增长：
一开始top在最底段，每次入栈，top先增加，把元素放到栈顶。
出栈时，先从栈顶拿出元素，然后栈顶指针top再减减。
*/
bool PushStack(Stack* para, BinaryNode data)
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

bool PopStack(Stack* para, BinaryTree data)
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

/* 
创建二二叉树：
这种是以前序方式来创建二叉树，在构造数据时，一定要把叶子节点的左子树和右子树都设置成结束符。
才能按照预期生成二叉树。
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
    int leftDeepth = dfs_deepth(bt->lchild);
    int rightDeepth = dfs_deepth(bt->rchild);
    return (leftDeepth > rightDeepth ? leftDeepth : rightDeepth) + 1;
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
二叉树的前序遍历(递归版本)
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
二叉树的前序遍历(非递归版本，栈实现)
*/
void PreOrderTraverseByStack(BinaryTree bt, int* saveData, int* counter)
{
    Stack binaryTree = {0};
    BinaryTree tmp = bt;

    InitStack(&binaryTree);
    while(tmp || !CheckStackIsEmpty(&binaryTree)) {
        if (tmp) {
            saveData[(*counter)++] = bt->data;
            PushStack(&binaryTree, *tmp);
            tmp = tmp->lchild;
        } else {
            BinaryTree tmp1 = NULL;
            PopStack(&binaryTree, tmp1);
            tmp = tmp1->rchild;
        }
    }
}


/*
二叉树的中序遍历(递归版本)
*/
void PreOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    PreOrderTraverse(bt->lchild, saveData, counter);
    saveData[(*counter)++] = bt->data;
    PreOrderTraverse(bt->rchild, saveData, counter);
}

/*
二叉树的后序遍历(递归版本)
*/
void PreOrderTraverse(BinaryTree bt, int* saveData, int* counter)
{
    if (bt == NULL) {
        return ;
    }
    PreOrderTraverse(bt->lchild, saveData, counter);
    PreOrderTraverse(bt->rchild, saveData, counter);
    saveData[(*counter)++] = bt->data;
}

int main(void)
{
    int data[] = {1,2,4,999,999,5,999,999,3,6,999,999,7,999,999,999,999,999,999,999};
    int counter = 0;
    BinaryTree root = NULL;
    CreatBinary(&root, data, &counter);
    int deepth = GetBinaryTreeDeepth(root);
    int leafCount = GetLeafCounter(root);
    system("pause");
}
