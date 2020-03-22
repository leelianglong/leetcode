#include <stdio.h>
#include <stdlib.h>

/*
求二叉树的最大深度：
从宏观上来看，先求左子树的深度，再求右子树的深度。然后比较2个深度谁大一点，较大值即是二叉树的深度
*/

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryTree;

int dfs(struct TreeNode* node)
{
    if (node == NULL) {
        return 0;
    }
    int leftDeepth = dfs(node->left) + 1; // 这里加1 表示 父节点的深度
    int rightDeepTh = dfs(node->right) + 1; // 这里加1 表示 父节点的深度
    return leftDeepth > rightDeepTh ? leftDeepth : rightDeepTh;
}

int maxDepth(struct TreeNode* root){
    return dfs(root);
}