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

int main() {
    int test[] = {1,1,5,1};
    int result = largestRectangleArea(test, sizeof(test) / sizeof(test[0]));
    printf("result = %u\n", result);
    return 0;
}
