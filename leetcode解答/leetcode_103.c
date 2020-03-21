/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#define  MAX_ROW_COLUM 1024
typedef struct TreeNode  BinaryTreeNode, *BinaryLink;

typedef struct TreeNode  BinaryTreeNode, *BinaryLink;

typedef BinaryLink StackElement;
typedef struct STNode
{
    int top;
    StackElement data[MAX_ROW_COLUM];
} StackNode, *LinkStack;

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
    return  ls == NULL ? 0 : ls->top;
}

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
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
				(*returnColumnSizes)[*returnSize] = 1 + GetStackDepenth(slFirst);
                returnArray[*returnSize] = (int* )malloc((1 + GetStackDepenth(slFirst)) * sizeof(int));
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
				(*returnColumnSizes)[*returnSize] = 1 + GetStackDepenth(slSecond);
                returnArray[*returnSize] = (int* )malloc((1 + GetStackDepenth(slSecond)) * sizeof(int));
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