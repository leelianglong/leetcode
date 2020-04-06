int direct[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

int row = 0;
int column = 0;
int length = 0;

bool step(char** board, int x, int y, char* target, int couter)
{
    bool result = false;
    if (couter == length - 1 && target[couter] == board[x][y]) {
        return true;
    }

    if (target[couter] == board[x][y]) {
        char c = board[x][y]; // 起初使用visit数组来表示访问，定义成全局数组后，每次搜索时需要清零，否则有有影响。但是这样会超时，所以就在原地修改
        board[x][y] = ' ';// 注意这里是搜索一个字符串，是需要回溯的，需要知道上次访问的是哪个字符，当前的字符是否访问过。
        for (int i = 0; i < 4; i++) {
            int xx = x + direct[i][0];
            int yy = y + direct[i][1];

            if (xx < 0 || yy < 0 || xx > row - 1 || yy > column - 1) {
                continue; // 这里某一个方向出错，不能直接返回false，还需要搜索其他方向。
            }
            if ((board[xx][yy] == target[couter + 1]) && (board[xx][yy] != ' ')) {
                result = step(board, xx, yy, target, couter + 1); // 注意这里counter的增加是要匹配后才增加的，不是随便一个就增加的。
                if (result) {
                    return result;
                }
            }
        }
        board[x][y] = c;        
    }
    return false;
}

bool exist(char** board, int boardSize, int* boardColSize, char * word){
    int i;
    int j;

    row = boardSize;
    column = boardColSize[0];
    int counter = 0;
    length = strlen(word);    
    for (i = 0; i < boardSize; i++) {
        for (j = 0; j < boardColSize[0]; j++) {
            if (board[i][j] == word[0] && step(board, i, j, word, counter)){
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
