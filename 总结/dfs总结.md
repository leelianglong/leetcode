### 题目 生命的游戏
思路：

1、在DFS中需要访问4个方向时，可以是direction[4][2] = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};归一化处理。

2、 把A[m][n] 这样的二维坐标转换成 一维坐标的小技巧  对于 [i][j]   对应的一维坐标是 i * n + j.

### 代码
```
/*
下面介绍一种二维数组可以避免边界点的算法，通过定义direction来处理。
下面的题目是生命的游戏
*/
int** gameoflife(int** board, int boardSize, int* boardColumSize)
{
    int row;
    int column;
    int cnt;
    for (row = 0; row < boardSize; row++) {
        for (column = 0; column < *boardColumnSize; column++) {
            int direction[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0, 1},
                                   {1, 1}, {1, 0}, {1, -1}, {0, -1}
                                  };
            for (int k = 0; k < 8; k++) {
                int x = row + direction[k][0];
                int y = column + direction[1];
                if (x >= 0 && x < row   &&  y >= 0 && y < column && board[row][column] == 1) {
                    cnt++;
                }
            }
            if((board[row][column] & 0x1 == 1) && (cnt == 2 || cnt == 3) ||
                board[row][column] & 0x1 == 0) && (cnt == 3)) {
                board[row][column] += 2; // 这里加2的原因就是把高位用作变化后的位置，低位保持不变用来计算
            }
        }
    }
    for (row = 0; row < boardSize; row++) {
        for(column = 0; column < *boardSize; column++) {
            board[row][column] >>= 1;
        }
    }
}
```

### 题目 目标和

思路：

1、使用dfs，需要构造的参数有： nums, numssize ,target这3个是必须的，另外，我们要遍历序列，那么需要一个变量来标记遍历到哪里 所以需要curpos. 另外

每执行一步，需要记录当前的和. 还有题目要求有多少种组合方式，所以还需要一个变量来记录找到的组合个数，由于是出参，所以需要设置成指针型

2、我们每一步有2种做法，即在cursum上加上当前的遍历的数值，或者在cursum上减去当前遍历的数值。

注意：在边界条件判断的地方使用 curPos == numssize 而不是 curPos == numssize - 1, 是因为该算法是以 curPos + 1 作为下次比较的curPos的，所以这里应该是前者。


### 代码
```
void dfs(int* nums, int numsSize, int curPos, int curSum, int target, int* counter)
{
    if (curPos == (numsSize)) {
        if (target == curSum) {
            (*counter)++;
        }
    } else {
        dfs(nums, numsSize, curPos + 1, curSum + nums[curPos], target, counter);
        dfs(nums, numsSize, curPos + 1, curSum - nums[curPos], target, counter);
    }
}

int findTargetSumWays(int* nums, int numsSize, int S){
    if (numsSize <= 0) {
        return -1;
    }
    int counter = 0;
    dfs(nums, numsSize, 0, 0, S, &counter);
    return counter;
}
```

### 题目 leetcode 695 岛屿的最大面积

1. 实际上就是计算在一起的 1 的个数， 使用一个变量counter来记录访问过的1的数量。
2. 遇到1就对其上下左右进行搜索，直到搜索到边界， 每搜索到一个1，就把记录个数count增加并且标记访问过vist置1。
3. 使用一个标记位visit记录是否访问过，否则会出现无限次循环访问导致leetcode的堆栈溢出。
4. 对所有点进行遍历，遇到1，调用上面的dfs.注意counter从1开始，因为遇到1，才调用dfs的。

这里是最简单最典型的dfs题目
```
int row;
int colum;
int dirction[4][2] = {{1,0}, {0,1}, {-1,0}, {0, -1}};
void dfs(int** grid, int x, int y, int* counter, int* visit)
{
    for (int idx = 0; idx < 4; idx++) {
        int xx = x + dirction[idx][0];
        int yy = y + dirction[idx][1];
        if (xx < 0 || yy < 0 || xx > row - 1 || yy > colum - 1) {
            continue;
        }
        if (grid[xx][yy] == 0) {
            continue;
        }
        if (visit[xx * colum + yy] == 1) {
            continue;
        }
        visit[xx * colum + yy] = 1;
        (*counter)++;
        dfs(grid, xx, yy, counter, visit);
    }
}

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize){
    if (gridSize <= 0) {
        return 0;
    }
    int res = INT_MIN;
    row = gridSize;
    colum = *gridColSize;
    int counter;
    int* visit = (int*)malloc(sizeof(int) * (row * colum));
    memset(visit, 0, sizeof(int) * (row * colum));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < colum; j++) {
            if (grid[i][j] == 1) {
                visit[i * colum + j] = 1;
                counter = 1;
                dfs(grid, i, j, &counter, visit);
                res = res > counter ? res : counter;
            }
        }
    }
    return res == INT_MIN ? 0 : res;
}
```
