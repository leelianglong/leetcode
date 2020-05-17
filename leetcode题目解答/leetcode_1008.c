/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode* bstFromPreorder(int* preorder, int preorderSize){
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;
    root->val = preorder[0];
    struct TreeNode* dummy;
    for (int i = 1; i < preorderSize; i++) {
        dummy = root;
        while ((preorder[i] < dummy->val && dummy->left != NULL) || (preorder[i] > dummy->val && dummy->right != NULL)) {
            if (preorder[i] > dummy->val) {
                dummy = dummy->right;
            } else {
                dummy = dummy->left;
            }
        } // 要从根节点 开始遍历，找到要插入的地方
        
        struct TreeNode* e = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        e->val = preorder[i];
        e->left = NULL;
        e->right = NULL;
        if (dummy->val > preorder[i]) {
            dummy->left = e;
        } else {
            dummy->right = e;
        }
    }
    return root;
}
