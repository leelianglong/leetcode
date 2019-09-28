#include <stdio.h>
#include <stdlib.h>


void BubbleSort(int* data, int size)
{
    int i;
    int j;
    int tmp;

    for (i = 0; i < size; i++) {
        for (j = i; j < size; j++) {
            if (data[i] > data[j]) {
                tmp = data[i];
                data[i] = data[j];
                data[j] = tmp;
            }
        }
    }
}

int cmp(const void* a, const void* b)
{
	return *(int*)(a) - *(int*)(b);
} 

int findContentChildren(int* g, int gSize, int* s, int sSize){
    int i;
    int j;
    int result = 0;
	int tmp = 0;

    if (g == NULL || s == NULL) {
        return 0;
    }

	BubbleSort(g, gSize);
    BubbleSort(s, sSize);

    for (i = 0; i < sSize; i++) { // 饼干
        for (j = tmp; j < gSize; j++) { // 小孩
            if (s[i] >= g[j]) {
              result++;  
              tmp = j + 1; // 该下一个小孩分饼干
              break;
            } else {
				tmp = j; //要找更大的饼干,已经分过的小孩就不要再分
                break;
            }
        }
		if (j == gSize) { //孩子分完了
			return result;
		}
    }
	return result;
}


int main(void)
{
    int data[10] = {9,8,7,7,5,4,3,3,1,0};
    int i;
    int child[3] = {1,2,3};
    int cake[1] = {3};
    int result;

    //BubbleSort(data, 10);
    qsort(data,10,sizeof(data[0]),cmp);
    for (i = 0; i < 10; i++) {
        printf("%4d", data[i]);
    }
    result = findContentChildren(child,2,cake,3);
    printf("\r\nfinally=%d\r\n", result);
}



/*
井字游戏，下面3种状态不合格：
初始的棋盘上O的个数不等于X的个数，或者O的个数不等于X-1；
棋盘上O的个数等于X - 1（轮到O下），但是O还没下棋，此时O已经赢了；
棋盘上O的个数等于X（轮到X下），但是X还没下棋，此时X已经赢了；

class Solution:
    def validTicTacToe(self, board):
        """
        :type board: List[str]
        :rtype: bool
        """
        xCount, oCount = 0, 0
        for i in range(3):
            for j in range(3):
                if board[i][j] == 'O':
                    oCount += 1
                elif board[i][j] == 'X':
                    xCount += 1
        if oCount != xCount and oCount != xCount - 1: return False
        if oCount != xCount and self.win(board, 'O'): return False
        if oCount != xCount - 1 and self.win(board, 'X'): return False
        return True
        
    def win(self, board, P):
        # board is list[str]
        # P is 'X' or 'O' for two players
        for j in range(3):
            if all(board[i][j] == P for i in range(3)): return True
            if all(board[j][i] == P for i in range(3)): return True
        if board[0][0] == board[1][1] == board[2][2] == P: return True
        if board[0][2] == board[1][1] == board[2][0] == P: return True
        return False
————————————————
版权声明：本文为CSDN博主「负雪明烛」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/fuxuemingzhu/article/details/83053972


*/