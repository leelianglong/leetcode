#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TREE_NODE_COUNTER   1024
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int column;
bool step(struct TreeNode* root, int sum, int curSum, int **result, int** returnColumnSize,
    int* saveTmp, int counter)
{
    if (root == NULL) {
        return false;
    }

    if (root->left == NULL && root->right == NULL) {
        curSum += root->val;
        if (sum == curSum) { // 找到一个
            saveTmp[counter++] = root->val;
            result[column] = (int*)malloc(sizeof(int) * counter);
            for (int i = 0; i < counter; i++) {
                result[column][i] = saveTmp[i];
            }
            returnColumnSize[0][column++] = counter;
            return true;
        }
    }
    saveTmp[counter++] = root->val;
    curSum += root->val;

    bool a = step(root->left, sum, curSum, result, returnColumnSize, saveTmp,counter);
    bool b = step(root->right, sum, curSum, result, returnColumnSize, saveTmp, counter);
    return a || b;
}

int** pathSum(struct TreeNode* root, int sum, int* returnSize, int** returnColumnSizes)
{
    column = 0;
    *returnSize = 0; // 这里一定要初始化成0
    int** result = (int**)malloc(sizeof(int*) * TREE_NODE_COUNTER);
    *returnColumnSizes = (int*)malloc(sizeof(int) * TREE_NODE_COUNTER);
    int curSum = 0;
    int counter = 0;
    int saveTmp[TREE_NODE_COUNTER] = {0};

    if (step(root, sum, curSum, result, returnColumnSizes, saveTmp, counter)) {
        *returnSize = column;
        return result;
    }
    return NULL;
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
    int returnSize = 0;
    //int coloumnSize[TREE_NODE_COUNTER] = {0};
    int* returnColumn[TREE_NODE_COUNTER] = {0};
    int target = 22;
    CreateBinaryTree(&tmp);
    int** result = pathSum(tmp, target, &returnSize, returnColumn);
    system("pause");
}