#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int direct[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int row = 0;
int column = 0;
int length = 0;
bool step(char** board, int x, int y, char* target, int* couter)
{
    if (*couter == length) {
        return true;
    }

    if ((x == row - 1) && (y == column - 1)) {
        return false;
    }

    if (board[x][y] != target[*couter]) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        int xx = x + direct[i][0];
        int yy = y + direct[i][1];

        if (xx < 0 || yy < 0 || xx > row - 1 || yy > column - 1) {
            continue;
        }
        step(board, xx, yy, target, couter);
        (*couter)++;
    }
    return false;
}


bool exist(char** board, int boardSize, int* boardColSize, char * word){
    if (board == NULL || boardColSize == NULL || word == NULL) {
        return false;
    }
    row = boardSize;
    column = *boardColSize;
    int couter = 0;
    length = strlen(word);
    return step(board, 0, 0, word, &couter);
}

int main(void)
{

    system("pause");
}