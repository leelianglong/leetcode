#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 这种处理方式只能针对没有重复#的情况 */
char* process(char* s)
{
    int i = 0;
    int j = 0;
    char* tmp = (char*)malloc(strlen(s));
    memset(tmp, 0, strlen(s));
    for (i = 0; i < strlen(s); i++) {
        if (s[i] != '#') {
            tmp[j] = s[i];
            j++;
            continue;
        }
        if (j >= 1) {
            tmp[j - 1] = s[i + 1];
        }
        i++;
    }
    return tmp;
}

int backspaceCompare(char * S, char * T){
    char* tmpS = NULL;
    char* tmpT = NULL;
    int result;

    tmpS = process(S);
    tmpT = process(T);
    result = strcmp(tmpS, tmpT);
    return result;
}

/* 使用栈来实现 */
#define MAX_ROW_COLUM   200
typedef char StackElement;
typedef struct STNode
{
    int top;
    StackElement data[MAX_ROW_COLUM];
} StackNode, *LinkStack;

int InitStack(LinkStack *ls)
{
    int i;
    if (ls == NULL)
    {
        return 0;
    }
    (*ls) = (LinkStack)malloc(sizeof(StackNode));
    for (i = 0; i < MAX_ROW_COLUM; i++)
    {
        (*ls)->data[i] = 0;
    }
    (*ls)->top = -1;
    return 0;
}

int PushStack(LinkStack *ls, StackElement data)
{
    if (ls == NULL)
    {
        return 0;
    }
    if ((*ls)->top >= MAX_ROW_COLUM - 1)
    {
        return 0;
    }
    (*ls)->top++;
    (*ls)->data[(*ls)->top] = data;
    return 1;
}

int PopStack(LinkStack *ls, StackElement *data)
{
    if (ls == NULL)
    {
        return 0;
    }
    if ((*ls)->top < 0)
    {
        return 0;
    }
    *data = (*ls)->data[(*ls)->top];
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

int backspaceCompareStack(char * S, char * T){
    LinkStack tmpS = NULL;
    LinkStack tmpT = NULL;
    char tmpCharS = 0;
    char tmpCharT = 0;

    if (S == NULL || T == NULL) {
        return 0;
    }

    InitStack(&tmpS);
    InitStack(&tmpT);
    while(*S) {
        if (*S != '#') {
            PushStack(&tmpS, *S);
        } else if (*S == '#' && GetStackDepenth(tmpS) != 0) {
            PopStack(&tmpS, &tmpCharS);
        }
        S++;
    }
    while(*T) {
        if (*T != '#') {
            PushStack(&tmpT, *T);
        } else if (*T == '#' && GetStackDepenth(tmpT) != 0) {
            PopStack(&tmpT, &tmpCharT);
        }
        T++;
    }

    if (GetStackDepenth(tmpS) != GetStackDepenth(tmpT)) {
        return -1;
    } else {
        while (GetStackDepenth(tmpS) != 0) {
            PopStack(&tmpS, &tmpCharS);
            PopStack(&tmpT, &tmpCharT);
            if (tmpCharS != tmpCharT) {
                return -1;
            }
        }
    }
    return 0;
}

int main(void)
{
    char* a1 = "a##c";
    char* a2 = "#a#c";
    int result = backspaceCompareStack(a1, a2);
    printf("\r\nthe result = %d\r\n", result);
    system("pause");
}