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
