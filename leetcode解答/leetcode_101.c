#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
* 判断一个树是不是对称树，思路：
1、当一个节点有左子树和右子树的时候，要判断他们左子树的 根节点 和 右子树的根节点的值是不是相等
2、当一个节点有左子树和右子树并且他们都有子树时，要判断其中一个节点左子树的根节点 和 另一个右子树的根节点是否相等
   或者 反之；
3、只要满足上面2条的就是对称二叉树
4、本题的一个关键点是 要把一个二叉树当成2个二叉树来分析。。。。
*/
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryTree;

bool dfs(struct TreeNode* nodeA, struct TreeNode* nodeB)
{
    if (nodeA == NULL && nodeB == NULL) {
        return true;
    }
    if ((nodeA == NULL && nodeB != NULL) || (nodeA != NULL && nodeB == NULL)) {
        return false;
    }
    if (nodeA->val != nodeB->val) {
        return false;
    }
    return dfs(nodeA->left, nodeB->right) && dfs(nodeA->right, nodeB->left);
}

bool isSymmetric(struct TreeNode* root){
    if (root == NULL) {
        return false;
    }
    return dfs(root, root); // 把一个二叉树 当成2个二叉树来分析。
}


int main(void)
{

    system("pause");
}