#include <stdio.h>
#include <stdlib.h>

/*
题目：
给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。
例如，从根到叶子节点路径 1->2->3 代表数字 123
计算从根到叶子节点生成的所有数字之和
思路：
遍历所有从根节点到叶子节点的所有路径上的数字，叶子节点是个位，然后逐个到根节点是十位，百位..
在算法上就用乘10来实现。
该题目还可以使用栈来存储从根节点遍历到所有叶子节点的数据，然后再出栈逐个乘10 累加计算，
但是怎么遍历所有路径，还需要考虑。
*/
struct TreeNode {
      int val;
      struct TreeNode *left;
      struct TreeNode *right;
 };

int dfs(struct TreeNode* bt, int num)
{
    if (bt == NULL) {
        return 0;
    }
    if (bt->left == NULL && bt->right == NULL) { //已经在叶子节点了，返回当前值加上到达该值之前的所有值。
        return bt->val + num * 10; // 每一层都是10倍关系。
    }
    return dfs(bt->left, bt->val + num * 10) + dfs(bt->right, bt->val + num * 10);
}

int sumNumbers(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    return dfs(root, 0);
}


