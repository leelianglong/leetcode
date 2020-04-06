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
