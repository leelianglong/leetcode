#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* findMinHeightTrees(int n, int** edges, int edgesSize, 
    int* edgesColSize, int* returnSize){
    if (edges == NULL || n <= 0 || edgesColSize == NULL || returnSize == NULL) {
        return NULL;        
    }
    int* res = NULL;
    if (n == 1) {
        res = (int*)malloc(sizeof(int));
        *returnSize = 1;
        res[0] = 0;
        return res;
    }

    int** graph = (int**)malloc(sizeof(int*) * n);
    int i;
    for (i = 0; i < n; i++) {
        graph[i] = (int*)malloc(sizeof(int));
        memset(graph[i], 0, sizeof(int));
    }

    int* degree = (int*)malloc(sizeof(int) * n); // 每个节点的度
    memset(degree, 0, sizeof(int) * n);

    int* queue = (int*)malloc(sizeof(int) * n); // 用于存储顶点值
    memset(queue, 0, sizeof(int) * n);

    int* colSize = (int*)malloc(sizeof(int) * n);
    memset(colSize, 0, sizeof(int) * n); // 用于存储每个边的大小

    // 对图的构造
    for (i = 0; i < edgesSize; i++) {
        graph[edges[i][0]][degree[edges[i][0]]] = edges[i][1];
        graph[edges[i][1]][degree[edges[i][1]]] = edges[i][0];
        printf("\r\n %2d %2d %2d\r\n", edges[i][0], degree[edges[i][0]], graph[edges[i][0]][degree[edges[i][0]]]);
        printf("\r\n %2d %2d %2d\r\n", edges[i][1], degree[edges[i][1]], graph[edges[i][1]][degree[edges[i][1]]]);        
        degree[edges[i][0]]++; // 边2端的顶点数增加
        degree[edges[i][1]]++; 
        graph[edges[i][0]] = realloc(graph[edges[i][0]], sizeof(int) * (degree[edges[i][0]] + 1)); //该顶点还有没有其他的边
        graph[edges[i][1]] = realloc(graph[edges[i][1]], sizeof(int) * (degree[edges[i][1]] + 1));
    }
    int tail = 0;
    for (i = 0; i < n; i++) {
        printf("\r\n%2d\r\n", degree[i]);
        colSize[i] = degree[i]; // 度表示该顶点有几条边
        if (degree[i] == 1) {
            queue[tail] = i;// 把第i个顶点入队
            printf("\r\%2d\r\n", queue[tail]);
            tail++; // 入队操作
        }
    }
    printf("\r\ntail=%d\r\n", tail);
    int curNodeCounter = n;
    int last = 0;
    int head = 0;
    int node;
    int nodeSize;
    while (curNodeCounter > 2) { // 队列中至少要有2个点，才能组成一个树。
        last = tail;
        curNodeCounter -= (tail - head);
        while (head < last) { // 把已经入队的出队。已入了tail个元素。
            node = queue[head]; // queue中存储的是第几个节点
            nodeSize = colSize[node]; // colSize中存储的是每个节点有几条边。
            for (i = 0; i < nodeSize; i++) {
                if (degree[graph[node][i]] > 0) {
                    degree[graph[node][i]]--;
                }
                if (degree[graph[node][i]] == 1) { // 把度为1的顶点入队。
                    queue[tail] = graph[node][i];
                    tail++;
                }
            } 
            head++;
        }
    }
    *returnSize = 0;
    res = (int*)malloc(sizeof(int) * (tail - head));
    i = 0;
    while (head < tail) {
        res[i] = queue[head]; // 把队列中还剩下的元素拿出来
        head++;
        i++;
    }
    *returnSize = i;
    return res;
}

int main(void)
{
    int tmpArr[3][2] = {
        {1,0},
        {1,2},
        {1,3}
    };
    int** edges = (int**)malloc(sizeof(int*) * sizeof(tmpArr) / sizeof(tmpArr[0]));
    int i;
    for (i = 0; i < sizeof(tmpArr) / sizeof(tmpArr[0]); i++) {
        edges[i] = (int*)malloc(sizeof(tmpArr[0]));
        memset(edges[i], 0, sizeof(tmpArr[0]));
    }
    int j;
    for (i = 0; i < sizeof(tmpArr) / sizeof(tmpArr[0]); i++) {
        for (j = 0; j < sizeof(tmpArr) / sizeof(tmpArr[0]); j++) {
            edges[i][j] = tmpArr[i][j];
        }
    }
    int returnSize = 0;
    int colSize = sizeof(tmpArr[0]) / sizeof(tmpArr[0][0]); 
    findMinHeightTrees(4, edges, sizeof(tmpArr) / sizeof(tmpArr[0]), &colSize,
        &returnSize);
    system("pause");
}