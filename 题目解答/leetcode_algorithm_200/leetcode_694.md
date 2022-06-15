## 题目
```
给定一个非空 01 二维数组表示的网格，一个岛屿由四连通（上、下、左、右四个方向）的 1 组成，你可以认为网格的四周被海水包围。

请你计算这个网格中共有多少个形状不同的岛屿。两个岛屿被认为是相同的，当且仅当一个岛屿可以通过平移变换（不可以旋转、翻转）和另一个岛屿重合。

 

示例 1：

11000
11000
00011
00011
给定上图，返回结果 1 。

示例 2：

11011
10000
00001
11011
给定上图，返回结果 3 。

注意：

11
1
和

 1
11
是不同的岛屿，因为我们不考虑旋转、翻转操作
```
### 思路
1. 二维矩阵的序列化
### 代码
```
#define LEN 30000
int g_row;
int g_clomun;

struct HashObj {
    char key[LEN];
    int times;
    UT_hash_handle hh;
};

struct HashObj* g_users;

void dfs(int** grid, int x, int y, int dir, char* tmpSave)
{
    if (x < 0 || y < 0 || x >= g_row || y >= g_clomun || grid[x][y] == 0) {
        return ;
    }
    grid[x][y] = 0;
    char tmp[10] = {0};
    sprintf(tmp, "%d,", dir);
    strcat(tmpSave, tmp);
    dfs(grid, x + 1, y, 1, tmpSave);
    dfs(grid, x, y + 1, 2, tmpSave);
    dfs(grid, x - 1, y, 3, tmpSave);
    dfs(grid, x, y - 1, 4, tmpSave);
    sprintf(tmp, "-%d,", dir);
    strcat(tmpSave, tmp);
}

int numDistinctIslands(int** grid, int gridSize, int* gridColSize){
    g_users = NULL;
    g_row = gridSize;
    g_clomun = gridColSize[0];
    for (int i = 0; i < g_row; i++) {
        for (int j = 0; j < g_clomun; j++) {
            if (grid[i][j] == 1) {
                char* tmpSave = (char*)calloc(LEN, sizeof(char));
                dfs(grid, i, j, 666, tmpSave);
                struct HashObj* find;
                HASH_FIND_STR(g_users, tmpSave, find);
                if (find == NULL) {
                    struct HashObj* add = (struct HashObj*)calloc(1, sizeof(struct HashObj));
                    strcpy(add->key, tmpSave);
                    add->times = 1;
                    HASH_ADD_STR(g_users, key, add);
                } else {
                    find->times++;
                }
            }
        }
    }
    int res = HASH_COUNT(g_users);
    struct HashObj* cur, *tmp;
    HASH_ITER(hh, g_users, cur, tmp) {
        HASH_DEL(g_users, cur);
        free(cur);
    }
    return res;
}
```
