/*
* 看到频率一般使用hash存储
* 这里2点需要注意，使用max 和 returnMax 来表示。 得到max，可以在下面遍历hash数组时，少些时间； returnMax,是题目中要求的多个幸运数存在时，返回最大的
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
