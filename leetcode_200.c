#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* ����Ŀ�������������ν������������ܱ�ˮ��Χ��1 ��ʾ½�أ�0 ��ʾ ˮ��
* ��ʵ�������ж��ٸ���ͨ�飨���涼��1�ģ�--->Ҳ���Ǽ�����ڵ���1�� ������
* ʹ��DFS��������Ŀ������������ˮƽ�ʹ�ֱ4������ֻҪ��1�ͼ���������ֱ������ˮ����ֹ
* ����ֻҪ��1������ֻҪ���ʹ��ľ�ֱ�ӱ��0����ʡvisit ����(���������Ƿ���ʣ���
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