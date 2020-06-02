#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetSize(int* buff)
{
    int counter = 0;
    for (int i = 0; i < 128; i++) {
        if (buff[i] != 0) {
            counter++;
        } 
    }
    return counter;
}

char * minWindow(char * s, char * t){
    if (s == NULL || t == NULL) {
        return NULL;
    }
    int left = 0;
    int right = 0;
    int targetHash[128] = {0};
    int sourceHash[128] = {0};
    int windowHash[128] = {0};
    int length = strlen(t);
    int i;
    char* tTmp = t;
    for (i = 0; i < length; i++) {
        targetHash[*(tTmp++)]++;
    }
    char* sTmp = s;
    length = strlen(s);
    for (i = 0; i < length; i++) {
        sourceHash[*(sTmp++)]++;
    }
    int match = 0;
    while (right < strlen(s)) {
        char c1 = s[right];
        if (targetHash[c1]) { // ��ǰ�ַ���Ŀ���ַ�������
            windowHash[c1]++; // �Ѹ��ַ��ŵ�����֮��
            if (windowHash[c1] == targetHash[c1]) { // C1 �ַ�����Ҫ��
                match++;
            }
        }
        right++; // ����ָ�������ƶ�
        while (match == GetSize(targetHash)) {
            
        }
    }
}

int main(void)
{


}