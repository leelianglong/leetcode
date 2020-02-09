#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


char ** printVertically(char * s, int* returnSize){
    if (s == NULL || returnSize == NULL) {
        return NULL;
    }
    int wordMaxLength = 0;
    int wordMinLength = 0;
    int wordCounter = 1;// 这里从1开始，第一个字符非空的话，遇到第一个空间就应该是一个单词了。
    int tmpLength = 0;
    bool firstWordLength = true;
    int i;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] != ' ') {
            tmpLength++;
        } else {
            wordMaxLength = wordMaxLength < tmpLength ? tmpLength : wordMaxLength;
            if (firstWordLength) {
                wordMinLength = tmpLength;
                firstWordLength = false;
            }
            wordMinLength = wordMinLength > tmpLength ? tmpLength : wordMinLength;
            tmpLength = 0;
            wordCounter++;
        }
    }
    if (tmpLength != 0) { // 这里处理最短/长的单词在最后的情况。
        wordMaxLength = wordMaxLength < tmpLength ? tmpLength : wordMaxLength;
        wordMinLength = wordMinLength > tmpLength ? tmpLength : wordMinLength;
    }
    // 分配二维空间用于存储字符串中的各个单词
    char** tmpSaveS = (char**)malloc(sizeof(char*) * wordCounter);
    for (i = 0; i < wordCounter; i++) {
        tmpSaveS[i] = (char*)malloc(sizeof(char) * wordMaxLength + 1);
        memset(tmpSaveS[i], 0, sizeof(char) * wordMaxLength + 1);
    } 

    int tmpRow = 0;
    int tmpColum = 0;
    for (i = 0; i < strlen(s); i++) {
        if (s[i] != ' ') {
            *(*(tmpSaveS + tmpRow) + tmpColum) = s[i];   
            tmpColum++;        
        } else {
            tmpColum = 0;
            tmpRow++;
        }
    }
    // 注意这里tmpRow要多 1个；
    for (i = 0; i < tmpRow + 1; i++) {
        printf("%s\r\n", tmpSaveS[i]);
    }
    char** res = (char**)malloc(sizeof(char*) * wordMaxLength);
    for (i = 0; i < wordMaxLength; i++) {
        res[i] = (char*)malloc(sizeof(char) * wordCounter + 1);
        memset(res[i], 0, sizeof(char) * wordCounter + 1);
    }
    printf("result:\r\n");
    int j;
    int k;
    for (i = 0; i < wordMinLength; i++) {
        for(j = 0; j < wordCounter; j++) {
            *(*(res + i) + j) = *(*(tmpSaveS + j) + i);
            printf("%c", *(*(res + i) + j));
        }
        printf("\n");
    }
    for (i = wordMinLength; i < wordMaxLength; i++) {
        for (j = 0; j < wordCounter; j++) {
            char realChar = *(*(tmpSaveS + j) + i) == '\0' ? ' ' : *(*(tmpSaveS + j) + i);
            *(*(res + i) + j) = realChar;
            printf("%c", *(*(res + i) + j));
        }
        printf("\n");
    }

    for (i = 0; i < wordMaxLength; i++) {
        int delSpaceLength = strlen(res[i]);
        if (*(*(res + i ) + delSpaceLength - 1) != ' ') {
            continue;
        }
        for (k = delSpaceLength - 1; k >= 0; k--) {
            if (*(*(res + i ) + k) == ' ') {
                *(*(res + i ) + k) = '\0';
            } else {
                break;
            }
        }
    }
    *returnSize = wordMaxLength;
    return res;
}


int main(void)
{
    int returnSize = 3;
    char str[] = {"How IS IT GOING"};
    char** result = printVertically(str, &returnSize);
    system("pause");
}