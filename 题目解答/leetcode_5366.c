#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 逆时针方向
int direction[4][2] = {
    {1,0},  // 右
    {0,1},  // 上
    {-1,0}, // 左
    {0,-1}, // 下
};

// 0表示下， 1表示右，2 表示上，3 表示左， -1 表示不能走
int puzzleDirectLimited[7][4] = { // 总共有6个拼图，是从1开始的，这里设置成7 ，从0开始，把第0个拼图设置成不能走
    {-1, -1, -1, -1}, // 表示0号拼图在4个方向都不能走。
    {-1, 1, -1, 3}, // 表示1号图不能下，能向右走，不能上，可以向左
    {0, -1, 2, -1}, // 表示2号图可以向下，不能向右，可以向上，不能向左。
    {-1, 0, 3, -1},
    {-1, -1, 1, 0},
    {3, 2, -1, -1}, 
    {1, -1, -1, 2},
};

int column = 0;
int row = 0;

bool step(int x, int y, int dir, int** grid)
{
    if (x == row - 1 && y == column - 1 ) {
        return true;
    }
    int xx = x + direction[dir][0];
    int yy = y + direction[dir][1];
    if (xx < 0 || yy < 0 || xx >= row || yy >= column) {
        return false;
    }
    int nextPuzzle = grid[xx][yy];
    if (puzzleDirectLimited[nextPuzzle][dir] != -1) {
        return step(xx, yy, puzzleDirectLimited[nextPuzzle][dir], grid);
    }
    return false;
}

bool hasValidPath(int** grid, int gridSize, int* gridColSize){
    if (grid == NULL || gridColSize == NULL) {
        return false;
    }
    row = gridSize;
    column = *gridColSize;
    int id = grid[0][0];
    int i;
    for (i = 0; i < 4; i++) { // 在4个方向上搜索
        if (puzzleDirectLimited[id][i] != -1) {
            if (step(0, 0, puzzleDirectLimited[id][i], grid)) {
                return true;
            }
        }
    }
    return false;
}



int main(void)
{
    system("pause");
}
