/*
* 当前解法没有完全正确还有4个用例没有过。
*/
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

char*** finalRes;
int finalReturnSize;
#define EXPECTED_PLALINDROME_COUNTER  100

bool IsPlalindrome(char* s, int left, int right)
{
    if (left == right) {
        return true;
    }

    while (left < right) {
        if (s[left] != s[right]) {
            return  false;
        }
        left++;
        right--;
    }
    return true;
}

char* GetSubStr(char* s, int start, int end)
{
    char* res = (char*)malloc(sizeof(char) * (end - start + 2));
    memset(res, 0, sizeof(char) * (end - start + 2));
    int counter = 0;
    for (int i = start; i <= end; i++) {
        res[counter++] = s[i];
    }
    res[counter] = '\0';
    return res;
}

void BuilFinalRes(char** subStr, int subSize, int* subStrColSize)
{
    finalRes[finalReturnSize] = (char**)malloc(sizeof(char*) * subSize);
    subStrColSize[finalReturnSize] = subSize;
    for (int i = 0; i < subSize; i++) {
        finalRes[finalReturnSize][i] = (char*)malloc(sizeof(char) * (strlen(subStr[i]) + 1));
        memset(finalRes[finalReturnSize][i], 0, sizeof(char) * (strlen(subStr[i]) + 1));
        strcpy(finalRes[finalReturnSize][i], subStr[i]);
    }
    finalReturnSize++;
}

void step(char* s, int length, int pos, char** subStr, int subStrSize, int* subStrColSize)
{
    if (pos == length) {
        //找到字符串的结尾退出
        BuilFinalRes(subStr, subStrSize, subStrColSize);
        return;
    }
    for (int i = pos; i < length; i++) {
        if (IsPlalindrome(s, pos, i)) {
            subStr[subStrSize] = GetSubStr(s, pos, i);
            step(s, length, i + 1, subStr, subStrSize + 1, subStrColSize);
        }
    }
}

char *** partition(char * s, int* returnSize, int** returnColumnSizes){
    finalReturnSize = 0;
    finalRes = (char***)malloc(sizeof(char**) * EXPECTED_PLALINDROME_COUNTER);
    char** subStr = (char**)malloc(sizeof(char*) * strlen(s)); // 单个字符也可以是回文串，这里存储所有的回文子串
    *returnColumnSizes = (int*)malloc(sizeof(int) * EXPECTED_PLALINDROME_COUNTER);
    memset(*returnColumnSizes, 0, sizeof(int) * EXPECTED_PLALINDROME_COUNTER);
    step(s, strlen(s), 0, subStr, 0, *returnColumnSizes);
    *returnSize = finalReturnSize;
    return finalRes;
}
