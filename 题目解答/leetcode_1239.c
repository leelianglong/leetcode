/*
* 该题目的意思就是把不相同的（所有字符都不同）字符串组合起来，找到能组成最长字符串的长度。
* 对于一个字符串要么添加到新的组成串中，要么不添加进去，通过类似二叉树的深度优先搜索来计算长度
*/
bool findSame(char* data, char* hashSame)
{
    int i;
    for (i = 0; i < strlen(data); i++) {
        hashSame[data[i] - 'a']++;
    }
    for (i = 0; i < 26; i++) {
        if (hashSame[i] > 1) {
            return true;
        }
    }
    return false;
}

int totalSize = 0;
int step(char** arr, int index, char* hashTable)
{
    if (index == totalSize) {
        return 0;
    }
    char hashTmp[26] = {0};
    memcpy(hashTmp, hashTable, 26);
    if (!findSame(arr[index], hashTmp)) {
        int curLength = strlen(arr[index]);
        int leftLength = curLength + step(arr, index + 1, hashTmp);
        int rightLength = step(arr, index + 1, hashTable);
        return leftLength > rightLength ? leftLength : rightLength;
    }
    return step(arr, index + 1, hashTable);
}

int maxLength(char ** arr, int arrSize){
    char hash[26] = {0};
    totalSize = arrSize;
    return step(arr, 0, hash);
}



/*
1.把字符串按照长度从小到大的顺序排序。
2.逐个计算每个字符串是否有重复的字符
3.倒序遍历，把2个最长的没有重复字符的字符串长度加起来返回。
4.目前没有想好如何解决 a,b,c,d 类似这种用例
*/
下面的解法这能过70个用例：
int cmp(const void * a, const void* b)
{
    char* aa = *(char**)a;
    char* bb = *(char**)b;
    return strlen(aa) - strlen(bb);
}

bool HasRepeatCha(char* buf, int* map)
{
    for (int i = 0; i < strlen(buf); i++) {
        map[buf[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (map[i] > 1) {
            return true;
        }
    }
    return false;
}

bool hasSameCha(int* buf1, int* buf2)
{
    for (int i = 0; i < 26; i++) {
        if (buf1[i] != 0  && buf2[i] != 0 && buf1[i] == buf2[i]) {
            return true;
        }
    }
    return false;
}

int maxLength(char ** arr, int arrSize){
    int map[2][26] = {0};
    qsort(arr, arrSize, sizeof(arr[0]), cmp);
    if (arrSize <= 0) {
        return 0;
    }
    if (arrSize == 1 && HasRepeatCha(arr[0], map[0])) {
        return 0;
    } else if (arrSize == 1 && !HasRepeatCha(arr[0], map[1])) {
        return strlen(arr[0]);
    }
    #if 0
    for (int i = arrSize - 1; i >= 0; i--) {
        printf("%s\n", arr[i]);
    }
    #endif
    for (int i = arrSize - 1; i > 0; i--) {
        memset(map[0], 0, sizeof(int) * 26);
        if (HasRepeatCha(arr[i], map[0])) {
            //printf("i=%d", i);
            continue;
        }
        for (int j = i - 1; j >= 0; j--) {
            memset(map[1], 0, sizeof(int) * 26);
            if (HasRepeatCha(arr[j], map[1])) {
                //printf("j=%d", j);
                continue;
            }
            if (hasSameCha(map[0], map[1]) && j != 0) {
                //printf("(%d,%d)", i, j);
                continue;
            } else if (hasSameCha(map[0], map[1]) && j == 0) {
                return strlen(arr[i]);
            }
            return strlen(arr[i]) + strlen(arr[j]);
        }
    }
    return 0;
}


上面这种解法的缺陷在与考虑场景单一，正确的解法的思路是：
参考现有题解，这里获取最大长度时，选取以任意一个字符串为起点，然后遍历剩余的字符串，把符号要求的串在一起，每次记录这个长度。最后再找出最大长度的。而不能像上面的简单合并。
这种解法有一个用例不能通过：["abc","ab","cd","efg","ef","gh"]
#define MAX(a,b)  ((a) > (b) ? (a) : (b))

int cmp(const void * a, const void* b)
{
    char* aa = *(char**)a;
    char* bb = *(char**)b;
    return strlen(bb) - strlen(aa);
}

bool HasRepeatCha(char* buf, int* map)
{
    for (int i = 0; i < strlen(buf); i++) {
        map[buf[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (map[i] > 1) {
            return true;
        }
    }
    return false;
}

bool hasSameCha(int* buf1, int* buf2)
{
    for (int i = 0; i < 26; i++) {
        if (buf1[i] != 0  && buf2[i] != 0 && buf1[i] == buf2[i]) {
            return true;
        }
    }
    return false;
}

int maxLength(char ** arr, int arrSize){
    int map[2][26] = {0};
    qsort(arr, arrSize, sizeof(arr[0]), cmp);
    int size = 0;
    char save[27] = {0};
    if (arrSize <= 0) {
        return 0;
    }

    int* count = (int*)malloc(sizeof(int) * arrSize);
    memset(count, 0, sizeof(int) * arrSize);
    for (int i = 0; i < arrSize; i++) {
        size = 0;
        memset(map[0], 0, sizeof(int) * 26);
        if (HasRepeatCha(arr[i], map[0])) {
            continue;
        }
        size += sprintf(save + size, "%s", arr[i]);
        count[i] = size;
        for (int j = 0; j < arrSize; j++) {
            memset(map[1], 0, sizeof(int) * 26);
            memset(map[0], 0, sizeof(int) * 26);
            HasRepeatCha(save, map[0]);
            if (i != j && !HasRepeatCha(arr[j], map[1]) && !hasSameCha(map[0], map[1])) {
                size += sprintf(save + size, "%s", arr[j]);
                count[i] = size;
            }
        }
    }
    int res = INT_MIN;
    for (int i = 0; i < arrSize; i++) {
        res = MAX(res, count[i]);
    }
    return res;
}
