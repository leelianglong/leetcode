#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//���������������������֧��3�������ϵ���ͬ������
char c[8][4] = {
    "abc", //2
    "def", //3
    "ghi", //4
    "jkl", //5
    "mno",//6
    "pqrs",//7
    "tuv",//8
    "wxyz"//9
};

//ÿ�������ܱ�ʾ���ַ���Ŀ
int total[8] = {3,3,3,3,3,4,3,4};

//�绰����:����绰��8λ��
int phoneNum[8] = {3,3};

//������ʾ��ǰ����������C�������±ꡣ
int answer[8] = {0};

char** letterCombinations(char* digits, int* returnSize) {
    int i;
    int index;
    int counter = 0;
    int counter1 = 0;
    char tmp[256] = { 0 };
    char* check = digits;

    if (check == NULL || *check == '\0') {
        *returnSize = 0;
        return;
    }
    while (*check) {
        if (*check > 0x39 || *check < 0x32) {
            *returnSize = 0;
            return NULL;
        }
        check++;
    }

    char** str = (char**)malloc(200 * sizeof(char*));
    if (str == NULL) {
        *returnSize = 0;
        return 0;
    }
    for (i = 0; i < 200; i++) {
        str[i] = (char*)malloc(9 * sizeof(char));
        if (str[i] == NULL) {
            *returnSize = 0;
            return 0;
        }
    }
    int digitsLength = strlen(digits);
    while (true) {
        /*���ﴦ�����ַ������*/
        if (digitsLength == 1) {
            switch (*digits) {
            case '2':
                memcpy(*(str + 0), "a", 2);
                memcpy(*(str + 1), "b", 2);
                memcpy(*(str + 2), "c", 2);
                *returnSize = 3;
                return str;
            case '3':
                memcpy(*(str + 0), "d", 2);
                memcpy(*(str + 1), "e", 2);
                memcpy(*(str + 2), "f", 2);
                *returnSize = 3;
                return str;
            case '4':
                memcpy(*(str + 0), "g", 2);
                memcpy(*(str + 1), "h", 2);
                memcpy(*(str + 2), "i", 2);
                *returnSize = 3;
                return str;
            case '5':
                memcpy(*(str + 0), "j", 2);
                memcpy(*(str + 1), "k", 2);
                memcpy(*(str + 2), "l", 2);
                *returnSize = 3;
                return str;
            case '6':
                memcpy(*(str + 0), "m", 2);
                memcpy(*(str + 1), "n", 2);
                memcpy(*(str + 2), "o", 2);
                *returnSize = 3;
                return str;
            case '7':
                memcpy(*(str + 0), "p", 2);
                memcpy(*(str + 1), "q", 2);
                memcpy(*(str + 2), "r", 2);
                memcpy(*(str + 3), "s", 2);
                *returnSize = 4;
                return str;
            case '8':
                memcpy(*(str + 0), "t", 2);
                memcpy(*(str + 1), "u", 2);
                memcpy(*(str + 2), "v", 2);
                *returnSize = 3;
                return str;
            case '9':
                memcpy(*(str + 0), "w", 2);
                memcpy(*(str + 1), "x", 2);
                memcpy(*(str + 2), "y", 2);
                memcpy(*(str + 3), "z", 2);
                *returnSize = 4;
                return str;
            default:
                *returnSize = 0;
                return 0;
            }
        }
        /*���洦�������ֵ��������û���ظ�������*/
        for (i = 0; i < strlen(digits); i++) {
            tmp[i] = c[digits[i] - 0x30 - 2][answer[i]];
        }
        memcpy(*(str + counter1), tmp, 1 + strlen(tmp));
        counter1++;
        for (index = strlen(digits) - 1; index >= 0; index--) { //���Ǵ����һ�����ֿ�ʼ����
            if (answer[index] < total[digits[index] - 0x30] - 1) {
                answer[index]++;
                break;
            }
            else
            {
                answer[index] = 0;
                index--;
            }
        }

        if (index < 0) {
            if (strlen(digits) == 1) {
                break;
            }
            counter++;
            answer[0] = counter;
        }
        if (counter >= total[digits[0] - 0x30 - 2]) {
            break;
        }
    }
    *returnSize = counter1;
    return str;
}


int main(void)
{
#if 1
    int counter = 0;
    int i = 0;
    char* digits = "888";
    char** str = letterCombinations(digits, &counter);
    for (i = 0; i < counter; i++) {
        printf("%s\r\n", *(str + i));
    }
#endif
}
















/*
������㷨��ֻ���ǰѵ�һ�����ֶ�Ӧ������ĸ�ͺ�������ֶ�Ӧ����ĸ����������ܰ��׸����ֶ�Ӧ��������ĸ�������
*/
#if 0
while (true) {
    for (i = 0; i < 8; i++) {
        printf("%c", c[phoneNum[i] - 2][answer[i]]);
    }
    printf("\r\ncounter=%d\r\n", counter);
    counter++;
    for (index = 8 - 1; index >= 0; index--) { //���Ǵ����һ�����ֿ�ʼ����
        if (answer[index] < total[phoneNum[index]] - 1) {
            answer[index]++;
            break;
        }
        else
        {
            answer[index] = 0;
            index--;
        }
    }

    if (index < 0) {
        break;
    }
    }
#endif