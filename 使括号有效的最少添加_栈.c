#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH_PARENTHESES 1000

typedef char StackElement;
typedef struct STNode
{
    int top;
    StackElement data[MAX_LENGTH_PARENTHESES + 1];
} StackNode, *LinkStack;

int InitStack(LinkStack *ls)
{
    int i;
    if (ls == NULL)
    {
        return 0;
    }
    (*ls) = (LinkStack)malloc(sizeof(StackNode));
    for (i = 0; i < MAX_LENGTH_PARENTHESES; i++)
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
    if ((*ls)->top >= MAX_LENGTH_PARENTHESES - 1)
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


int minAddToMakeValid(char * S){
    LinkStack leftParentheses = NULL;
    LinkStack rightParentheses = NULL;
    int leftStackSize = 0;
    int rightStackSize = 0;
    StackElement tmp = 0;

    if (S == NULL) {
        return 0;
    }
    InitStack(&leftParentheses);
    InitStack(&rightParentheses);
    /* 
    左括号压左栈，遇到右括号，如果左栈右元素，则左栈出栈，否则右括号入右栈；
    最终返回2个栈的大小，就是需要添加的最少括号个数（包含左括号、右括号） 
    */
    while (*S == '(' || *S == ')')
    {
        if (*S == '(')
        {
            PushStack(&leftParentheses, '(');
        }
        else
        {
            if (!CheckStackEmpty(leftParentheses))
            {
                PopStack(&leftParentheses, &tmp);
            }
            else
            {
                PushStack(&rightParentheses, ')');
            }
        }
        S++;
    }
    return GetStackDepenth(leftParentheses) + GetStackDepenth(rightParentheses);
}


int main(void)
{
    int length = 0;
    StackElement test[] = {'(','(','('};
    length = minAddToMakeValid(test);
    printf("%4d", length);
}
