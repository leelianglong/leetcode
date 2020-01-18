#include <stdio.h>
#include <stdlib.h>

/*
* 该题目关键点：
1、二叉树的构造上，采用前序遍历，添加节点时，要把二叉树按照满二叉树来填，叶子节点使用999来填充
2、要计算二叉树上某些点的和，可以使用深度优先搜索(dfs),来找到合适点，关键是 dfs最终要递归调用，
要想把和传出去，一定要使用指针传参，内部改变，然后传出去。
*/
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryTree;

void dfs(BinaryTree node, int *sum)
{
    if (node == NULL) {
        return;
    }

    if (node->val % 2 == 0) {
        if (node->left != NULL) {
            if (node->left->left != NULL) {
                *sum += node->left->left->val;
            }
            if (node->left->right != NULL) {
                *sum += node->left->right->val;
            }
        }
        if (node->right != NULL) {
            if (node->right->left != NULL) {
                *sum += node->right->left->val;
            }
            if (node->right->right != NULL) {
                *sum += node->right->right->val;
            }
        }
    }
    dfs(node->left, sum);
    dfs(node->right, sum);
}

int sumEvenGrandparent(BinaryTree root){
    int sum = 0;
    dfs(root, &sum);
    return sum;
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
    int data[] = {50,999,54,98,999,999, 6, 999,34, 999, 999, 999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999};
    BinaryTree root = NULL;
    int counter = 0;

    CreatBinary(&root, data, &counter);
    int result = sumEvenGrandparent(root);
    printf("%4d", result);
    system("pause");
}