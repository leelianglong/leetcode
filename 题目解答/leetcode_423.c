参考帖子
https://blog.csdn.net/kexinxin1/article/details/93016005?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase

// 关键在于找到字符对应的数字

#define NUMBER_LENGTH    50000
char * originalDigits(char * s){
    char* result = (char*)malloc(sizeof(char) * NUMBER_LENGTH);
    memset(result, 0, sizeof(char) * NUMBER_LENGTH);
    if (s == NULL) {
        return result;
    }
    int saveNumberCounter[10] = {0};
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == 'z') {
            saveNumberCounter[0]++;
        } else if (s[i] == 'w') {
            saveNumberCounter[2]++;
        } else if (s[i] == 'u') {
            saveNumberCounter[4]++;
        } else if (s[i] == 'x') {
            saveNumberCounter[6]++;
        } else if (s[i] == 'g') {
            saveNumberCounter[8]++;
        } else if (s[i] == 'o') {
            saveNumberCounter[1]++;
        } else if (s[i] == 'h') {
            saveNumberCounter[3]++;
        } else if (s[i] == 'f') {
            saveNumberCounter[5]++;
        } else if (s[i] == 's') {
            saveNumberCounter[7]++;
        } else if (s[i] == 'i') {
            saveNumberCounter[9]++;
        }
    }
    #if 0
    printf("\nbefore\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", saveNumberCounter[i]);
    }
    #endif
    saveNumberCounter[1] = saveNumberCounter[1] - saveNumberCounter[0] - saveNumberCounter[2] - saveNumberCounter[4];
    saveNumberCounter[3] = saveNumberCounter[3] - saveNumberCounter[8];
    saveNumberCounter[5] = saveNumberCounter[5] - saveNumberCounter[4];
    saveNumberCounter[7] = saveNumberCounter[7] - saveNumberCounter[6];
    saveNumberCounter[9] = saveNumberCounter[9] - saveNumberCounter[5] - saveNumberCounter[6] - saveNumberCounter[8];
    #if 0
    printf("after");
    for (int i = 0; i < 10; i++) {
        printf("%d ", saveNumberCounter[i]);
    }
    #endif
    int length = 0;
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < saveNumberCounter[j]; i++) {
            result[length++] = j + 0x30;
        }
    }
    return result;
}
