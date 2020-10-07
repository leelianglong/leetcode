
// 注意全局变量的使用，在外面定义，一定要在主函数里面初始化。

int** result;
int findCounter;
#define COUNTER  50000

void dfs(int curPos, int lastSelectData, int* num, int numSize, int* tmp, int* tmpCounter, int** returnColumnSizes)
{
    if (curPos == numSize) {
        if ((*tmpCounter) >= 2) {
            result[findCounter] = (int*)malloc(sizeof(int) * (*tmpCounter));
            memcpy(result[findCounter], tmp, sizeof(int) * (*tmpCounter));
            (*returnColumnSizes)[findCounter] = (*tmpCounter);
            findCounter++;
        }
        return;
    }
    if (num[curPos] >= lastSelectData) { // 官方解答
        tmp[(*tmpCounter)++] = num[curPos];
        dfs(curPos + 1, num[curPos], num, numSize, tmp, tmpCounter, returnColumnSizes);
        (*tmpCounter)--;
    }
    if (num[curPos] != lastSelectData) {
        dfs(curPos + 1, lastSelectData, num, numSize, tmp, tmpCounter, returnColumnSizes);
    }
}


int** findSubsequences(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    result = (int**)malloc(sizeof(int*) * COUNTER);
    *returnColumnSizes = (int*)malloc(sizeof(int) * COUNTER);
    memset(*returnColumnSizes, 0, sizeof(int) * COUNTER);

    int* tmp = (int*)malloc(sizeof(int) * numsSize);
    memset(tmp, 0, sizeof(int) * numsSize);
    int tmpCounter = 0;
    findCounter = 0; // 
    *returnSize = 0;
    dfs(0, INT_MIN, nums, numsSize, tmp, &tmpCounter, returnColumnSizes);
    *returnSize = findCounter;
    return result;
}
