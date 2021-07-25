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
5. dfs还要避免走回头路
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

### 题目 leetcode 322  零钱兑换
思路：详见代码注释

### 代码
```
第一种超时
#define MIN(a, b)  ((a) > (b) ? (b) : (a))

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int dfs(int* coins, int coinsSize, int curPos, int amount)
{
    if (coinsSize == 0 || amount == 0) {
        return 0;
    }
    if (curPos < coinsSize && amount > 0) { // 注意这里的剪枝
        int maxCount = amount / coins[curPos]; // 计算要兑换amount所需要的当前coins数组中第curpos个面值的最大个数
        int minCOunt = INT_MAX;
        for (int i = 0; i <= maxCount; i++) { // 这里就是查询分别需要0到maxCount个当前面值和剩余的其他面值能够满足兑换需求的 所有硬币的总数最小值。 对于这种循环方式，前面的排序没有必要
            if (amount >= i * coins[curPos]) {
                int res = dfs(coins, coinsSize, curPos + 1, amount - i * coins[curPos]);
                if (res != -1) {
                    minCOunt = MIN(minCOunt, res + i);
                }
            }
        }
        return minCOunt == INT_MAX ? -1 : minCOunt;
    }
    return -1;
}

int coinChange(int* coins, int coinsSize, int amount){
    if (amount == 0) {
        return 0;
    }
    qsort(coins, coinsSize, sizeof(coins[0]), cmp);
    return dfs(coins, coinsSize, 0, amount);
}


第二种通过剪枝，通过

#define MIN(a, b)  ((a) > (b) ? (b) : (a))

int cmp(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}
int res;
void dfs(int* coins, int coinsSize, int curPos, int amount, int findCnt)
{
    if (amount == 0) { //注意剪枝
        res = MIN(res, findCnt); 
        return;
    }
    if (curPos >= coinsSize) { // 注意剪枝
        return 0;
    }
    int CurCnt = amount / coins[curPos];
    for (int i = CurCnt; i >= 0 && findCnt + i < res; i--) { // 这里倒置循环，就是先获取大面额的。最开始要求对面额倒序排序，另外注意这里的剪枝 findcnt + i < res
        dfs(coins, coinsSize, curPos + 1, amount - i * coins[curPos], findCnt + i);
    }
}

int coinChange(int* coins, int coinsSize, int amount){
    if (amount == 0) {
        return 0;
    }
    res = INT_MAX;
    qsort(coins, coinsSize, sizeof(coins[0]), cmp);
    dfs(coins, coinsSize, 0, amount, 0);
    return res == INT_MAX ? -1 : res;
}

```

### 题目 leetcode 547
思路：
1. 本题虽然是给的二维矩阵，但是要注意，只有n个同学，这里的二维矩阵，仅仅是表示它们直接的是否存在关系。搜索时，在顶层没有必要二维遍历，只需要外面一层从行开始搜索，dfs里面从列开始搜索。
2. 设置访问标记长度每必要是二维矩阵的长度，应该是同学的人数。
3. 朋友圈的个数，就是dfs能遍历的次数。

### 代码
```
int gColumn;
void dfs(int** M, int x, int* visit)
{
    for (int i = 0; i < gColumn; i++) {
        if (M[x][i] == 1 && visit[i] == false) {
            visit[i] = true;
            dfs(M, i, visit);
        }
    }
}

int findCircleNum(int** M, int MSize, int* MColSize){
    if (MSize <= 0) {
        return 0;
    }
    gColumn = MSize;
    int* visit = (int*)malloc(gColumn * sizeof(int));
    memset(visit, 0, sizeof(int) * gColumn);
    int count = 0;
    for (int j = 0; j < gColumn; j++) {
        if (visit[j] == false) {
            dfs(M, j, visit);
            count++;
        }
    }

    return count;
}
```
### leetcode 62
#### 思路
1. 注意2个地方：这个direct 数组取决与坐标系怎么建立， 目的地是右下角，所以坐标系向右表示x正，向下表示Y正； 还有 起始位置设置成（0,0）还是（1,1） 决定 退出的条件不同，当前我取的是(0,0)为起始条件，所以退出条件是下面这样的。
2. 当前题目使用动态规划来做更省时间，dfs是超时的。
#### 代码
```
int direct[2][2] = {{1,0}, {0,1}};
void dfs(int m, int n, int curx, int cury, int* count)
{
    if (curx == m - 1 && cury == n - 1) {
        (*count)++;
        return;
    }
    for (int i = 0; i < 2; i++) {
        int xx = curx + direct[i][0];
        int yy = cury + direct[i][1];
        if (xx >= m || yy >= n || xx < 0 || yy < 0) {
            continue;
        }
        dfs(m, n, xx, yy, count);
    }
}

int uniquePaths(int m, int n){
    int res = 0;
    dfs(m, n, 0, 0, &res);
    return res;
}
```
### leetcode 437
#### 思路
1. 当前题目是说从二叉树的任意节点开始的路径都算，所以存在多重递归。从二叉树的任意节点遍历，路径上的和是target就可以了
2. 当前存在2种递归，一个是计算和的递归； 一个是递归访问原来二叉树的任意节点。
3. 减少函数参数，可以从原来的target中逐步减root->val值来判断是否找到结果。

