/*
* 总体思路就是：从beginWord开始，先把beginWord入队，然后再出队，然后再Wordlist中搜索到和beginWord相差一个字符的单词，使其入队。
* 然后再出队，再在Wordlist中找和该单词相差一个的单词，入队。如此循环往复。
* 结束条件是，最后出队的单词和结束单词完全一样。
* 或者是队列为空了。
* 该题中定义了一个结构很好，保存了变换的步数，不需要吧front 和 rear指针保存下来，这2个指针在过程中处理。
* 另外，避免出现不好计算的循环队列，这里在分配队列内存时 多分配了 2个单位空间。
*/

typedef struct {
    char* str;
    int changeStep;
}Element;

bool isOneStepChange(char* str1, char* str2, int len)
{
    int i;
    int changeCounter = 0;
    for (i = 0; i < len; i++) {
        if (str1[i] != str2[i] && (++changeCounter > 1)) {
            return false;
        }
    }
    return changeCounter == 1;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
    if (wordListSize == 0) {
        return 0;
    }
    int length = strlen(beginWord);
    Element* queue = (Element*)malloc(sizeof(Element) * (wordListSize + 2));
    int* visit = (int*)malloc(sizeof(int) * wordListSize);
    memset(visit, 0, sizeof(int) * wordListSize);

    int front = 0;
    int rear = 0;
    queue[rear].changeStep = 1; // 初始就需要1步转换。
    queue[rear++].str = beginWord; 

    int level;
    char* outBuf = NULL;
    while (front != rear) {
        level = queue[front].changeStep; // 这里2步，都是给队列中同一个节点赋值。第二个用++表示下一次出队的位置
        outBuf = queue[front++].str;
        printf("\nf:%s\n", outBuf);
        if (strcmp(outBuf, endWord) == 0) {
            printf("\nreturn %d\n", level);
            return level;
        }
        int i;
        for (i = 0; i < wordListSize; i++) {
            printf("\n i:%d", i);
            if (visit[i] == 0 && isOneStepChange(outBuf, wordList[i], length)) {
                visit[i] = 1;
                queue[rear].changeStep = level + 1;
                queue[rear++].str = wordList[i];
                printf("\nr:%s\n", wordList[i]);
            }
        }
    }
    return 0;
}
