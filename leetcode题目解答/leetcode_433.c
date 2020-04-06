/*
* 基因的每一次变换都要求是合法的，所以是在基因库中的。
* 所以每次在基因库中找一个和当前基因序列相差一个的，使其入队，然后再出队，再在基因库中找相差一个的，每找到一个，步数加1。
* 如此循环直到队列为空。
*/

typedef struct {
    char* str;
    int changeSteps;
} Element;

bool isOneStepChange(char* src, char* dst, int len)
{
    int changeCounter = 0;
    for (int i = 0; i < len; i++) {
        if (src[i] != dst[i] && (++changeCounter > 1)) {
            return false;
        }
    }
    return changeCounter == 1;
}

int minMutation(char * start, char * end, char ** bank, int bankSize){
    int change = 0;
    Element* queue = (Element*)malloc(sizeof(Element) * (bankSize + 2));
    int* visit = (int*)malloc(sizeof(int) * bankSize);
    memset(visit, 0, sizeof(int) * bankSize);

    int front = 0;
    int rear = 0;
    int length = strlen(start);

    queue[rear].changeSteps = 0;
    queue[rear++].str = start;
    int steps;
    char* outStr = NULL;
    while (front != rear){
        steps = queue[front].changeSteps;
        outStr = queue[front++].str;
        //printf("\nf %s", outStr);
        if (strcmp(outStr, end) == 0) {
            return steps;
        }
        int i;
        for (i = 0; i < bankSize; i++) {
            //printf("\n i:%d", i);
            if (visit[i] == false && isOneStepChange(bank[i], outStr, length)) {
                visit[i] = true;
                queue[rear].changeSteps = steps + 1;
                queue[rear++].str = bank[i];
                //printf("\nr : %s", bank[i]);
            }
        }
    } 
    return -1;
}
