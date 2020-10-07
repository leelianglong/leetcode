
int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int findMinDifference(char ** timePoints, int timePointsSize){
    int* tmp = (int*)malloc(sizeof(int) * timePointsSize);
    memset(tmp, 0, sizeof(int) * timePointsSize);
    int counter = 0;
    int num[2] = {0};
    for (int i = 0; i < timePointsSize; i++) {
        char* hour = strtok(timePoints[i], ":");
        memset(num, 0, sizeof(int) * 2);
        counter = 0;
        while (hour != NULL) {
            num[counter++] = atoi(hour);
            hour = strtok(NULL, ":");
        }
        tmp[i] = num[0] * 60 + num[1];
    }
    qsort(tmp, timePointsSize, sizeof(int), cmp);
    int min = 24 * 60 - tmp[timePointsSize - 1] + tmp[0];  // 这个差值计算是关键
    for (int i = 0; i < timePointsSize - 1; i++) {
        if (tmp[i + 1] - tmp[i] < min) {
            min = tmp[i + 1] - tmp[i];
        }
    }
    return min;
}
