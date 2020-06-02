/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

/*
* 思路： 从前序和中序遍历构造二叉树。 从前序遍历中获取 根节点， 该根节点把 中序遍历分成左右子树2部分。然后依次处理前序遍历的左子树、中序遍历的左子树部分
* 和 前序遍历的右子树、中序遍历的右子树部分。
*/
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    if (preorderSize <= 0) {
        return NULL;
    }

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[0]; //前序遍历的首元素肯定是跟节点
    int index = 0;
    while (index < inorderSize && inorder[index] != preorder[0]) {
        index++; // 找到中序遍历中的跟节点所在的位置
    }
    printf("\n index=%u", index);
    root->left = buildTree(preorder + 1, index, inorder, index);
    root->right = buildTree(preorder + 1 + index, preorderSize - (index + 1), inorder + index + 1, inorderSize - (index + 1));
    return root;
}
