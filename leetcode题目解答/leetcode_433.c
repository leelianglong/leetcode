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

bool  isValidChange(char** bank, int bankSize, char* src)
{
    for (int i = 0; i < bankSize; i++) {
        if (strcmp(bank[i], src) == 0) {
            return true;
        }
    }
    return false;
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
