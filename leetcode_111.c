#include <stdio.h>
#include <stdlib.h>

/*
����������С��ȣ��Ӹ��ڵ㵽�����Ҷ�ӽڵ㾭���ġ�
Ҷ�ӽڵ�Ķ��������Ӻ��Һ��Ӷ�Ϊ null ʱ����Ҷ�ӽڵ�
�� root �ڵ����Һ��Ӷ�Ϊ��ʱ������ 1
�� root �ڵ����Һ�����һ��Ϊ��ʱ�����ز�Ϊ�յĺ��ӽڵ�����
�� root �ڵ����Һ��Ӷ���Ϊ��ʱ���������Һ��ӽ�С��ȵĽڵ�ֵ

*/
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int dfs_deepth(struct TreeNode* bt) 
{
    if (bt == NULL) {
        return 0;
    }
    if (bt->left == NULL && bt->right == NULL) {
        return 1;
    }
    int leftDeepth = dfs_deepth(bt->left);
    int rightDeepth = dfs_deepth(bt->right);
    if (bt->left == NULL || bt->right == NULL) {
        return leftDeepth + rightDeepth + 1;
    }
    return (leftDeepth > rightDeepth ? rightDeepth : leftDeepth) + 1;
}
int minDepth(struct TreeNode* root){
    return dfs_deepth(root);
}