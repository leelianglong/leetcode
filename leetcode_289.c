#include <stdio.h>
#include <stdlib.h>


void gameOfLife(int** board, int boardSize, int* boardColSize){
    if (board == NULL || boardColSize == NULL || *board == NULL || boardSize == 0 || *boardColSize == 0) {
        return; // 注意非法入参的判断，[[]] 这个入参是通过*boardColSize == 0 来过滤的
    }  
    int i;
    if (boardSize == 1) { // 1行
        int* rowTmp = (int*)malloc(sizeof(int) * *boardColSize);
        memset(rowTmp, 0, sizeof(int) * *boardColSize);
        if (board[0][0] == 1) {
            rowTmp[0] = 1;
        }
        if (board[0][*boardColSize - 1] == 1) {
            rowTmp[*boardColSize - 1] = 1;
        }
        for (i = 1; i < *boardColSize - 2; i++) {
            printf("%4d", board[0][i]);
            if (board[0][i] == 1) {
                if ((board[0][i-1] == 1) && (board[0][i+1] == 1)) {
                    rowTmp[i] = 0;
                } else {
                    rowTmp[i] = 1;
                }
            }
        }
        for (i = 0; i < *boardColSize; i++) {
            board[0][i] ^= rowTmp[i];
        }
        return;
    }
    if (*boardColSize == 1) { // 1列
        int* columnTmp = (int*)malloc(sizeof(int) * boardSize);
        memset(columnTmp, 0, sizeof(int) * boardSize);
        if (board[0][0] == 1) {
            columnTmp[0] = 1;
        }
        if (board[boardSize - 1][0] == 1) {
            columnTmp[boardSize - 1] = 1;
        }
        for (i = 1; i < boardSize - 2; i++) {
            if (board[i][0] == 1) {
                if (board[i - 1][0] == 1 && board[i + 1][0] == 1) {
                    columnTmp[i] = 0;
                } else {
                    columnTmp[i] = 1;
                }
            }
        }
        for (i = 0; i < boardSize; i++) {
            board[i][0] ^= columnTmp[i];
        }
        return;
    }
    int** saveChange = (int**)malloc(sizeof(int*) * boardSize);
    for (i = 0; i < boardSize; i++) {
        saveChange[i] = (int*)malloc(sizeof(int) * (*boardColSize));
        memset(saveChange[i], 0, sizeof(int) * (*boardColSize));
    }
    int row;
    int column;
    int sum;
    
    for (row = 0; row < boardSize; row++) {
        for (column = 0; column < *boardColSize; column++) {
            sum = 0;
            if (row - 1 >= 0 && column - 1 >= 0&& row < boardSize - 1 && column < *boardColSize - 1) {
                sum += board[row - 1][column - 1];
                sum += board[row][column - 1];
                sum += board[row + 1][column - 1];
                sum += board[row + 1][column];
                sum += board[row + 1][column + 1];
                sum += board[row][column + 1];
                sum += board[row - 1][column + 1];
                sum += board[row - 1][column];
            } else if (row == 0 && column == 0) { // 左上点
                sum += board[1][0];
                sum += board[0][1];
                sum += board[1][1];
            } else if (row == boardSize - 1 && column == 0) { // 左下点
                sum += board[row - 1][0];
                sum += board[row][1];
                sum += board[row - 1][1];
            } else if (row == boardSize - 1 && column == *boardColSize - 1) { // 右下点
                sum += board[row][column - 1];
                sum += board[row - 1][column - 1];
                sum += board[row - 1][column];
            } else if (row == 0 && column == *boardColSize - 1) { // 右上点
                sum += board[row][column - 1];
                sum += board[row + 1][column - 1];
                sum += board[row + 1][column];    
            } else if (column == 0) { // 左边
                sum += board[row - 1][column];
                sum += board[row - 1][column + 1];
                sum += board[row][column + 1];
                sum += board[row + 1][column + 1];
                sum += board[row + 1][column];
            } else if (row == boardSize - 1) { // 下边
                sum += board[row][column - 1];
                sum += board[row - 1][column - 1];
                sum += board[row - 1][column];  
                sum += board[row - 1][column + 1];
                sum += board[row][column + 1];
            } else if (column == *boardColSize - 1) { // 右边
                sum += board[row - 1][column];
                sum += board[row - 1][column - 1];
                sum += board[row][column - 1];  
                sum += board[row + 1][column - 1];
                sum += board[row + 1][column];
            } else if (row == 0) { // 上边
                sum += board[row][column - 1];
                sum += board[row][column + 1];
                sum += board[row + 1][column];
                sum += board[row + 1][column + 1];   
                sum += board[row + 1][column - 1];  
            }

            if (board[row][column] == 0) {
                if (sum == 3) {
                    saveChange[row][column] = 1; // 变化
                } else {
                    saveChange[row][column] = 0;
                }
            } else {
                if (sum == 2 || sum == 3) {
                    saveChange[row][column] = 0; 
                } else {
                    saveChange[row][column] = 1;// 变化
                }
            }
        }
    }
    for (row = 0; row < boardSize; row++) {
        for (column = 0; column < *boardColSize; column++) {
            printf("%4d", saveChange[row][column]);
        }
        printf("\n");
    }
    for (row = 0; row < boardSize; row++) {
        for (column = 0; column < *boardColSize; column++){
            board[row][column] ^= saveChange[row][column];
        }
    }
}


int main(void)
{
    int test[6][1] = {
        {1},
        {1},
        {1},
        {0},
        {0},
        {1},
    };
    int i;
    int j;
    int column = 1;
    int** tmp = (int**)malloc(6 * sizeof(int*));
    for (i = 0; i < 6; i++) {
        tmp[i] = (int*)malloc(1 * sizeof(int));
        memset(tmp[i], 0, sizeof(int) * 1);
    }
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 1; j++) {
            tmp[i][j] = test[i][j];
        }
    }
    gameOfLife(tmp, 6, &column);
    printf("\r\nresult:\r\n");
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            printf("%4d", tmp[i][j]);
        }
        printf("\n");
    } 
    system("pause");

}
