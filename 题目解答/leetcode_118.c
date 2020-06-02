/*
* 采用动态规划，
*/

int** generate(int numRows, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    int** result = NULL;
    if (numRows <= 0) {
        return result;
    }
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * numRows);
    result = (int**)malloc(sizeof(int*) * numRows);
    for (int i = 0; i < numRows; i++) {
        result[i] = (int*)malloc(sizeof(int) * (i + 1));
        (*returnColumnSizes)[i] = i + 1;
    }
    *returnSize = numRows;
    for (int i = 0; i < numRows; i++) { // 先把初始值设置好，2边的都是1.
        result[i][0] = 1;
        result[i][i] = 1;
    }
    if (numRows <= 2) {
        return result;
    }
    for (int k = 2; k < numRows; k++) {// 从第二行开始，它的中间元素有上一行来决定。为了坐标好计算，可以以左边对齐。
        for (int j = 1; j < k; j++) { // 列的循环次数是上一行元素的个数减1，因为每一行元素个数是 K + 1个，所以这里是K。
            result[k][j] = result[k - 1][j] + result[k - 1][j - 1];
        }
    }
    return result;
}
