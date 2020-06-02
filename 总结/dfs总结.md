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
