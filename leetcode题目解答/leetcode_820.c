#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
* 思路：
* 1、这里说的是单词列表，并不是语句，所以单词出现的没有先后顺序；
* 2、题目的意思是某个单词是另一个单词的后缀的话，该单词就可以使用另一个单词
加上编码得到，所以它可以不要；
* 3、如何将有后缀关系的单词放在一起？ 这里就使用逆序，再升序，就达到效果。
*/
void reverse(char* str)
{
    int length = strlen(str);
    char tmp = 0;
    int i;
    for (i = 0; i < (length + 1) / 2; i++) {
        tmp = str[i];
        str[i] = str[length - i -1];
        str[length - i - 1] = tmp;
    }
}

int cmp(const void* a, const void* b)
{
    char* s1 = *(char**)a;
    char* s2 = *(char**)b;
    return strcmp(s1, s2);
}

int minimumLengthEncoding(char ** words, int wordsSize){
    if (words == NULL || wordsSize <= 0) {
        return 0;
    }
    int i;
    for (i = 0; i < wordsSize; i++) {
        reverse(words[i]);
    }
    qsort(words, wordsSize, sizeof(char*), cmp);
    for (i = 0; i < wordsSize; i++) {
        printf("%s\n", words[i]);
    }
    printf("\n");
    int res = 0;
    for (i = 0; i < wordsSize; i++) {
        if (i + 1 < wordsSize && strstr(words[i + 1], words[i])) {
            continue;
        }
        res += strlen(words[i]) + 1;
    }
    return res;
}

int main(void)
{
    char* test[3] = {"time","bell","me"};
    char buf[2000] = {0};
    int offset = 0;
    int i;
    char** tmp = (char**)malloc(sizeof(char*) * 3);
    for (i = 0; i < 3; i++) {
        tmp[i] = (char*)malloc(sizeof(char) * 7);
        memset(tmp[i], 0, sizeof(char) * 7);
        strncpy(tmp[i], test[i], strlen(test[i]));
    }
    int result = minimumLengthEncoding(tmp, 3);
    printf("\r\n result=%d", result);
    system("pause");
}