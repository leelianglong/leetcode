#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
* 路劲和问题：给定一个二叉树和一个指定的数字，从根节点到叶子节点的所有路劲中只要有一个的和是这个值
* 则返回真。
* 思路：使用递归调用，
* 1、使用target值减去当前节点的值。
* 2、递归调用的结束点是当前节点的左子树和右子树都为空
* 3、判断target是否为0，如果为0，表示找到这条路径。
*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool hasPathSum(struct TreeNode* root, int sum){
    if (root == NULL) {
        return false;
    }
    sum -= root->val; // 注意进来一定是先减本节点的值，再取判断当前节点是不是叶子节点。 
    if (root->left == NULL && root->right == NULL) {
        return (sum == 0);
    }
    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}

int main(void)
{

    system("pause");
}