#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW_COLUM 512

typedef struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryLink;

typedef BinaryLink StackElement;
typedef struct STNode
{
    int top;
    int matchCount;
    int data[MAX_ROW_COLUM]; //这个栈里面只存储节点值。不要存储节点关系。
} StackNode, *LinkStack;

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
    (*ls)->matchCount = 0;
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

int IsLeafNode(BinaryLink root)
{
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return 0;
}


void RecordMatchPath(LinkStack* ls, int **data, int *returnColumSize)
{
    int i;
    int dataCounter;
    if (ls == NULL) {
        return;
    }
    i = (*ls)->matchCount;
    dataCounter = GetStackDepenth(ls);
    data[i] = malloc(dataCounter * sizeof(int));
    if (data[i] == NULL) {
        return;
    }
    memset(data[i], 0, dataCounter * sizeof(int));
    memcpy(data[i], ls->data, dataCounter * sizeof(int));
    returnColumSize[i] = dataCounter;
    (*ls)->matchCount++;
}


void PathSumPatch(BinaryLink root, LinkStack* ls, int ** data, 
    int *returnColumnSizes, int curSum, int sum)
{
    int data;
    if (root == NULL || ls == NULL) {
        return 0;
    }

    PushStack(ls, root->val);
    if (IsLeafNode(root)) {
        if (curSum + root->val  == sum) {
            RecordMatchPath(ls, data, returnColumnSizes);
        }
        return;
    }

    PathSumPatch(root->left, ls, data, returnColumnSizes, curSum + root->val, sum);
    if (root->left) {
        PopStack(ls,&data);
    }

    PathSumPatch(root->right, ls, data, returnColumnSizes, curSum + root->val, sum);
    if (root->right) {
        PopStack(ls,&data);
    }
}

int** pathSum(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes){
    int curSum = 0;
    LinkStack ls = NULL;
    int **data = NULL;
    if (returnColumnSizes == NULL) {
        return NULL;
    }
    if (returnSize == NULL) {
        *returnColumnSizes = NULL; //如果行没有，则把列也设置成0
        return NULL;
    }

    if(root == NULL) {
        *returnSize = NULL;
        returnColumnSizes = NULL;
        return NULL;
    }

    *returnColumnSizes = NULL;
    *returnSize = 0;
    InitStack(&ls);

    **data = (int **)malloc(sizeof(int *) * 1024);
    if (data == NULL) {
        return NULL;
    }
    memset(data, 0, sizeof(int *) * 1024);
    
    *returnColumnSizes = (int *)malloc(sizeof(int) * 1024);
    if (*returnColumnSizes == NULL) {
        return NULL;
    }
    memset(*returnColumnSizes, 0, sizeof(int) * 1024);
    PathSumPatch(root, &ls, data, *returnColumnSizes, curSum, sum);
}
