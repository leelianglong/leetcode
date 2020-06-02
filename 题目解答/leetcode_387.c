#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int firstUniqChar(char * s){
    if (s == NULL || *s == '\0') {  // 注意空指针 和 空字符串是不一样的。
        return -1;
    }
    int hashTable[26] = {0};
    int position = strlen(s) - 1;
    int counter = 0;
    while (*(s + counter) != '\0') { // 注意这里不能直接把s++,因为下面还需要使用s[]来做判断
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
        //下面这种找首个不重复的实现方法比较优雅
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