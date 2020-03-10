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

    int* degree = (int*)malloc(sizeof(int) * n); // ÿ���ڵ�Ķ�
    memset(degree, 0, sizeof(int) * n);

    int* queue = (int*)malloc(sizeof(int) * n); // ���ڴ洢����ֵ
    memset(queue, 0, sizeof(int) * n);

    int* colSize = (int*)malloc(sizeof(int) * n);
    memset(colSize, 0, sizeof(int) * n); // ���ڴ洢ÿ���ߵĴ�С

    // ��ͼ�Ĺ���
    for (i = 0; i < edgesSize; i++) {
        graph[edges[i][0]][degree[edges[i][0]]] = edges[i][1];
        graph[edges[i][1]][degree[edges[i][1]]] = edges[i][0];
        printf("\r\n %2d %2d %2d\r\n", edges[i][0], degree[edges[i][0]], graph[edges[i][0]][degree[edges[i][0]]]);
        printf("\r\n %2d %2d %2d\r\n", edges[i][1], degree[edges[i][1]], graph[edges[i][1]][degree[edges[i][1]]]);        
        degree[edges[i][0]]++; // ��2�˵Ķ���������
        degree[edges[i][1]]++; 
        graph[edges[i][0]] = realloc(graph[edges[i][0]], sizeof(int) * (degree[edges[i][0]] + 1)); //�ö��㻹��û�������ı�
        graph[edges[i][1]] = realloc(graph[edges[i][1]], sizeof(int) * (degree[edges[i][1]] + 1));
    }
    int tail = 0;
    for (i = 0; i < n; i++) {
        printf("\r\n%2d\r\n", degree[i]);
        colSize[i] = degree[i]; // �ȱ�ʾ�ö����м�����
        if (degree[i] == 1) {
            queue[tail] = i;// �ѵ�i���������
            printf("\r\%2d\r\n", queue[tail]);
            tail++; // ��Ӳ���
        }
    }
    printf("\r\ntail=%d\r\n", tail);
    int curNodeCounter = n;
    int last = 0;
    int head = 0;
    int node;
    int nodeSize;
    while (curNodeCounter > 2) { // ����������Ҫ��2���㣬�������һ������
        last = tail;
        curNodeCounter -= (tail - head);
        while (head < last) { // ���Ѿ���ӵĳ��ӡ�������tail��Ԫ�ء�
            node = queue[head]; // queue�д洢���ǵڼ����ڵ�
            nodeSize = colSize[node]; // colSize�д洢����ÿ���ڵ��м����ߡ�
            for (i = 0; i < nodeSize; i++) {
                if (degree[graph[node][i]] > 0) {
                    degree[graph[node][i]]--;
                }
                if (degree[graph[node][i]] == 1) { // �Ѷ�Ϊ1�Ķ�����ӡ�
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
        res[i] = queue[head]; // �Ѷ����л�ʣ�µ�Ԫ���ó���
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