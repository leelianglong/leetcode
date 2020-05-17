/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
* 本题是根据前序遍历和后序遍历构造匹配的二叉树。这里可以利用的知识点是 ：
1、前序遍历的第一个 和 后序遍历的最后一个是根节点。

2、除过根节点后，前序遍历的第一个节点 也就是 后序遍历的倒数第一个节点。 这样拿前序遍历的第一个节点 在后序遍历中找到相等的元素，那么后序遍历数据中从

开始到这个位置都是左子树，从这个位置的下一个位置到倒数第一个位置就是右子树。

3、这样确定前序遍历的左子树 的起始结束位置是 [prestart + 1,  prestart + length + 1], 后序遍历的左子树数的起始位结束置是 [poststart, pos]

前序遍历的右子树的起始结束位置是 [preStart + lengh + 2, preEnd] 后序遍历的起始结束位置[[pos + 1, postEnd - 1]

4、这里各个子树的起始结束位置是关键，确定后直接递归就计算出来。
*/
struct TreeNode* buildTree(int* pre, int preStart, int preEnd, int* post, int postStart, int postEnd) {
    if (preStart > preEnd) {
        return NULL; // 这个是结束条件,这个要放在前面，否则好多用例过不了。异常分支要放在前面。
    }
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = pre[preStart];
    root->left = NULL;
    root->right = NULL;
    if (preStart == preEnd) {
        return root;
    }
    int val = pre[preStart + 1];
    int pos;
    for (pos = postStart; pos <= postEnd; pos++) {
        if (val == post[pos]) {
            int length = pos - postStart;
            root->left = buildTree(pre, preStart + 1, preStart + length + 1, post, postStart, pos);
            root->right = buildTree(pre, preStart + length + 2, preEnd, post, pos + 1, postEnd - 1); // +2 表示，除过 根 和 这里的 pos.
        }
    }
    return root;
}

struct TreeNode* constructFromPrePost(int* pre, int preSize, int* post, int postSize){
    int preStart = 0;
    int preEnd = preSize - 1;
    int postStart = 0;
    int postEnd = postSize - 1;
    //printf("\n%d %d\n", preEnd, postEnd);
    return buildTree(pre, preStart, preEnd, post, postStart, postEnd);
}
