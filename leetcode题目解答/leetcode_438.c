/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char * s, char * p, int* returnSize){
    *returnSize = 0;
    int hashNeeds[26] = {0}; // 这里注意，用例输入的字符串较长，这里char类型存不下，才使用int类型的。
    int hashWindon[26] = {0};
    int* res = (int*)malloc(sizeof(int) * 20101);
    memset(res, 0, sizeof(int) * 20101);

    for (int i = 0; i < strlen(p); i++) {
        hashNeeds[p[i] - 'a']++;
    }
    int charNumber = 0;
    for (int i = 0; i < 26; i++) {
        if (hashNeeds[i] != 0) {
            charNumber++; // target中存在的字符有几个。
        }
    }

    int left = 0;
    int right  = 0;
    int match = 0;
    int start = 0;
    while(right < strlen(s)) {
        char c1 = s[right];
        if (hashNeeds[c1 - 'a']) { // 注意一定要在target中的字符，才往Windows中放，其他的不要放进来。
            hashWindon[c1 - 'a']++;
            if (hashNeeds[c1 - 'a'] == hashWindon[c1 - 'a']) {
                match++;
            }
        }
        right++;
        while (match == charNumber) { // 这里使用的是hash，匹配的，要匹配完target中的字符
            if (right - left == strlen(p)) {// 把窗口缩放到刚好target字符串的长度。
                start = left;
                res[(*returnSize)++] = start;
            }
            char c2 = s[left];
            if (hashNeeds[c2 - 'a']) {这里同样的，要是在target中的字符，才在这里从Windows中减去。
                hashWindon[c2 - 'a']--;
                if (hashNeeds[c2 - 'a'] > hashWindon[c2 - 'a']) {
                    match--;
                }
            }
            left++;
        }
    }
    return res;
}
