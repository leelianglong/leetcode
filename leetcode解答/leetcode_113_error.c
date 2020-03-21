#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TREE_NODE_COUNTER   1024
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
typedef struct {
    int top;
    struct TreeNode* data[TREE_NODE_COUNTER];
} BinaryTreeStack, *BinaryTreeLink;
bool visited[TREE_NODE_COUNTER] = {false};
int leafNo = 0;
int** finalRes = NULL;
int* finalColumnSize = NULL;
bool InitStack(BinaryTreeLink* btl)
{
    if (btl == NULL) {
        return false;
    }
    int i;
    (*btl) = (BinaryTreeLink)malloc(sizeof(BinaryTreeStack));
    for (i = 0; i < TREE_NODE_COUNTER; i++) {
        (*btl)->data[i] = NULL;
    }
    (*btl)->top = -1;
    return true;
}

bool PushStack(BinaryTreeLink* btl, struct TreeNode* bts)
{
    if ((*btl)->top > TREE_NODE_COUNTER - 1) {
        return false;
    }
    (*btl)->top++;
    (*btl)->data[(*btl)->top] = bts;
    return true;
}

struct TreeNode* PopStack(BinaryTreeLink* btl)
{
    struct TreeNode* tmp = NULL;
    if ((*btl)->top < 0) {
        return tmp;
    }
    tmp = (*btl)->data[(*btl)->top];
    (*btl)->top--;
    return tmp;
}

struct TreeNode* GetTopElement(BinaryTreeLink* btl)
{
    struct TreeNode* tmp = NULL;
    if ((*btl)->top < 0) {
        return tmp;
    }
    tmp = (*btl)->data[(*btl)->top];
    return tmp;
}

bool CheckStackEmpty(BinaryTreeLink btl)
{
    return btl->top == -1 ? true : false;
}

int* GetStackElement(BinaryTreeLink btl)
{
    int* res = (int*)malloc(sizeof(int) * (btl->top + 1));
    memset(res, 0, sizeof(int) * (btl->top + 1));
    int i;
    for (i = 0; i <= btl->top; i++) {
        res[i] = btl->data[i]->val;
    }
    return res;
}

void SearchPath(struct TreeNode* root, int sum, int* returnSize,
    int** returnColumnSizes, BinaryTreeLink* btl)
{
    if (root == NULL) {
        return;
    }
    if (leafNo - 1 >= 0 && visited[leafNo - 1] == true) { 
        return; // 上一个叶子节点已经访问过了
    }
    struct TreeNode* tmpTop = NULL;
    struct TreeNode* popResult = NULL;
    sum -= root->val;
    PushStack(btl,root);
    if (root->left == NULL && root->right == NULL) { // 找到叶子节点
        visited[leafNo++] = true; // 当前叶子节点已经访问。
        if (sum == 0) {
            // 说明找到一条路径遍历栈中全部元素，遍历完后，栈顶出栈
            (*returnColumnSizes)[*returnSize] = (*btl)->top + 1; // 栈大小 // 用来存储元素个数
            finalRes[(*returnSize)] = (int*)malloc(sizeof(int) * ((*btl)->top + 1));
            int* tmpSave = GetStackElement(*btl);
            memcpy(finalRes[(*returnSize)], tmpSave, sizeof(int) * ((*btl)->top + 1));
            (*returnSize)++;
            popResult = PopStack(btl);
            if (popResult == NULL) {
                return;
            }
            tmpTop = GetTopElement(btl);
            sum += popResult->val;
        } else {
            // 栈顶元素退出
            popResult = PopStack(btl);
            if (popResult == NULL) {
                return;
            }
            tmpTop = GetTopElement(btl);
            sum += popResult->val;
        }
        SearchPath(tmpTop->left, sum, returnSize, returnColumnSizes, btl);
        SearchPath(tmpTop->right, sum, returnSize, returnColumnSizes, btl);
    }
    SearchPath(root->left, sum, returnSize, returnColumnSizes, btl);
    SearchPath(root->right, sum, returnSize, returnColumnSizes, btl);
}

int** pathSum(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes){
    BinaryTreeLink btl;
    InitStack(&btl);
    finalRes = (int**)malloc(sizeof(int*) * 100);
   // finalColumnSize = (int*)malloc(sizeof(int) * 100);
  //  *returnColumnSizes = finalColumnSize;
    SearchPath(root, sum, returnSize, returnColumnSizes, &btl);
    return finalRes;
}

int CreateBinaryTree(struct TreeNode** bt)
{
	int data[] = {5,4,11,7,999,999,2,999,999,8,13,999,999,4,5,999,999,1,999,999,999};
    static int i = 0;
    if (data[i] == 999) {
        i++;
        *bt = NULL;
        return 0;
    }
    if (bt == NULL) {
        printf("bt is null");
        return 0;
    }
    (*bt) = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (*bt == NULL) {
        printf("malloc fail");
        return 0;
    }
    (*bt)->val = data[i];
    i++;
    CreateBinaryTree(&(*bt)->left);
    CreateBinaryTree(&(*bt)->right);
    return 1;
}

int main(void)
{
    struct TreeNode* tmp = NULL;
    int(*returnColumnSize)[100] = NULL;
    int returnSize = 0;
    CreateBinaryTree(&tmp);
    pathSum(tmp, 22, &returnSize, returnColumnSize);
    system("pause");
}