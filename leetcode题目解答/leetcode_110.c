int height(struct TreeNode* root)
{
    if (root == NULL) {
        return 0;
    }
    int leftHeight = height(root->left) + 1;
    int rightHeight = height(root->right) + 1;
    return leftHeight > rightHeight ? leftHeight : rightHeight;
}

bool isBalanced(struct TreeNode* root){
    if (root == NULL) {
        return true;
    }
    return abs((height(root->left) - height(root->right))) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}
