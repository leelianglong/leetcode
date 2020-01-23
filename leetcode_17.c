#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char** letterCombinations(char* digits, int* returnSize)
{
    if (!strcmp(digits, "") || digits == NULL) {
        *returnSize = 0;
        return NULL;
    }

    const char* str[8] = { "abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };
    int inputLength = strlen(digits);
    int* number = (int*)malloc(sizeof(int) * inputLength);
    int outputLength = 1;
    for (int i = 0; i < inputLength; i++) {
        number[i] = digits[i] - '0';
        outputLength *= strlen(str[number[i] - 2]); // 数字2才有字母，所以这里减2. 每个字母上有不同的字符，多个数字组合，那么可能的组合方式是各个数字能组合的方式的乘积
    }
    char** ch = (char**)malloc(sizeof(char*) * outputLength);// 分配一个二维指针用来存储能够输出的所有可能
    for (int i = 0; i < outputLength; i++) {
        ch[i] = (char*)malloc(sizeof(char) * (inputLength + 1)); // 分配每种可能的长度，并把结束符也分配
    }

    int k = 1;
    for (int i = 0; i < inputLength; i++) {
        int len = strlen(str[number[i] - 2]);
        k *= len;
        int block = outputLength / k;
        for (int j = 0; j < k; j++) {//这里是关键，先填充所有可能的第一个字符，然后再补充后面的。
            for (int r = j * block; r < (j + 1) * block; r++) {
                ch[r][i] = str[number[i] - 2][j % len];
                //printf("%c%d%d ", ch[r][i], r, i);
            }
        }
    }

    for (int i = 0; i < outputLength; i++) { //outputLength种输出可能，
        ch[i][inputLength] = '\0'; //每种输出可能长度是 inputlength,在末尾加上结束符。
    }
    *returnSize = outputLength;
    return ch;
}

int main() {
    char* digits = (char*)"23";
    int* returnSize = (int*)malloc(sizeof(int) * 1);
    int length = sizeof(digits) / sizeof(char);
    char** res = letterCombinations(digits, returnSize);

    for (int i = 0; i < *returnSize; i++) {
        for (int j = 0; j < length; j++) {
            //printf("%c", res[i][j]);
        }
        printf("\n");
    }
    return 0;
}