#### 代码
```
int dfs(struct TreeNode* root, int targetSum)
{
    int cnt = 0;
    if (root == NULL) {
        return 0;
    }
    targetSum -= root->val;
    if (0 == targetSum) {
        cnt++;
    }
    cnt += dfs(root->left, targetSum); 
    cnt += dfs(root->right, targetSum);
    return cnt;
}

int pathSum(struct TreeNode* root, int targetSum){
    if (root == NULL) {
        return 0;
    }
    return dfs(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum);  // 后面2个是对原二叉树的左子树和右子树的遍历。这里的顺序很重要不能交换。后面这2个也不可或缺。
}
```
#### 代码2
1. 这种方法不好，c语言中使用了全局变量。第一个用例使用过了之后，后面这个全局变量不会再被初始化，导致题目解答异常。
```
int g_count = 0;
void dfs(struct TreeNode* root, int* curSum, int targetSum)
{
    if (root == NULL) {
        return;
    }
    if (targetSum == *curSum) {
        //printf("find\n");
        g_count++;
        return;
    }
    (*curSum) += root->val;
    dfs(root->left, curSum, targetSum);
    dfs(root->right, curSum, targetSum);
}

int pathSum(struct TreeNode* root, int targetSum){
    if (root == NULL) {
        return 0;
    }
    int sum = 0;
    //printf("\n val=%d\n", root->val);
    dfs(root, &sum, targetSum);
    pathSum(root->left, targetSum);
    pathSum(root->right, targetSum);
    return g_count; 
}
```

### leetcode 1267
#### 思路
1. 当前题目要求，求同一行或者同一列上的元素。 这个和之前常用的上下左右相邻，不同，不要思维定式。
2. 要求行 和 列2个方向，就用2个for循环，分别遍历
3. 注意避免不能走回头路
4. 注意dfs中有行列2个for循环，如果某个位置上有元素的话，它会被计算2次。

#### 代码
```

int cnt;
void dfs(int** grid, int row, int col, int x, int y, int* vis)
{
    if (x < 0 || y < 0 || x >= row || y >= col) {
        return;
    }
    if (grid[x][y] == 0) {
        return;
    }
    if (vis[x * col + y]) {
        return;
    }
    cnt++;
    vis[x * col + y] = 1;
    for (int i = 0; i < row; i++) {
        dfs(grid, row, col, i, y, vis);
    }

    for (int j = 0; j < col; j++) {
        dfs(grid, row, col, x, j, vis);
    }
}


int countServers(int** grid, int gridSize, int* gridColSize){
    cnt = 0;
    int row = gridSize;
    int col = gridColSize[0];
    int* vis = (int*)malloc(sizeof(int) * row * col);
    memset(vis, 0, sizeof(int) * row * col);

    int res = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == 0) {
                continue;
            }
            cnt = 0;
            dfs(grid, row, col, i, j, vis);
            if (cnt > 1) { // 这里一定要是大于1的，应为要计算行，列 会计算2次。
                res += cnt;
            }
        }
    }
    return res;
}
```

### leetcode 419
#### 思路
1. 常规dfs思路。注意避免走回头路，把无效的X换成. 最后在统计 X的个数。
#### 代码
```
const int direct[4][2] = {{1,0}, {0,1}, {-1,0}, {0, -1}};

void dfs(char** board, int row, int col, int x, int y, int* vis)
{
    for (int i = 0; i < 4; i++) {
        int dx = x + direct[i][0];
        int dy = y + direct[i][1];
        if (dx < 0 || dx >= row || dy < 0 || dy >= col) {
            continue;
        }
        if (board[dx][dy] == '.') {
            continue;
        }
        if (vis[dx * col + dy]) {
            continue;
        }
        vis[dx * col + dy] = 1;
        board[dx][dy] = '.';
        dfs(board, row, col, dx, dy, vis);
    }
}

int countBattleships(char** board, int boardSize, int* boardColSize){
    int row = boardSize;
    int col = boardColSize[0];
    int* vis = (int*)malloc(sizeof(int) * row * col);
    memset(vis, 0, sizeof(int) * row * col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == '.') {
                continue;
            }
            vis[i * col + j] = 1;
            dfs(board, row, col, i,j,vis);
        }
    }
    int res = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'X') {
                res += 1;
            }
        }
    }
    return res;
}
```
#### 迭代一次遍历版本
```
int countBattleships(char** board, int boardSize, int* boardColSize){
    int row = boardSize;
    int col = boardColSize[0];
    int res = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'X' && (i <= 0 || board[i - 1][j] == '.') && (j <=0 || board[i][j - 1] == '.')) { // 左上角为空时，这个就是有效战舰。
                res += 1;
            }
        }
    }
    return res;
}
```
