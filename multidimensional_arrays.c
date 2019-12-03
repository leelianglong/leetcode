#include <stdio.h>
#include <stdlib.h>


int a[2][3][4] = {1,2,3,4,5,6,7,8,9,10};

int (*GetArray(void))[3][4] 
{
    return a;
}

int main(void)
{
    int (*access)[3][4] = GetArray();
    printf("hello world");
    system("pause");
}