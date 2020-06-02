/*
* 当前题目使用递归，下一步搜索只有2种情况，即基于当前节点序号值 加上 当前节点值  或者 减去 当前节点值；
* 思路就是先判断一些特殊情况，最后递归调用 2种搜索路径
*/

int step(int* arr, int arrSize, int start, int* visited)
{
    if (start > arrSize -1 || start < 0) {
        return 0;
    }
    if (visited[start] == 1) {
        return 0;
    }
    if (arr[start] == 0) {
        return 1;
    }
    visited[start] = 1;
    return step(arr, arrSize, start + arr[start], visited) || step(arr, arrSize, start - arr[start], visited);
}

int canReach(int* arr, int arrSize, int start){
    if (arr == NULL || arrSize <= 0) {
        return 0;
    }
    int* visited = (int*)malloc(sizeof(int) * arrSize);
    memset(visited, 0, sizeof(int) * arrSize);
    return step(arr, arrSize, start, visited);
}

int main() {
    int test[] = {4,2,3,0,3,1,2};
    int start = 5;
    int result = canReach(test, sizeof(test) / sizeof(test[0]), start);
    printf("result=%d", result);
    return 0;
}
