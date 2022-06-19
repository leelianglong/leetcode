### 题目
```
想象一下你是个城市基建规划者，地图上有 n 座城市，它们按以 1 到 n 的次序编号。

给你整数 n 和一个数组 conections，其中 connections[i] = [xi, yi, costi] 表示将城市 xi 和城市 yi 连接所要的costi（连接是双向的）。

返回连接所有城市的最低成本，每对城市之间至少有一条路径。如果无法连接所有 n 个城市，返回 -1

该 最小成本 应该是所用全部连接成本的总和。


输入：n = 3, conections = [[1,2,5],[1,3,6],[2,3,1]]
输出：6
解释：选出任意 2 条边都可以连接所有城市，我们从中选取成本最小的 2 条。

输入：n = 4, conections = [[1,2,3],[3,4,4]]
输出：-1
解释：即使连通所有的边，也无法连接所有城市。
```

### 思路
1. 要求连接所有城市的最小花费，那么我们就应该从最小的花费线路上选起。所以排序是必然选择
2. 要联通所有城市，那么可以考虑并查集，确认是否能够联通所有城市
3. 在计算开销时，要在遍历线路过程中计算，并且是把能够添加到联通分量中的线路添加进来。

### 代码
```
int cmp(const void* a, const void* b)
{
    int* aa = *(int**)a;
    int* bb = *(int**)b;
    return aa[2] - bb[2];
}
typedef struct {
    int* buff;
    int cnt;
} UF;

UF* init(int n)
{
    UF* obj = (UF*)calloc(1, sizeof(UF));
    obj->buff = (int*)calloc(n + 1, sizeof(int));
    for (int i = 1; i < n; i++) {
        obj->buff[i] = i;
    }
    obj->cnt = n;
    return obj;
}

int find(UF* obj, int x)
{
    while (x != obj->buff[x]) {
        x = obj->buff[x];
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
    obj->buff[rootX] = rootY;
    obj->cnt--;
}

int minimumCost(int n, int** connections, int connectionsSize, int* connectionsColSize){
    qsort(connections, connectionsSize, sizeof(connections[0]), cmp);
    UF* obj = init(n);
    long long int sum = 0;
    for (int i = 0; i < connectionsSize; i++) {
        int rootX = find(obj, connections[i][0]);
        int rootY = find(obj, connections[i][1]);
        if (rootX != rootY) {
            sum += connections[i][2];
            obj->buff[rootX] = rootY;
            obj->cnt--;
        }
    }
    return obj->cnt == 1 ? sum : -1;
}
```
