#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_LENGTH    1024
typedef struct {
    int index[STACK_LENGTH];
    int top;
} BracketsStack, *LinkStack;

int InitStack(LinkStack *ls)
{
    int i;
    if (ls == NULL) {
        return 0;
    }
    (*ls) = (LinkStack)malloc(sizeof(BracketsStack));
    for (i = 0; i < STACK_LENGTH; i++) {
        (*ls)->index[i] = 0;
    }
    (*ls)->top = -1;
    return 0;
}

int PushStack(LinkStack *ls, int index)
{
    if (ls == NULL) {
        return 0;
    }
    if ((*ls)->top >= STACK_LENGTH - 1) {
        return 0;
    }
    (*ls)->top++;
    (*ls)->index[(*ls)->top] = index;
    return 1;
}

int PopStack(LinkStack *ls, int *index)
{
    if (ls == NULL) {
        return 0;
    }
    if ((*ls)->top < 0) {
        return 0;
    }
    *index = (*ls)->index[(*ls)->top];
    (*ls)->top--;
    return 1;
}

int CheckStackEmpty(LinkStack ls)
{
    return ls->top == -1 ? 1 : 0;
}

int GetStackDepenth(LinkStack ls) 
{
    return  ls == NULL ? 0 : ls->top + 1;
}

char * minRemoveToMakeValid(char * s){
    if (s == NULL) {
        return NULL;
    }
    LinkStack ls;
    InitStack(&ls);
    int length = strlen(s);
    char* res = (char*)malloc(sizeof(char) * length + 1); // 这里要多分配一个。
    memset(res, 0, sizeof(char) * length + 1);
    int counter = 0;
    int stringIndex = 0;
    while(*(s + stringIndex) != '\0') {
        if (*(s + stringIndex) != '(' && *(s + stringIndex) != ')') {
            res[counter++] = *(s + stringIndex);
            stringIndex++;
            continue;
        }

        if (*(s + stringIndex) == ')') {
            if (CheckStackEmpty(ls)) { // 栈为空，可以直接删除
                stringIndex++;
                continue;
            } else { // 栈不为空，出栈
                int outIndex = 0;
                PopStack(&ls, &outIndex);
                res[counter++] = *(s + stringIndex);
                stringIndex++;
            }
        } else {
            PushStack(&ls, counter);//stringIndex);
            res[counter++] = *(s + stringIndex);
            stringIndex++;
        }
    }
    if (CheckStackEmpty(ls)) {
        res[counter] = '\0';
        return res;
    }
    /*
    * 前不部分已经把字符串过滤完了，res中的是字符和 多余的（ ，下面准备删除多余的（，
    * 方法如下：
    * 1）因为前面栈中已经存储了'('的位置（该位置一定要是res中的位置，不能是原来序列中的位置）
    * 2）取出该位置
    * 3）把res复制到一个临时变量中存储
    * 4）在临时变量中，把2）中位置上填充一个特定字符
    * 5）在申请一个最终返回的空间，遍历4）中的临时变量，跳过特定字符。
    * 6）返回
    */
    res[counter] = '\0';
    char* finalResult = (char*)malloc(sizeof(char) * counter + 1);
    memset(finalResult, 0, sizeof(char) * counter + 1);
    int finnalCounter = 0;
    if (CheckStackEmpty(ls) != 1) {
        int left = GetStackDepenth(ls);
        int* saveLeftBrackets = (int*)malloc(sizeof(int) * left);
        memset(saveLeftBrackets, 0, sizeof(int) * left);
        printf("left = %d", left);
        for (int i = 0; i < left; i++) {
            PopStack(&ls, (saveLeftBrackets + i));
        }
        char* tmpSaveStr = (char*)malloc(sizeof(char) * counter + 1);
        memset(tmpSaveStr, 0, sizeof(char) * counter + 1);
        memcpy(tmpSaveStr, res, counter + 1);
        for (int j = 0; j < left; j++) {
            tmpSaveStr[saveLeftBrackets[j]] = 'A';
        }
        for (int k = 0; k <= counter; k++) {
            if (tmpSaveStr[k] != 'A') {
                finalResult[finnalCounter++] = tmpSaveStr[k];
            }
        }
    }
    finalResult[finnalCounter] = '\0';
    return finalResult;
}



int main(void)
{
    char test[] = {"(a(b(c)d)"};
    char* result = minRemoveToMakeValid(test);
    printf("\r\n%s", result);
    system("pause");
}