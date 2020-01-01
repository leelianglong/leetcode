#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

int counter = 0;
int res[10000] = {0};
int returnCounter = 0;

int com(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

void PreOrderTraverse(struct TreeNode* bt, int* res, int* returnCounter)
{
    if (bt) {
        res[(*returnCounter)++] = bt->val;
        PreOrderTraverse(bt->left, res, returnCounter);
        PreOrderTraverse(bt->right, res, returnCounter);
    }
}

int* getAllElements(struct TreeNode* root1, struct TreeNode* root2, int* returnSize){

	PreOrderTraverse(root1, res, &returnCounter);
	
	PreOrderTraverse(root2, res, &returnCounter);
	
	qsort(res, returnCounter, sizeof(int), com);

	*returnSize = returnCounter;
	return res;
}


int CreatBinary(struct TreeNode** bt, int* data)
{
    if (data[counter] == 999) {
        *bt = NULL;
        counter++;
        return 0;
    }
    (*bt) = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (*bt == NULL) {
        return 0;
    }
    (*bt)->val = data[counter];
    counter++;
    CreatBinary(&(*bt)->left, data);
    CreatBinary(&(*bt)->right, data);
}

int main(void)
{
	struct TreeNode* root1 = NULL;
	struct TreeNode* root2 = NULL;
	int returnCounter1 = 0;
	int i;
	int data1[] = {0,-10,999,999,10,999,999,999,999,999,999,999,999,999,999};
	int data2[] = {5,1,0,999,999,2,999,999,7,999,999,999,999,0};

	CreatBinary(&root1, data1);
	counter = 0;
	CreatBinary(&root2, data2);
	printf("\r\nreturnCounter=%d\r\n", returnCounter);
	int* result = getAllElements(root1, root2, &returnCounter1);
	printf_s("\r\nthe length = %d\r\n", returnCounter1);
	for (i = 0; i < returnCounter1; i++) {
		printf("%4d", result[i]);
	}
	system("pause");
}
