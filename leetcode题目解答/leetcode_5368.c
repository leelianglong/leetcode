/*
* 看到频率一般使用hash存储
*/

int findLucky(int* arr, int arrSize){
    if (arr == NULL || arrSize <= 0) {
        return -1;
    }
    int  hashTmp[10000] = {0};
    int i;
    int max = -1;
    int returnMax = -1;
    for (i = 0; i < arrSize; i++) {
        hashTmp[arr[i]]++;
        max = max < arr[i] ? arr[i] : max;
    }
    
    for (i = 1; i <= max; i++) {
        if (hashTmp[i] == i) {
            returnMax = returnMax < i ? i : returnMax;
        }
    }
    return returnMax == -1 ? -1 : returnMax;
}
