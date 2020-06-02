/*
* 下面的算法有2个用例没有过。其中一个是 【 a aa aaa】 k = 3
*/

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    char saveStr[100];
    int repeat;
} result;

int cmp(const void* a, const void* b)
{
    char* aa = *(char**)a;
    char* bb = *(char**)b;
    return strcmp(aa, bb);
}

int cmpStruct(const void* a, const void* b)
{
    result* aa = (result*)a;
    result* bb = (result*)b;
    return bb->repeat - aa->repeat;
}

char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){
    *returnSize = 0;
    qsort(words, wordsSize, sizeof(char*), cmp);
    result* res = (result*)malloc(sizeof(result) * wordsSize);
    memset(res, 0, sizeof(result) * wordsSize);
    char** finalRes = (char**)malloc(sizeof(char*) * k);
    #if 0
    for (int k = 0; k < wordsSize; k++) {
        printf("%s\n", words[k]);
    }
    #endif
    int repeat = 1;
    int counter = 0;
    for (int i = 0; i < wordsSize - 1; i++) {
        for (int j = i + 1; j < wordsSize; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                repeat++;
                i = j;
            }
        }
        if (strcmp(res[counter].saveStr, words[i])) {
            strcpy(&res[counter].saveStr, words[i]);
            res[counter++].repeat = repeat;
        }
        repeat = 1;
    }

    qsort(res, counter, sizeof(result), cmpStruct);
    for (int i = 0; i < k; i++) {
        finalRes[i] = (char*)malloc(sizeof(char) * (strlen(res[i].saveStr) + 1));
        strcpy(finalRes[i], res[i].saveStr);
        finalRes[i][strlen(res[i].saveStr)] = '\0';
    }
    #if 0
    for (int i = 0; i < counter; i++) {
        printf("%s %d\n", res[i].saveStr, res[i].repeat);
    }
    #endif;
    *returnSize = k;
    return finalRes;
}
