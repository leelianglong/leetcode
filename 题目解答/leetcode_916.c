bool find(char* data1, char* data2)
{
    int i;
    for (i = 0; i < 26; i++) {
        if (data2[i] == 0) { // 根据target中的字符来比较
            continue;
        }
        if(data1[i] < data2[i]) {
            return false;
        }
    }
    return true;
}

char ** wordSubsets(char ** A, int ASize, char ** B, int BSize, int* returnSize){
    char Ahash[26] = {0};
    char Bhash[10000][26] = {{0}};
    char merge[26] = {0};
    int i;
    int j;
    for (i = 0; i < BSize; i++) {
        for (j = 0; j < strlen(B[i]); j++) {
            Bhash[i][B[i][j] - 'a']++;
        }
    }
    char columMax = 0;
    for (i = 0; i < 26; i++) {
        for (j = 0; j < BSize; j++) {
            columMax = columMax > Bhash[j][i] ? columMax : Bhash[j][i];
        }
        merge[i] = columMax;
        columMax = 0;
    }
    *returnSize = 0;

    char** res = (char**)malloc(sizeof(char*) * 10000);
    int k;
    int m;
    for (i = 0; i < ASize; i++) {
        for (j = 0; j < strlen(A[i]); j++) {
            Ahash[A[i][j] - 'a']++;
        }
        if (find(Ahash, merge)) {
            res[(*returnSize)] = (char*)malloc(strlen(A[i]) + 1);
            memset(res[(*returnSize)], 0, strlen(A[i]) + 1);
            memcpy(res[(*returnSize)], A[i], strlen(A[i]));
            (*returnSize)++;
        }
        memset(Ahash, 0, 26);
    }
    return res;
}
