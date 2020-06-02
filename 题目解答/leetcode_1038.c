/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
根据二叉搜索树的性质，通过后续遍历一次达成
*/

typedef struct TreeNode BinaryNode, *BinaryTree;

int dfs(BinaryTree* root, int val)
{
    int preSum = 0;
    /* 先把右子树的所有节点的的和计算出来 */
    if ((*root)->right != NULL) {
        preSum = dfs(&(*root)->right, val);
        (*root)->val += preSum;
    }
    else {
        (*root)->val += val;
    }

    preSum = (*root)->val;
    if((*root)->left != NULL) {
        preSum = dfs(&(*root)->left, (*root)->val); //这里传入的参数是右子树所有节点的和，然后加到左子树的节点上。
    }
    return preSum;
}

struct TreeNode* bstToGst(struct TreeNode* root){
    if (root != NULL) {
        dfs(&root,0);
    }
    return root;
}
