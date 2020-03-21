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
    ȥ���ַ����е��ʼ����Ŀո�˼·�ǣ�ʹ��2��ָ�룬front����ɨ�������ַ�����
    last�����ռ����ʵ��ַ�,����Ŀո񣬲��ø��ơ�
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
    // ���洦�����Ŀո�
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