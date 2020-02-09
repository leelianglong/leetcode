#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char*s, int start, int end)
{
    while (start < end) {
        char tmp = s[start];
        s[start] = s[end];
        s[end] = tmp;
        start++;
        end--;
    }
}

char * addBinary(char * a, char * b){
    if(a == NULL || b == NULL) {
        return NULL;
    }
    int aLength = strlen(a);
    int bLength = strlen(b);
    int returnLength = 0;
    if (aLength == bLength) {
        returnLength += aLength + 1;
    } else {
        returnLength = (aLength > bLength ? aLength : bLength) + 1;
    }
    char* res = (char*)malloc(sizeof(char) * returnLength + 1);
    memset(res, 0, sizeof(char) * returnLength + 1);
    reverse(a, 0, aLength - 1);
    reverse(b, 0, bLength - 1);
    int i = 0;
    int j = 0;
    int counter = 0;
    while (i < aLength && j < bLength) {
        res[counter] += a[i] - '0' + b[j] - '0';
        if (res[counter] >= 2) {
            res[counter + 1] += res[counter] / 2;
            res[counter] %= 2;            
        }
        counter++;
        i++;
        j++;
    }
    if (i == aLength && j != bLength) {
        for (i = aLength; i < bLength; i++) {
            res[counter] += b[i] - '0';
            if (res[counter] >= 2) {
                res[counter + 1] += res[counter] / 2;
                res[counter] %= 2;               
            }
            counter++; 
        }
    }
    if (j == bLength && i != aLength) {
        for (i = bLength; i < aLength; i++) {
            res[counter] += a[i] - '0';
            if (res[counter] >= 2) {
                res[counter + 1] += res[counter] / 2;
                res[counter] %= 2;               
            }
            counter++; 
        }
    }
    for (i = 0; i <= counter; i++) {
        res[i] += 0x30;
    }
    reverse(res, 0, counter);
// 处理前面是0的特殊情况
    if (res[0] == '0') {
        for (i = 0; i <= counter; i++) {
            if (res[i] == '0') {
                continue;
            } else {
                return &res[i];
            }
        }
        if ( i == counter + 1) {
            return "0";
        }        
    }
    return res;
}


int main(void)
{
    char a[] = {"11"};
    char b[] = {"1"};
    char* result = addBinary(a, b);
    printf("%s", result);
    system("pause");
}