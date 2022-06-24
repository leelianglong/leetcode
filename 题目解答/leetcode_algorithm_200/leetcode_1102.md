### 题目
```
给定一个 m x n 的整数矩阵 grid，返回从 (0,0) 开始到 (m - 1, n - 1) 在四个基本方向上移动的路径的最大 分数 。

一条路径的 分数 是该路径上的最小值。

例如，路径 8 → 4 → 5 → 9 的得分为 4 

输入：grid = [[5,4,5],[1,2,6],[7,4,6]]
输出：4
解释：得分最高的路径用黄色突出显示。
```
### 思路
1.分2步走。第一是获取路径上的最小值；第二是获取所有路径上的最大值
2.在获取路径上的最小值时，是和上次的值进行比较，选择较小的传递下去。
3.在终点选择所有路径中的最大值。
### 代码
```
当前解法超时
int g_res;
int g_R;
int g_C;
int dir[4][2] = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};

void dfs(int** grid, int x, int y, int score, int* vis)
{
    if (x == g_R - 1 && y == g_C - 1) {
        g_res = fmax(g_res, score);
        return;
    }
    for (int i = 0; i < 4; i++) {
        int dx = x + dir[i][0];
        int dy = y + dir[i][1];
        if (dx < 0 || dy < 0 || dx > g_R - 1 || dy > g_C - 1) {
            continue;
        }
        if (vis[dx * g_C + dy] == 1) {
            continue;
        }
        vis[dx * g_C + dy] = 1;
        int newscore = fmin(score, grid[dx][dy]); //每次和上一个值进行比较，选择较小的。
        dfs(grid, dx, dy, newscore, vis);
        vis[dx * g_C + dy] = 0;
    }
}

int maximumMinimumPath(int** grid, int gridSize, int* gridColSize){
    g_res = INT_MIN;
    g_R = gridSize;
    g_C = gridColSize[0];
    int* vis = (int*)calloc(g_R * g_C, sizeof(int));
    vis[0] = 1;
    dfs(grid, 0, 0, grid[0][0], vis);
    return g_res;
}
```
