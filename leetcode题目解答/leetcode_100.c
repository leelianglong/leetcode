#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#if 0
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
#endif
/*
* 该题的思路：
1、使用一个全局数组，初始化成0；
2、当前一个树的节点为NULL 和 另一个树的节点非NULL，那么这2个树不同；2个树的当前节点非NULL
如果两个节点的值不同，那么这2个树也不同 
3、使用dfs遍历所有节点.
*/
#define DATA_SIZE     1024
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryTree;

void dfs(struct TreeNode* p, struct TreeNode* q, int* data, int* counter)
{
    if ((p == NULL && q != NULL) || (p != NULL && q == NULL)) {
        data[(*counter)++] = 1;
        return;
    }
    if (p == NULL && q == NULL) {
        return;
    }
    if (p->val != q->val) {
        data[(*counter)++] = 1;
        return;
    }
    dfs(p->left, q->left, data, counter);
    dfs(p->right, q->right, data, counter);
}

bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    int data[DATA_SIZE] = {0};
    int counter = 0;
    dfs(p, q, data, &counter);
    for (int i = 0; i < counter; i++) {
        if (data[i] == 1) {
            return false;
        }
    }
    return true;
}

void CreatBinary(BinaryTree* bt, int* data, int* counter)
{
    if (data[(*counter)] == 999) {
        *bt = NULL;
        (*counter)++;
        return;
    }
    (*bt) = (BinaryTree)malloc(sizeof(BinaryTreeNode));
    if (*bt == NULL) {
        return;
    }
    (*bt)->val = data[(*counter)];
    (*counter)++;
    CreatBinary(&(*bt)->left, data, counter);
    CreatBinary(&(*bt)->right, data, counter);
}

int main(void)
{
    BinaryTree root1 = NULL;
    int data1[] = {1,2,999,999,3,999,999,9999};
    int counter1 = 0;
    BinaryTree root2 = NULL;
    int data2[] = {1,2,999,999,3,999,999,9999};
    int counter2 = 0;
    CreatBinary(&root1, data1, &counter1);
    CreatBinary(&root2, data2, &counter2);
    bool result = isSameTree(root1, root2);
    printf("result=%u", result);
    system("pause");
}