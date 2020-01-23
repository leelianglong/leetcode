#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define    MAX_LENGTH       220

char * multiply(char * num1, char * num2){
    if (num1 == NULL || num2 == NULL) {
        return NULL;
    }
    char* result="0";
    if (num1[0] == '0' || num2[0] == '0') {
        return result;
    }
    char* firstNum = (char*)malloc(sizeof(char) * strlen(num1) + 1);
    char* secondNum = (char*)malloc(sizeof(char) * strlen(num2) + 1);
    if (firstNum == NULL || secondNum == NULL) {
        return NULL;
    }
    memset(firstNum, 0, strlen(num1) * sizeof(char) + 1);
    memset(secondNum, 0, strlen(num2) * sizeof(char) + 1);
    int i;
    int j = 0;

    //  将2组字符串逆序
    for (i = strlen(num1) - 1; i >= 0; i--) {
        firstNum[j] = num1[i] - '0';
        printf("%d", firstNum[j]);
        j++;
    }
    printf("\n");
    j = 0;
    for (i = strlen(num2) - 1; i >= 0; i--) {
        secondNum[j] = num2[i] - '0';
        printf("%d", secondNum[j]);
        j++;
    }
    printf("\n");
    // 将2组数字逐位相乘
    int equal[MAX_LENGTH] = {0};  // 注意这里要用int,否则例如999 这样的，这里char类型存不下。
    for (i = 0; i < strlen(num1); i++) {
        for (j = 0; j < strlen(num2); j++) {
            equal[i + j] += firstNum[i] * secondNum[j];
            printf("%d %d%d    ", equal[i + j], i, j);
        }
    }
    printf("\n");
    //将得到的结果进位处理
    for (i = 0; i < MAX_LENGTH; i++) {
        if (equal[i] >= 10) {
            equal[i + 1] += equal[i] / 10;
            equal[i] %= 10;
        }
    }

    // 除去多余的0
    for (i = MAX_LENGTH - 1; i >= 0; i--) {
        if (equal[i] != 0) {
            break;
        }
    }

    char* res = (char*)malloc(sizeof(char) * i + 2); // 这里+2的原因， i是从0开始的，另外，还要多分配一个存储字符串结束符。
    memset(res, 0, sizeof(char) * i + 2);
    j = 0;
    // 把数组反向输出，即得到正常的结果,上面做乘法的时候做了翻转，先乘的是低位，最后是高位。
    for (; i >= 0; i--) {
        res[j++] = equal[i] + '0';
    }
    res[j] = '\0';
    return  res;
}

int main() {

    char* res = multiply("999", "999");
    printf("%s", res);
    return 0;
}
