### 题目
```
你有一个包含 n 个节点的图。给定一个整数 n 和一个数组 edges ，其中 edges[i] = [ai, bi] 表示图中 ai 和 bi 之间有一条边。

返回 图中已连接分量的数目 。

输入: n = 5, edges = [[0, 1], [1, 2], [3, 4]]
输出: 2

输入: n = 5, edges = [[0,1], [1,2], [2,3], [3,4]]
输出:  1

```

### 思路
1. 简单的并查集题目

### 代码
```
typedef struct {
    int* data;
    int cnt;
} UF;

UF* init(int n)
{
    UF* obj = (UF*)calloc(1, sizeof(UF));
    obj->data = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        obj->data[i] = i;
    }
    obj->cnt = n;
    return obj;
}

int find(UF* obj, int x)
{
    while (x != obj->data[x]) {
        x = obj->data[x];
    }
    return x;
}

void combine(UF* obj, int x, int y)
{
    int rootX = find(obj, x);
    int rootY = find(obj, y);
    if (rootX == rootY) {
        return;
    }
    obj->data[rootY] = rootX;
    obj->cnt--;
}

bool isConnected(UF* obj, int x, int y)
{
    int rootX = find(obj, x);
    int rootY = find(obj, y);
    return rootX == rootY;
}

int countComponents(int n, int** edges, int edgesSize, int* edgesColSize){
    UF* obj = init(n);
    for (int i = 0; i < edgesSize; i++) {
        combine(obj, edges[i][0], edges[i][1]);
    }
    return obj->cnt;
}
```
