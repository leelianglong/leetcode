#include <stdio.h>
#include <stdbool.h>
#include "securec.h"

#define BUF_LEN 50000

typedef struct {
    int top;
    int* buf;
} Stack;

bool IsOperateSysmbol(char *in)
{
    if (strcmp(in, "+") == 0 || strcmp(in, "/") == 0  || strcmp(in, "*") == 0  || strcmp(in, "-") == 0 ) {
        return true;
    }
    return false;
}

Stack* InitStack(void)
{
    Stack* obj = NULL;
    obj = (Stack*)malloc(sizeof(Stack));
    if (obj == NULL) {
        return obj;
    }
    obj->buf = (int*)malloc(sizeof(int) * BUF_LEN);
    (void)memset_s(obj->buf, sizeof(int) * BUF_LEN, 0, sizeof(int) * BUF_LEN);
    obj->top = -1;
    return obj;
}

void PushStack(Stack* obj, int data)
{
    if (obj->top > BUF_LEN - 1) {
        return;
    }
    obj->top++;
    obj->buf[obj->top] = data;
}

bool PopStack(Stack* obj, int* data)
{
    if (obj->top < 0){
        return false;
    }
    *data = obj->buf[obj->top];
    obj->top--;
    return true;
}

int Caculation(int data1, int data2, const char sysbol)
{
    int result = 0;
    switch (sysbol) {
        case '+' :
            result = data2 + data1;
            break;
        case '-' :
            result = data2 - data1;
            break;
        case '*' :
            result = data2 * data1;
            break;
        case '/' :
            result = data2 / data1;
            break;
        default:
            break;
    }
    return result;
}

int divide(char* in)
{
    Stack* obj = InitStack();
    char* pstr = strtok(in, ",");
    int i = 0;
    while (pstr != NULL) {
        while (!IsOperateSysmbol(pstr)) {
            PushStack(obj, atoi(pstr));
            pstr = strtok(NULL, ",");
        }
        int data1 = 0;
        int data2 = 0;
        int tmp = 0;
        bool ret1 = PopStack(obj, &tmp);
        if (ret1) {
            data1 = tmp;
        }
        tmp = 0;
        bool ret2 = PopStack(obj, &tmp);
        if (ret2) {
            data2 = tmp;
        }

        int midResult = Caculation(data1, data2, *pstr);

        PushStack(obj, midResult);
        pstr = strtok(NULL, ",");
    }
    return obj->buf[obj->top];
}

int Calc(char *input)
{
    int ret = divide(input);
    return ret;
}


int main(void)
{
    static char buf[BUF_LEN];
    if (scanf_s("%s", buf, sizeof(buf)) != 1) { return -1; }

    int ret = Calc(buf);

    (void)printf("%d", ret);
    return 0;
}
