#include <stdio.h>
#include <stdlib.h>

/*
二叉树的最小深度，从根节点到最近的叶子节点经过的。
叶子节点的定义是左孩子和右孩子都为 null 时叫做叶子节点
当 root 节点左右孩子都为空时，返回 1
当 root 节点左右孩子有一个为空时，返回不为空的孩子节点的深度
当 root 节点左右孩子都不为空时，返回左右孩子较小深度的节点值

*/
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int dfs_deepth(struct TreeNode* bt) 
{
    if (bt == NULL) {
        return 0;
    }
    if (bt->left == NULL && bt->right == NULL) {
        return 1;
    }
    int leftDeepth = dfs_deepth(bt->left);
    int rightDeepth = dfs_deepth(bt->right);
    if (bt->left == NULL || bt->right == NULL) {
        return leftDeepth + rightDeepth + 1; // 这里 bt->left 或者 bt->right为空的时候，他们的深度会是0，所以尽管这里是2个深度相加 再加1，实际上也就仅仅是子节点不为空的深度
    }
    return (leftDeepth > rightDeepth ? rightDeepth : leftDeepth) + 1; //如果左右子树都不为空，则返回二者较小深度
}
int minDepth(struct TreeNode* root){
    return dfs_deepth(root);
}
