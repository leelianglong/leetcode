#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void reverse(char* s, int start, int end)
{
    while (start < end) {
        char tmp = s[start];
        s[start] = s[end];
        s[end] = tmp;
        start++;
        end--;
    }
}

char * reverseWords(char * s){
    if (s == NULL) {
        return NULL;
    }
    int length = strlen(s);
    reverse(s, 0, length - 1);
    int start = 0;
    int end = 0;
    while (start < length) {
        while(end < length && s[end] != ' ') {
            end++;
        }
        reverse(s, start, end - 1);
        start = ++end;
    }
    /*
    去除字符串中单词间多余的空格，思路是：使用2个指针，front负责扫描整个字符串，
    last负责收集合适的字符,多余的空格，不用复制。
    */
    char* front = s;
    char* last = s;
    while (*front == ' ') {
        front++;
    }
    while (*front != '\0') {
        if (*front == ' ') {
            *last = ' '; 
            while (*front == ' ') {
                front++;
            }
        } else {
            *last = *front;
            ++front;
        }
        ++last;
    }
    *last = '\0';
    // 下面处理最后的空格。
    length = strlen(s);
    for (int i = length - 1; i >= 0; i--) {
        if (s[i] == ' ') {
            continue;
        } else {
            s[i + 1] = '\0';
            break;
        }
    }
    return s;
}


int main(void)
{
    char test[] = {"  hello world!  "};
    char* result = reverseWords(test);
    //reverse(test, 0, strlen(test) - 1);
    printf("%s", result);
    system("pause");
}