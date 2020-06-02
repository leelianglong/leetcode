#include <stdio.h>
#include <stdlib.h>

/*
* 二叉查找树，也称二叉搜索树，或二叉排序树。其定义也比较简单，要么是一颗空树，要么就是具有如下性质的二叉树：

*（1）若任意节点的左子树不空，则左子树上所有结点的值均小于它的根结点的值；

*（2） 若任意节点的右子树不空，则右子树上所有结点的值均大于它的根结点的值；

*（3） 任意节点的左、右子树也分别为二叉查找树；

*（4） 没有键值相等的节点。
*/

// 题目： 给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，使得每个节点的值是原来的节点值加上所有大于它的节点值之和

/**
 * Definition for a binary tree node.
**/

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

typedef struct TreeNode BinaryNode, *BinaryTree;
typedef void(*vist)(int);

int CreatBinary(BinaryTree* bt)
{
    int data[] = {5,2,999,999,13,999,999,999,999,999,999};
    static int i = 0;
    if (data[i] == 999) {
        *bt = NULL;
        i++;
        return 0;
    }
    (*bt) = (BinaryTree)malloc(sizeof(BinaryNode));
    if (*bt == NULL) {
        return 0;
    }
    (*bt)->val = data[i];
    i++;
    CreatBinary(&(*bt)->left);
    CreatBinary(&(*bt)->right);
}

void print(int data)
{
    printf("%4d", data);
}

void PreOrderTraverse(BinaryTree bt, vist p)
{
    if (bt) {
        p(bt->val);
        PreOrderTraverse(bt->left,p);
        PreOrderTraverse(bt->right,p);
    }
}
#if 0
//这个算法有问题。
void dfs(BinaryTree* root)
{
    int preSum = 0;
    if (root != NULL && *root != NULL) {
        dfs(&(*root)->right);
        (*root)->val = preSum + (*root)->val;
        preSum = (*root)->val;
        dfs(&(*root)->left);
    }
}
#endif

int dfs1(BinaryTree* root, int val)
{
    int preSum = 0;
    /* 先把右子树的所有节点的的和计算出来 */
    if ((*root)->right != NULL) {
        preSum = dfs1(&(*root)->right, val);
        (*root)->val += preSum;
    }
    else {
        (*root)->val += val;
    }

    preSum = (*root)->val;
    if((*root)->left != NULL) {
        preSum = dfs1(&(*root)->left, (*root)->val); //这里传入的参数是右子树所有节点的和，然后加到左子树的节点上。
    }
    return preSum;
}

struct TreeNode* convertBST(struct TreeNode* root){
    if (root != NULL) {
        dfs1(&root,0);
    }
    return root;
}


int main(void)
{
    BinaryTree bt = NULL;
    CreatBinary(&bt);
    PreOrderTraverse(bt, print);
    bt = convertBST(bt);
    printf("\r\nchange tree:\r\n");
    PreOrderTraverse(bt, print);
}


