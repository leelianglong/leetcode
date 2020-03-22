#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_LENGTH      20000
#define MAX(a, b)         ((a) > (b) ? (a) : (b))
typedef int StackElement;
typedef struct STNode {
    int top;
    StackElement data[STACK_LENGTH];
} StackNode, *LinkStack;


int InitStack(LinkStack *ls) {
    int i;
    if (ls == NULL) {
        return false;
    }
    (*ls) = (LinkStack) malloc(sizeof(StackNode));
    for (i = 0; i < STACK_LENGTH; i++) {
        (*ls)->data[i] = 0;
    }
    (*ls)->top = -1;
    return true;
}

int PushStack(LinkStack *ls, StackElement data) {
    if (ls == NULL) {
        return false;
    }
    if ((*ls)->top >= STACK_LENGTH - 1) {
        return false;
    }
    (*ls)->top++;
    (*ls)->data[(*ls)->top] = data;
    return true;
}

int PopStack(LinkStack *ls) {
    if (ls == NULL) {
        return false;
    }
    if ((*ls)->top < 0) {
        return false;
    }
    int data = (*ls)->data[(*ls)->top];
    (*ls)->top--;
    return data;
}

int PopTop(LinkStack*ls) {
    if (ls == NULL) {
        return false;
    }
    if ((*ls)->top < 0) {
        return false;
    }
    int data = (*ls)->data[(*ls)->top];
    return data;
}

bool CheckStackEmpty(LinkStack ls) {
    return ls->top == -1 ? 1 : 0;
}

int GetStackDepenth(LinkStack ls) {
    return ls == NULL ? 0 : ls->top + 1;
}



int largestRectangleArea(int* heights, int heightsSize){
    LinkStack ls;
    int maxArea = 0;
    int position = 0;

    InitStack(&ls);
    while(position < heightsSize) {
        if (CheckStackEmpty(ls)) {
            PushStack(&ls, position); // 首先把0入栈，解决最后一个矩形也计算在内的问题
            position++;
        } else {
            if (heights[position] >= heights[PopTop(&ls)]) { // 如果当前元素比栈顶元素更大时，该元素入栈。
                PushStack(&ls, position);
                position++;
            } else {   // 如果当前元素比栈顶元素更小时，出栈进行计算。
                int height = heights[PopTop(&ls)];
                PopStack(&ls);
                int rPos = position;
                int lPos = CheckStackEmpty(ls) ? -1 : PopTop(&ls);
                maxArea = MAX(maxArea, height * (rPos - lPos - 1));
            }
        }
    }

    while (!CheckStackEmpty(ls)) {
        int height = heights[PopTop(&ls)];
        PopStack(&ls);
        int rPos = position;
        int lPos = CheckStackEmpty(ls) ? -1 : PopTop(&ls);
        maxArea = MAX(maxArea, height * (rPos - lPos - 1));
    }
    return maxArea;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize){
    if (matrix == NULL || matrixSize <= 0 || matrixColSize == NULL 
        || *matrixColSize <= 0) { // 注意二维指针的判断，不要判断 *matrix, 如果输入[] 或者 [[]], 这里都会报错。访问空指针。
        return 0;
    }
    int maxArea = 0;
    int row;
    int column;
    int* tmp = (int*)malloc(sizeof(int) * (*matrixColSize));
    memset(tmp, 0, sizeof(int) * (*matrixColSize));
    for (row = 0; row < matrixSize; row++) {
        for (column = 0; column < *matrixColSize; column++) {
            #if 1
            if (matrix[row][column] == '1') {
                tmp[column]++;
            } else {
                tmp[column]= 0;
            }
            #endif
            printf("%4d ", tmp[column]);
        }
        printf("\n");
        maxArea = MAX(maxArea, largestRectangleArea(tmp, (*matrixColSize)));
        printf("\nmaxArea = %d\n", maxArea);
    }
    return maxArea;
}

int main() {
    char test[4][5] = {  
        {0x31,0x30,0x31,0x30,0x30},
        {0x31,0x30,0x31,0x31,0x31},
        {0x31,0x31,0x31,0x31,0x31},
        {0x31,0x30,0x30,0x31,0x30}
    };
    int i;
    int j;
    char** tmp = (int**)malloc(sizeof(char*) * 4);
    for (i = 0; i < 4; i++) {
        tmp[i] = (char*)malloc(sizeof(char) * 5);
        memset(tmp[i], 0, sizeof(char) * 5);
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            tmp[i][j] = test[i][j];
            printf("%4d", tmp[i][j]);
        }
        printf("\n");
    }
    int column = 5;
    int result = maximalRectangle(tmp, 4, &column);
    printf("result = %u\n", result);
    system("pause");
    return 0;
}