#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char * toHexspeak(char * num){
    if (num == NULL) {
        return NULL;
    }
    unsigned long long tmp = 0;
    int i;
    for (i = 0; i < strlen(num); i++) {
        tmp = tmp * 10 + (*(num + i) - '0');
    }
    char hexBuf[12] = {17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17};
    char* result = (char*)malloc(12 * sizeof(char));
    memset(result, 12, 0);
    int k = 0;
    while (tmp > 0) {
        hexBuf[k++] = tmp % 16;  
        tmp = tmp / 16;  
    }
    bool flag = true;
    for ( i = 0; i < 11 && hexBuf[i] != 17; i++) {
        if (hexBuf[i] == 1) {
            hexBuf[i] = 'I';
        } else if (hexBuf[i] == 0) {
            hexBuf[i] = 'O';
        } else if (hexBuf[i] >= 10 && hexBuf[i] < 16) {
            hexBuf[i] = hexBuf[i] + 'A' - 10;
        } else {
            flag = false;
            hexBuf[i] = hexBuf[i] + '0';
        }
    }
    char a = 0;
    for (k = 0; k < i / 2; k++) {
        a = hexBuf[k];
        hexBuf[k] = hexBuf[i - k - 1]; 
        hexBuf[i - k - 1] = a;
    }
    hexBuf[i] = '\0';
    if (flag) {
        memcpy_s(result, 12, hexBuf, 1 + strlen(hexBuf));      
    } else {
        memcpy_s(result, 12, "ERROR", 6);
    }
    return result;
}

int main(void)
{
    char* test = "747823223228";
    char* result = toHexspeak(test);
    printf("%s", result);
    system("pause");
}