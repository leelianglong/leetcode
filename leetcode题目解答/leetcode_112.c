#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
* ·�������⣺����һ����������һ��ָ�������֣��Ӹ��ڵ㵽Ҷ�ӽڵ������·����ֻҪ��һ���ĺ������ֵ
* �򷵻��档
* ˼·��ʹ�õݹ���ã�
* 1��ʹ��targetֵ��ȥ��ǰ�ڵ��ֵ��
* 2���ݹ���õĽ������ǵ�ǰ�ڵ������������������Ϊ��
* 3���ж�target�Ƿ�Ϊ0�����Ϊ0����ʾ�ҵ�����·����
*/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool hasPathSum(struct TreeNode* root, int sum){
    if (root == NULL) {
        return false;
    }
    sum -= root->val; // ע�����һ�����ȼ����ڵ��ֵ����ȡ�жϵ�ǰ�ڵ��ǲ���Ҷ�ӽڵ㡣 
    if (root->left == NULL && root->right == NULL) {
        return (sum == 0);
    }
    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
}

int main(void)
{

    system("pause");
}