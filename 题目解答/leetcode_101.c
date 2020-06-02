#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
* �ж�һ�����ǲ��ǶԳ�����˼·��
1����һ���ڵ�������������������ʱ��Ҫ�ж������������� ���ڵ� �� �������ĸ��ڵ��ֵ�ǲ������
2����һ���ڵ������������������������Ƕ�������ʱ��Ҫ�ж�����һ���ڵ��������ĸ��ڵ� �� ��һ���������ĸ��ڵ��Ƿ����
   ���� ��֮��
3��ֻҪ��������2���ľ��ǶԳƶ�����
4�������һ���ؼ����� Ҫ��һ������������2����������������������
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
    return dfs(root, root); // ��һ�������� ����2����������������
}


int main(void)
{

    system("pause");
}