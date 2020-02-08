#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
* �����һ����ʾ�ǣ� ջ�����������һ���������ַ����������һ���ַ���Ϊ��ջ�ı�־��
* ����ǰ��ĳ�ջ���ַ��Ƿ��Ԥ��һ�¡�
*/
#define STACK_LENGTH    1024
typedef struct {
    char index[STACK_LENGTH];
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

int PushStack(LinkStack *ls, char index)
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

int PopStack(LinkStack *ls, char *index)
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

bool CheckStackEmpty(LinkStack ls)
{
    return ls->top == -1 ? true : false;
}

int GetStackDepenth(LinkStack ls) 
{
    return  ls == NULL ? 0 : ls->top + 1;
}

bool isValid(char * S){
    if (S == NULL) {
        return false;
    }
    LinkStack ls;
    InitStack(&ls);
    int length = strlen(S);
    int i;
    for (i = 0; i < length; i++) {
        if (S[i] != 'c') {
            PushStack(&ls, S[i]);
        } else {
            char tmp[2] = {0};
            int ret = -1;
            ret = PopStack(&ls, &tmp[0]);
            if (ret == 0) {
                return false;
            }
            ret = PopStack(&ls, &tmp[1]);
            if (ret == 0) {
                return false;
            }
            if (tmp[0] != 'b' || tmp[1] != 'a') { // ����Ҫ��||��ʵ���ϣ�����Ҫ���ջ����2��һ����b �� a����ȷ��
                return false;
            }
        }
    }
    return CheckStackEmpty(ls);
}


int main(void)
{
    char test[] = {"aabbcc"};
    int result = isValid(test);
    printf("%d", result);
    system("pause");
}