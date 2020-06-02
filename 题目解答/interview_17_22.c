/*
* 这个题目没有完成，主要卡在 队列中元素并不是想要的解。
* 当一个单词和接下来多个单词都只差一个字符时，它们都会被入队。所以不能把队列中出现的元素当成解，但是如何在队列中挑出解来，还未实现。
* 这个题目应该首先排除 结束单词 没有在字典中的情况。我下面这种做法不好。一般都是先判断异常情况。
*/

bool IsOneCharDiff(const char* dst, const char* src)
{   
    int counter = 0;
    for (int i = 0; i < strlen(dst); i++) {
        if (dst[i] != src[i] && (++counter > 1)) {
            return false;
        }
    }
    return counter == 1 ;
}

char** findLadders(char* beginWord, char* endWord, char** wordList, int wordListSize, int* returnSize){
    char** result = (char**)malloc(sizeof(char*) * (wordListSize + 100));
    *returnSize = 0;
    int* visited = (int*)malloc(sizeof(int) * wordListSize);
    memset(visited, 0, sizeof(int) * wordListSize);
    char** queue = (char**)malloc(sizeof(char*) * (wordListSize + 100));
    for (int i = 0; i < wordListSize + 100; i++) {
        queue[i] = (char*)malloc(sizeof(char) * 26);
        memset(queue[i], 0, sizeof(char) * 26);
    }
    int front = 0;
    int rear = 0;
    strncpy(queue[rear++], beginWord, strlen(beginWord));
    result[(*returnSize)] = (char*)malloc(sizeof(char) * 26);
    memset(result[(*returnSize)], 0, sizeof(char) * 26);
    strncpy(result[(*returnSize)++], beginWord, strlen(beginWord));
    while (front != rear) {
        int curSize = rear - front;
        for (int i = 0; i < curSize; i++) {
            char* curNode = queue[front];
            printf("\n %s", curNode);
            if (strcmp(curNode, endWord) == 0) {
                return result;
            }
            front++;
            for (int k = 0; k < wordListSize; k++) {
                if ((visited[k] == 0) && IsOneCharDiff(curNode, wordList[k])) {
                    visited[k] = 1;
                    strncpy(queue[rear], wordList[k], strlen(wordList[k]));
                    //printf("\n rear = %d", rear);
                    rear++;
                    result[(*returnSize)] = (char*)malloc(sizeof(char) * 26);
                    memset(result[(*returnSize)], 0, sizeof(char) * 26);
                    strncpy(result[(*returnSize)++], wordList[k], strlen(wordList[k]));
                }
            }
        }
    }
    *returnSize = 0;
    return result;
}
