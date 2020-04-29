/*
* 该题目的思路是：把X包围的O使用X填充，我们先把要填充的部分先确定下来。题目提示任何在边界上的O都不会被填充，所以我们转而先把边界上的O找出来，使用
* 其他的字符填充。那么剩下的O就是可以填充的了。也就确定了填充范围。
* 怎么定界边界上的O，题目提示在垂直和水平方向上相邻，则认为它们相连，那么就搜索一下，4个边界上相连的O,把它们先设置成其他字符。
* 搜索完毕后，再全范围中搜索到O就用X填充，然后再把其他字符恢复成O，就达到题意。
* 提示：遇到问题想想转换途径来解决。
*/


int g_row = 0;
int g_column = 0;

void step(char** board, int i, int j)
{
    int direct[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
    if (i < 0 || i > g_row - 1 || j < 0 || j > g_column - 1 || board[i][j] != 'O') {
        return;
    }
    //printf("\nenter %d %d\n", i, j);
    board[i][j] = '#';
    for (int k = 0; k < 4; k++) {
        step(board, i + direct[k][0], j + direct[k][1]);
    }
}

void solve(char** board, int boardSize, int* boardColSize){
    if (boardSize < 3) {
        return;
    }
    g_row = boardSize;
    g_column = boardColSize[0];
    //printf("\n%d %d\n", g_row, g_column);
    for (int i = 0; i < g_row; i++) {
        step(board, i, 0);
        step(board, i, g_column - 1);
    }

    for (int j = 0; j < g_column; j++) {
        step(board, 0, j);
        step(board, g_row - 1, j);
    }
    #if 0
    for (int i = 0; i < g_row; i++) {
        for (int j = 0; j < g_column; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
    #endif
    for (int i = 0; i < g_row; i++) {
        for (int j = 0; j < g_column; j++) {
            if (board[i][j] == 'O') {
                board[i][j] = 'X';
            } else if (board[i][j] == '#'){
                board[i][j] = 'O';
            }
        }
    }
}


/*****另一种解法，使用并查集*****/
typedef struct {
    int* weight;
    int* parent;
    int counter;
} UFStruct;

UFStruct* UFInit(int n)
{
    UFStruct* tmp = (UFStruct*)malloc(sizeof(UFStruct));
    tmp->parent = (int*)malloc(sizeof(int) * n);
    tmp->weight = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        tmp->parent[i] = i;
        tmp->weight[i] = 1; // 初始化时每个节点的子树都是1，每个节点的父节点是自己
    }
    tmp->counter = n;
    return tmp;
}

// 用来查找x节点的根节点
int find (UFStruct* data, int x)
{
    while (data->parent[x] != x) {
        data->parent[x] = data->parent[data->parent[x]]; // 路径压缩
        x = data->parent[x];
    }
    return x;
}

// 把2个节点p  和 q 连通
void union_element(UFStruct* data, int p, int q)
{
    int rootP = find(data, p);
    int rootQ = find(data, q);

    if (rootP == rootQ) { // 节点p和q的根节点一样，他们必然连通
        return;
    }

    if (data->weight[rootP] > data->weight[rootQ]) {
        data->parent[rootQ] = rootP;
        data->weight[rootP] += rootP;
    } else {
        data->parent[rootP] = rootQ;
        data->weight[rootQ] += data->weight[rootP];
    }
    data->counter--;
}

bool isConnected(UFStruct* data, int p, int q)
{
    int rootP = find(data, p);
    int rootQ = find(data, q);
    return rootP == rootQ;
}

void solve(char** board, int boardSize, int* boardColSize)
{
    if (boardSize < 3) {
        return;
    }
    int row = boardSize;
    int column = boardColSize[0];
    UFStruct* save = UFInit(row * column + 1); //这里存储矩阵中的所有元素，另外在存储一个多余dummy节点，它是所有不能被包围的节点的父节点。
    int dummy = row * column;

    // 将首列和最后一列的o 和 dummy相连起来。因为它们不可能被包围。
    for (int i = 0; i < row; i++) {
        if (board[i][0] == 'O') {
            union_element(save, i * column, dummy); // 这里连同的坐标
        }
        if (board[i][column - 1] == 'O') {
            union_element(save, i * column + column - 1, dummy);
        }
    }

    // 将首行和最后一行的O和dummy相连起来，它们不可能被包围
    for (int i = 0; i < column; i++) {
        if (board[0][i] == 'O') {
            union_element(save, i, dummy);
        }
        if (board[row - 1][i] == 'O') {
            union_element(save, (row - 1) * column + i, dummy);
        }
    }

    int direct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < column - 1; j++) { // 把矩阵中间O的元素都连通起来,这里从1开始结束也是行、列 - 1的原因是，前面已经计算过4周了
            if (board[i][j] == 'O') {
                for (int k = 0; k < 4; k++) {
                    int dx = i + direct[k][0];
                    int dy = j + direct[k][1];
                    if (board[dx][dy] == 'O') {
                        union_element(save, i * column + j, dx * column + dy);
                    }
                }
            }
        }
    }
    // 所有不和dummy向连同的O都要被替换成X
    for (int i = 1; i < row - 1; i++) {
        for (int j = 1; j < column - 1; j++) {
            if (!isConnected(save, i * column + j, dummy)) {
                board[i][j] = 'X';
            }
        }
    }
}

