#include <stdio.h>
#include <stdlib.h>

/*
��������������ȣ�
�Ӻ������������������������ȣ���������������ȡ�Ȼ��Ƚ�2�����˭��һ�㣬�ϴ�ֵ���Ƕ����������
*/

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryTree;

int dfs(struct TreeNode* node)
{
    if (node == NULL) {
        return 0;
    }
    int leftDeepth = dfs(node->left) + 1; // �����1 ��ʾ ���ڵ�����
    int rightDeepTh = dfs(node->right) + 1; // �����1 ��ʾ ���ڵ�����
    return leftDeepth > rightDeepTh ? leftDeepth : rightDeepTh;
}

int maxDepth(struct TreeNode* root){
    return dfs(root);
}