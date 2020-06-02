#include <stdio.h>
#include <stdlib.h>
/*
 * �������һ��������
 * һ���ؼ��㣺������������ʲô��ı�����ʵ���϶��Ƿ��ʸ��ڵ��ֵ
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
 #define BINARY_TREE_SIZE     1000
 void inorder(struct TreeNode* root, int* saveData, int* counter)
 {
     if (root == NULL) {
         return;
     }
     if (root->left) {
        inorder(root->left, saveData, counter);
     }
     saveData[(*counter)++] = root->val;
     if (root->right) {
        inorder(root->right, saveData, counter);
     }
 }

int* inorderTraversal(struct TreeNode* root, int* returnSize){
    if (root == NULL) {
        //return NULL; //����������жϣ�LeetCode��������[]ʱ���������ֱ�ӷ���NULL������������
    }
    int* res = (int*)malloc(BINARY_TREE_SIZE * sizeof(int));
    if (res == NULL) {
        return NULL;
    }
    memset(res, 0, BINARY_TREE_SIZE);
    *returnSize = 0; // �����ǹؼ���LeetCode�����ڵ���ʱ�������ֵû�г�ʼ�����ñ�����ֵ�����ֵ��
    //������Ĳ����У���ʹ��(*counter)++,�������û�г�ʼ������������ᵼ�·���Խ�硣
    inorder(root, res, returnSize);
    return res;
}