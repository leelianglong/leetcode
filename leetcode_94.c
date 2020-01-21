#include <stdio.h>
#include <stdlib.h>
/*
 * 中序遍历一个二叉树
 * 一个关键点：二叉树无论是什么序的遍历，实际上都是访问根节点的值
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define BINARY_TREE_SIZE     1000
 void inorder(struct TreeNode* root, int* saveData, int* counter)
 {
     if (root == NULL) {
         return;
     }
     if (root->left) {
        inorder(root->left, saveData, counter);
     }
     saveData[(*counter)++] = root->val;
     if (root->right) {
        inorder(root->right, saveData, counter);
     }
 }

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    if (root == NULL) {
        //return NULL; //不能有这个判断，LeetCode用例输入[]时，这里如果直接返回NULL，用例不过。
    }
    int* res = (int*)malloc(BINARY_TREE_SIZE * sizeof(int));
    if (res == NULL) {
        return NULL;
    }
    memset(res, 0, BINARY_TREE_SIZE);
    *returnSize = 0; // 这里是关键，LeetCode可能在调用时，传入的值没有初始化，该变量的值是随机值。
    //在下面的步骤中，会使用(*counter)++,如果这里没有初始化这里的自增会导致访问越界。
    inorder(root, res, returnSize);
    return res;
}