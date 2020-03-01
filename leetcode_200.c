#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* 该题目求岛屿的数量，所谓岛屿就是它四周被水包围。1 表示陆地，0 表示 水；
* 其实就是求有多少个连通块（里面都是1的）--->也就是计算根节点是1的 数量。
* 使用DFS搜索，题目的搜索方向是水平和垂直4个方向。只要有1就继续搜索，直到遇到水就终止
* 本题只要看1，所以只要访问过的就直接变成0，节省visit 数组(用来保存是否访问）。
*/

void step(char** grid, int x, int y, int xTarget, int yTarget)
{
    int direction[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
    grid[x][y] = '0';
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        int nx = x + direction[i][0];
        int ny = y + direction[i][1];
        if (nx < 0 || nx >= xTarget || ny < 0 || ny >= yTarget) {
            continue;
        }
        if (grid[nx][ny] == '1') {
            step(grid, nx, ny, xTarget, yTarget);           
        }
    }
}

int numIslands(char** grid, int gridSize, int* gridColSize){
    if (grid == NULL || gridSize < 0 || gridColSize == NULL || *gridColSize <= 0) {
        return 0;
    }
    int row = gridSize;
    int column = *gridColSize;
    int i;
    int j;
    int islandNum = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < column; j++) {
            if (grid[i][j] == '1') {
                islandNum++;
                step(grid, i, j, row, column);
            }
        }
    }
    return islandNum;
}

int main(void)
{
    char test[4][5] = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    char** tmp = (char**)malloc(sizeof(char*) * 4);
    int i;
    for (i = 0; i < 4; i++) {
        tmp[i] = (char*)malloc(sizeof(char) * 5);
    }
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            tmp[i][j] = test[i][j];
        }
    }
    int size = 4;
    int columnSize = 5;
    int result = numIslands(tmp, size, &columnSize);
    printf("%d", result);
}