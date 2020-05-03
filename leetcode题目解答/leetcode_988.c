/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void reverseStr(char* data)
{
    int right = strlen(data) - 1;
    int left = 0;
    while (left <= right) {
        char tmp = data[left];
        data[left] = data[right];
        data[right] = tmp;
        left++;
        right--;
    }
}
int cmp(const void* a, const void* b)
{
    char* aa = *(char**)a;
    char* bb = *(char**)b;
    return strcmp(aa, bb);
}
void step(struct TreeNode* root, char** res, int* returnSize, int *tmpCounter, char* tmpSave)
{
    if (root->left == NULL && root->right == NULL) {
        tmpSave[(*tmpCounter)] = (root->val - 0) + 'a';
        (*tmpCounter)++;
        res[(*returnSize)] = (char*)malloc(sizeof(char) * 8500);
        memset(res[*returnSize], 0, sizeof(char) * 8500);
        strncpy(res[*returnSize], tmpSave, (*tmpCounter));
        (*returnSize)++;
        return;
    }
    tmpSave[(*tmpCounter)] = (root->val - 0) + 'a';
    (*tmpCounter)++;
    if (root->left) {
        step(root->left, res, returnSize, tmpCounter, tmpSave);
        (*tmpCounter)--;
    }
    if (root->right) {
        step(root->right, res, returnSize, tmpCounter, tmpSave);
        (*tmpCounter)--;
    }
}

char * smallestFromLeaf(struct TreeNode* root){
    if (root == NULL) {
        return NULL;
    }
    char** res = (char**)malloc(sizeof(char*) * 8500);
    int returnSize = 0;
    int tmpCounter = 0;
    char* tmpSave = (char*)malloc(sizeof(char) * 8500);
    memset(tmpSave, 0, sizeof(char) * 8500);
    step(root, res, &returnSize, &tmpCounter, tmpSave);
    for (int i = 0; i < returnSize; i++) {
       // printf("\n11 %s",  res[i]);
        reverseStr(res[i]);
        //printf("\n22 %s",  res[i]);
    }
    qsort(res, returnSize, sizeof(char*),cmp);
    #if 0
    printf("\nafter sort:\n");
    for (int k = 0; k < returnSize; k++) {
        printf("%s\n", res[k]);
    }
    #endif
    return res[0];
}
