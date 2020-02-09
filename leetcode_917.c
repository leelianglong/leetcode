#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_CHAR(c)  ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))

char * reverseOnlyLetters(char * S){
    if (S == NULL) {
        return NULL;
    }
    int length = strlen(S);
    char* res = (char*)malloc(sizeof(char) * length + 1);
    memset(res, 0, sizeof(char) * length + 1);
    char* isAccess = (char*)malloc(sizeof(char) * length);
    memset(isAccess, 0, sizeof(char) * length);

    int i;
    int j;
    int counter = 0;
    for (i = 0; i < length; i++) {
        if (IS_CHAR(S[i])) {
            for (j = length - 1; j >= 0; j--) {
                if (IS_CHAR(S[j]) && isAccess[j] == 0) {
                    isAccess[j] = 1;
                    res[counter++] = S[j];
                    break;
                }
            }
        } else {
            res[counter++] = S[i];
        }
    }
    res[counter] = '\0';
    return res;
}


/*
* 下面是比较好的解法：采用双指针
*/
char * reverseOnlyLetters(char * S){
    int length=0,i,j;
    while(S[length]!=0) length++;
    char str[length+1];
    str[length]=0;
    i=0;
    j=length-1;
    while(i<=j){
        if(!(S[i]>='A'&&S[i]<='Z'||S[i]>='a'&&S[i]<='z')){
            str[i]=S[i];
            i++;
            continue;
        }
        if(!(S[j]>='A'&&S[j]<='Z'||S[j]>='a'&&S[j]<='z')){
            str[j]=S[j];
            j--;
            continue;
        }
        str[i]=S[j];
        str[j]=S[i];
        i++;
        j--;
    }
    S=str;
    return S;
}

int main(void)
{
    char test[] = {"a-bC-dEf-ghIj"};
    char* result = reverseOnlyLetters(test);
    printf("%s", result);
    system("pause");
}