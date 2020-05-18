/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize){
    if (inorderSize <= 0) {
        return NULL;
    }
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[postorderSize - 1]; // 后序遍历最后一个是根节点
    root->left = NULL;
    root->right = NULL;
    int pos = 0;
    for (int i = 0; i < inorderSize; i++) {
        if (inorder[i] == root->val) {
            pos = i;
            break;
        }
    } // 根节点把中序遍历分成左右2部分。即左子树和右子树，下面分别基于中序遍历和后序遍历构造左子树和右子树
    root->left = buildTree(inorder, pos, postorder, pos);
    root->right = buildTree(inorder + pos + 1, inorderSize - pos - 1, postorder + pos, postorderSize - 1 - pos);
    return root;
}
