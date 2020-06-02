/*
* 字符串的处理。
* 根据规则处理电话号码 和 邮箱地址的隐藏
*/

#define PRE_LENGTH 7
#define START_LENGTH  5

int UpdatePreNum(char* s, int pos, char* pStr)
{
    const char star = '*';
    int index = 0;
    int offset = 0;

    if (isupper(s[index])) {
        offset = 'A' - 'a';
    }
    pStr[index] = s[index] - offset;
    index++;
    for (int i = 0; i < START_LENGTH; i++) {
        pStr[index++] = star;
    }
    offset = 0;
    if (islower(s[pos])) {
        offset = 'a' - 'A';
    }
    pStr[index] = s[pos] + offset;
    index++;
    return index;
}

char* UpdateMail(char* s)
{
    int length = strlen(s);
    const char *key = "@";
    char* match = strstr(s, key);
    int retLength = length - (match - s) + PRE_LENGTH + 1;
    char* ret = (char*)malloc(retLength);
    ret[retLength - 1] = 0;

    int index = UpdatePreNum(s, (match - s - 1), ret);
    int offset;
    for (int i = (match - s); i < length; i++) {
        offset = 0;
        if (isupper(s[i])) {
            offset = 'a' - 'A';
        }
        ret[index++] = s[i] + offset;
    }
    return ret;
}

int CounterOfNumber(char* s)
{
    int i = 0;
    int counter = 0;
    while (s[i] != '\0') {
        if (isdigit(s[i])) {
            counter++;
        }
        i++;
    }
    return counter;
}

#define DUPLATE_TIME 2
#define EACH_NUM   3
#define KEEP_SIZE  4
void UpdateLocalPhoneNum(char* ret, int* index, char* s, int numCounter)
{
    int length = strlen(s);
    for (int i = 0; i < DUPLATE_TIME; i++) {
        for (int j = 0; j < EACH_NUM; j++) {
            ret[(*index)] = '*';
            (*index)++;
        }
        ret[(*index)] = '-';
        (*index)++;
    }

    for (int i = 0; i < length; i++) {
        if (numCounter > KEEP_SIZE) {
            if (isdigit(s[i])) {
                numCounter--;
            }
            continue;
        }
        if (isdigit(s[i])) {
            ret[(*index)] = s[i];
            (*index)++;
        }
    }
}

#define LOCAL_NUM 10
#define LOCAL_EXTRA 2
#define NATIONAL_EXTRA 3

void UpdateInternationalPhoneNum(char* ret, int* index, char* s, int length)
{
    ret[(*index)] = '+';
    (*index)++;
    for (int i = 0; i < (length - LOCAL_NUM - LOCAL_EXTRA - NATIONAL_EXTRA); i++) {
        ret[(*index)] = '*';
        (*index)++;
    }
    ret[(*index)] = '-';
    (*index)++;
}

char* UpdatePhoneNum(char* s)
{
    bool local = true;
    int length = strlen(s);
    int extLength = LOCAL_EXTRA;
    int numCOunter = CounterOfNumber(s);
    int totalNumLen = numCOunter;

    if (totalNumLen > LOCAL_NUM) {
        local = false;
        extLength += LOCAL_EXTRA;
    }
    totalNumLen += extLength;
    char* ret = (char*)malloc(sizeof(char) * (totalNumLen + 1));
    ret[totalNumLen] = 0;
    int index = 0;
    if (!local) {
        UpdateInternationalPhoneNum(ret, &index, s,totalNumLen);
    }
    UpdateLocalPhoneNum(ret, &index, s, totalNumLen);
    return ret;

}

char * maskPII(char * S){
    if (isalpha(S[0])) {
        return UpdateMail(S);
    }
    return UpdatePhoneNum(S);
}
