#include <stdio.h>
#include <stdlib.h>

/*
��Ŀ��
����һ��������������ÿ����㶼���һ�� 0-9 �����֣�ÿ���Ӹ���Ҷ�ӽڵ��·��������һ�����֡�
���磬�Ӹ���Ҷ�ӽڵ�·�� 1->2->3 �������� 123
����Ӹ���Ҷ�ӽڵ����ɵ���������֮��
˼·��
�������дӸ��ڵ㵽Ҷ�ӽڵ������·���ϵ����֣�Ҷ�ӽڵ��Ǹ�λ��Ȼ����������ڵ���ʮλ����λ..
���㷨�Ͼ��ó�10��ʵ�֡�
����Ŀ������ʹ��ջ���洢�Ӹ��ڵ����������Ҷ�ӽڵ�����ݣ�Ȼ���ٳ�ջ�����10 �ۼӼ��㣬
������ô��������·��������Ҫ���ǡ�
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
    if (bt->left == NULL && bt->right == NULL) { //�Ѿ���Ҷ�ӽڵ��ˣ����ص�ǰֵ���ϵ����ֵ֮ǰ������ֵ��
        return bt->val + num * 10; // ÿһ�㶼��10����ϵ��
    }
    return dfs(bt->left, bt->val + num * 10) + dfs(bt->right, bt->val + num * 10);
}

int sumNumbers(struct TreeNode* root){
    if (root == NULL) {
        return 0;
    }
    return dfs(root, 0);
}


