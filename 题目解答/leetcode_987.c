/*
本题思路：
1、中序遍历二叉树，获取每个节点的坐标；
2、对X坐标进行升序排序，如果X相等，则对Y进行升序排序，如果Y也相等，则对节点值进行升序排序。（这里选择怎样的排序，取决于坐标系怎么建立）。目前根节点是（0，0），根节点左子树X坐标减1，Y坐标加1，
即对坐标系来讲是向下Y正增长，X向左负增长
3、然后按照X坐标来输出节点值，X坐标一样则输出到一个数组中。
*/




/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */


/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct {
    int x;
    int y;
    int val;
} Location;

int g_nodeCnt;

#define MAX_NODE_COUNT 1001

void GetLocation(struct TreeNode* root, int xx, int yy, Location** tmpSave) {
    tmpSave[g_nodeCnt]->x = xx;
    tmpSave[g_nodeCnt]->y = yy;
    tmpSave[g_nodeCnt]->val = root->val;
    g_nodeCnt++;

    if (root->left) {
        GetLocation(root->left, xx - 1, yy + 1, tmpSave);
    }

    if (root->right) {
        GetLocation(root->right, xx + 1, yy + 1, tmpSave);
    }
}

int cmp(const void* a, const void* b) {
    Location* aa = *(Location**)a;
    Location* bb = *(Location**)b;
    if (aa->x != bb->x) {
        return aa->x - bb->x;
    } else if (aa->y != bb->y){
        return aa->y - bb->y;
    } else {
        return aa->val - bb->val;
    }
    return 0;
}

int** verticalTraversal(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int** result = (int**)malloc(sizeof(int*) * MAX_NODE_COUNT);
    *returnSize = -1;
    g_nodeCnt = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX_NODE_COUNT);
    Location** tmpSave = (Location**)malloc(sizeof(Location*) * MAX_NODE_COUNT);
    for (int i = 0; i < MAX_NODE_COUNT; i++) {
        tmpSave[i] = (Location*)malloc(sizeof(Location));
        memset(tmpSave[i], 0, sizeof(Location));
    }
    GetLocation(root, 0, 0, tmpSave);
    qsort(tmpSave, g_nodeCnt, sizeof(Location*), cmp); // 排序时，注意一个节点的大小，这里不能是sizeof(location).
    int curX = INT_MIN;
    for (int i = 0; i < g_nodeCnt; i++) {
        if (tmpSave[i]->x > curX) {
            (*returnSize)++; // (*returnSize) 初值是-1，这里相加是关键，可以把X坐标一样的存储在一个数组中。
            result[(*returnSize)] = (int*)malloc(sizeof(int) * MAX_NODE_COUNT);
            memset(result[(*returnSize)], 0,  sizeof(int) * MAX_NODE_COUNT);
            (*returnColumnSizes)[*returnSize] = 0;
            result[*returnSize][ (*returnColumnSizes)[*returnSize]] = tmpSave[i]->val;
            ((*returnColumnSizes)[*returnSize])++;
            curX = tmpSave[i]->x;
        } else {
            result[*returnSize][ (*returnColumnSizes)[*returnSize]] = tmpSave[i]->val;
            ((*returnColumnSizes)[*returnSize])++; 
        }
    }
    (*returnSize)++;
    return result;

}

// 下面这种临时存储采用一维指针的方式，更方便一些
typedef struct {
    int x;
    int y;
    int val;
} Location;

int g_nodeCnt;

#define MAX_NODE_COUNT 1001

void GetLocation(struct TreeNode* root, int xx, int yy, Location* tmpSave) {
    tmpSave[g_nodeCnt].x = xx;
    tmpSave[g_nodeCnt].y = yy;
    tmpSave[g_nodeCnt].val = root->val;
    g_nodeCnt++;

    if (root->left) {
        GetLocation(root->left, xx - 1, yy + 1, tmpSave);
    }

    if (root->right) {
        GetLocation(root->right, xx + 1, yy + 1, tmpSave);
    }
}

int cmp(const void* a, const void* b) {
    Location* aa = (Location*)a;
    Location* bb = (Location*)b;
    if (aa->x != bb->x) {
        return aa->x - bb->x;
    } else if (aa->y != bb->y){
        return aa->y - bb->y;
    } else {
        return aa->val - bb->val;
    }
    return 0;
}

int** verticalTraversal(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    int** result = (int**)malloc(sizeof(int*) * MAX_NODE_COUNT);
    *returnSize = -1;
    g_nodeCnt = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * MAX_NODE_COUNT);
    Location* tmpSave = (Location*)malloc(sizeof(Location) * MAX_NODE_COUNT);
    memset(tmpSave, 0, sizeof(Location) * MAX_NODE_COUNT);
    GetLocation(root, 0, 0, tmpSave);
    qsort(tmpSave, g_nodeCnt, sizeof(Location), cmp);
    int curX = INT_MIN;
    for (int i = 0; i < g_nodeCnt; i++) {
        if (tmpSave[i].x > curX) {
            (*returnSize)++;
            result[(*returnSize)] = (int*)malloc(sizeof(int) * MAX_NODE_COUNT);
            memset(result[(*returnSize)], 0,  sizeof(int) * MAX_NODE_COUNT);
            (*returnColumnSizes)[*returnSize] = 0;
            result[*returnSize][ (*returnColumnSizes)[*returnSize]] = tmpSave[i].val;
            ((*returnColumnSizes)[*returnSize])++;
            curX = tmpSave[i].x;
        } else {
            result[*returnSize][ (*returnColumnSizes)[*returnSize]] = tmpSave[i].val;
            ((*returnColumnSizes)[*returnSize])++; 
        }
    }
    (*returnSize)++;
    return result;
}
