#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/****************** �������ṹ���� ****************/
typedef struct BTNode {
    int data;
    struct BTNode* lchild;
    struct BTNode* rchild;
} BinaryNode, *BinaryTree;
/****************** �������ṹ���� ****************/

/****************** ջ�Ľṹ���� ****************/
#define  STATCK_LENGTH           1000
typedef struct {
    int top;
    BinaryTree data;
}Stack;
/****************** ջ�Ľṹ���� ****************/
/***************************************ջ��������**************************************/
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
����ʵ�ֵ�ջ������������
һ��ʼtop����׶Σ�ÿ����ջ��top�����ӣ���Ԫ�طŵ�ջ����
��ջʱ���ȴ�ջ���ó�Ԫ�أ�Ȼ��ջ��ָ��top�ټ�����
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
/***************************************ջ��������**************************************/

/* 
��������������
��������ǰ��ʽ���������������ڹ�������ʱ��һ��Ҫ��Ҷ�ӽڵ���������������������óɽ�������
���ܰ���Ԥ�����ɶ�������
ע�⣺�ݹ����Ҳ�Ǻ���ÿ������һ�Σ��ú����еľֲ�����Ҳ���������ʱ����ʧ�������Ҫ������
�����˳�֮ǰ����Ҫ���ֵı�����Ҫ���ó�ȫ�ֱ��������߾�̬�ֲ�����������ʹ��ָ�봫�롣
��ǰ�����ڶ�ε���ʱ��Ҫ�ǵð�counter���㡣
*/
void CreatBinary(BinaryTree* bt, int* data, int* counter)
{
    if (data[(*counter)] == 999) {
        *bt = NULL;
        (*counter)++;
        return 0;
    }
    (*bt) = (BinaryTree)malloc(sizeof(BinaryNode));
    if (*bt == NULL) {
        return 0;
    }
    (*bt)->data = data[(*counter)];
    (*counter)++;
    CreatBinary(&(*bt)->lchild, data, counter);
    CreatBinary(&(*bt)->rchild, data, counter);
}

/*
����������
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
�������п�
*/
bool BinaryTreeIsEmpety(BinaryTree bt)
{
    return bt == NULL ? true : false;
}

/*
��ȡ�����������(�ݹ鷽��)
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
��ȡ����ȵ���һ�ּ򵥵ݹ�汾д��,�ȼ�������������ȣ��ټ�������������ȣ�Ȼ��ȡ���нϴ�ģ����
�ټ��ϸ��ڵ�����1���������������������
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
ͳ��Ҷ�ӽڵ�ĸ���
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
��������ǰ�����(�ݹ�汾)
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
��������ǰ�����(�ǵݹ�汾��ջʵ��)
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
���������������(�ݹ�汾)
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
�������ĺ������(�ݹ�汾)
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