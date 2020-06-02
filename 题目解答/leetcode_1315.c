#include <stdio.h>
#include <stdlib.h>

/*
* ����Ŀ�ؼ��㣺
1���������Ĺ����ϣ�����ǰ���������ӽڵ�ʱ��Ҫ�Ѷ��������������������Ҷ�ӽڵ�ʹ��999�����
2��Ҫ�����������ĳЩ��ĺͣ�����ʹ�������������(dfs),���ҵ����ʵ㣬�ؼ��� dfs����Ҫ�ݹ���ã�
Ҫ��Ѻʹ���ȥ��һ��Ҫʹ��ָ�봫�Σ��ڲ��ı䣬Ȼ�󴫳�ȥ��
*/
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} BinaryTreeNode, *BinaryTree;

void dfs(BinaryTree node, int *sum)
{
    if (node == NULL) {
        return;
    }

    if (node->val % 2 == 0) {
        if (node->left != NULL) {
            if (node->left->left != NULL) {
                *sum += node->left->left->val;
            }
            if (node->left->right != NULL) {
                *sum += node->left->right->val;
            }
        }
        if (node->right != NULL) {
            if (node->right->left != NULL) {
                *sum += node->right->left->val;
            }
            if (node->right->right != NULL) {
                *sum += node->right->right->val;
            }
        }
    }
    dfs(node->left, sum);
    dfs(node->right, sum);
}

int sumEvenGrandparent(BinaryTree root){
    int sum = 0;
    dfs(root, &sum);
    return sum;
}

void CreatBinary(BinaryTree* bt, int* data, int* counter)
{
    if (data[(*counter)] == 999) {
        *bt = NULL;
        (*counter)++;
        return;
    }
    (*bt) = (BinaryTree)malloc(sizeof(BinaryTreeNode));
    if (*bt == NULL) {
        return;
    }
    (*bt)->val = data[(*counter)];
    (*counter)++;
    CreatBinary(&(*bt)->left, data, counter);
    CreatBinary(&(*bt)->right, data, counter);
}

int main(void)
{
    int data[] = {50,999,54,98,999,999, 6, 999,34, 999, 999, 999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999};
    BinaryTree root = NULL;
    int counter = 0;

    CreatBinary(&root, data, &counter);
    int result = sumEvenGrandparent(root);
    printf("%4d", result);
    system("pause");
}