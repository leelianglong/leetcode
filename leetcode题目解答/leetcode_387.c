#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int firstUniqChar(char * s){
    if (s == NULL || *s == '\0') {  // ע���ָ�� �� ���ַ����ǲ�һ���ġ�
        return -1;
    }
    int hashTable[26] = {0};
    int position = strlen(s) - 1;
    int counter = 0;
    while (*(s + counter) != '\0') { // ע�����ﲻ��ֱ�Ӱ�s++,��Ϊ���滹��Ҫʹ��s[]�����ж�
        hashTable[*(s + counter) - 'a']++;
        counter++;
    }
    int i;
    int j;
    bool noReapt = false;
    for (i = 0; i < 26; i++) {
        if (hashTable[i] == 1) {
            noReapt = true;
            for (j = 0; j < counter; j++) {
                if (s[j] == i + 'a') {
                    position = position > j ? j : position;
                    break;
                }
            }
        }
    }

    if (noReapt == false) {
        return -1;
    }
    return position;
    /*
        //�����������׸����ظ���ʵ�ַ����Ƚ�����
        for(i = 0; i < len; i++){
        if(p[s[i] - 'a'] == 1)
            return i;
    }
    */
}


int main(void)
{
    char test[] = {""};
    int result = firstUniqChar(test);
    printf("%d", result);
    system("pause");
}