
算法思路是：
1、把target中的字母先通过hash进行存储，具体获取有多少种字符，每个字符的个数

2、使用滑窗思想，右指针逐个移动，如果这个元素在 target中，则把它放到window中。在放入window的时候，检查一下，看看该字符在window中是否存在，如果存在，则把它出现的次数加1，否则，申请hash节点内存

把该元素放进去。

3、计算当前该元素在target 和 window中出现的次数是否一样，如果一样，则把match增加

4、使match等于 target中的元素种类， 在这种情况下，计算最短子串的起始位置 和 长度，再把左指针 left从0开始移动，如果指向的元素在 target中，那么从window中移除该元素，具体操作是把它出现的次数减1

接下来判断，该元素在window中出现的次数和在target中出现的次数，如果前者小于后者，则说明已经不匹配了，需要把match减1

5、当有指针移动到末尾时就结束，查看最小的长度，然后把相应的字符填充到返回内存中，返回

struct HashObj {
    int key;
    int times;
    UT_hash_handle hh;
};

struct HashObj* g_usersNeed;
struct HashObj* g_window;

char * minWindow(char * s, char * t){
    if (s == NULL || t == NULL || strlen(t) > strlen(s)) {
        return "";
    }  
    g_usersNeed = NULL;
    g_window = NULL;
    char* result = (char*)malloc(sizeof(char) * (strlen(s) + 1));
    memset(result, 0, sizeof(char) * (strlen(s) + 1));

    for (int i = 0; i < strlen(t); i++) {
        struct HashObj* add;
        struct HashObj* find;
        int key = t[i];

        HASH_FIND_INT(g_usersNeed, &key, find);
        if (find == NULL) {
            add = (struct HashObj*)malloc(sizeof(struct HashObj));
            add->key = t[i];
            add->times = 1;
            HASH_ADD_INT(g_usersNeed, key, add);
        } else {
            find->times++;
        }
    } 

    int right = 0;
    int left = 0;
    int match = 0;
    int start = 0;
    int minLength = INT_MAX;
    while (right < strlen(s)) {
        int c1 = s[right];
        int key = c1;
        struct HashObj* find;
        struct HashObj* windFind;
        HASH_FIND_INT(g_usersNeed, &key, find);
        if (find != NULL) { // 说明在target中有,要把该key添加到window中，再添加之前，先查询有没有该key，没有，则添加，否则，增加times
            HASH_FIND_INT(g_window, &c1, windFind);
            if (windFind == NULL) {
                struct HashObj* add;
                add = (struct HashObj*)malloc(sizeof(struct HashObj));
                add->key = c1;
                add->times = 1;
                HASH_ADD_INT(g_window, key, add);
            } else {
                windFind->times++;
            }
            struct HashObj* calcTimes;
            HASH_FIND_INT(g_window, &c1, calcTimes);
            if (find->times == calcTimes->times) {
                match++;
            }
        }
        right++;
        while (match == HASH_COUNT(g_usersNeed)) {
            if (right - left < minLength) {
                start = left;
                minLength = right - left;
            }
            int c2 = s[left];
            struct HashObj* find;
            HASH_FIND_INT(g_usersNeed, &c2, find);// 移动左边指针，看看左边指针所指向的是否在target

            struct HashObj* winFind1;
            HASH_FIND_INT(g_window, &c2, winFind1);
            if (find != NULL) { // 在target里面
                winFind1->times--; // 从window中移除,这里的移除是把出现的次数降低
                if (find->times > winFind1->times) { // 当c2在window中的计数，小于target中的计数时，就要停止移动左边的。
                    match--;
                }
            }
            left++;
        }
    }
    #if 0 // 有前面初始化成NULL后，这里就可以不要了。
    struct HashObj* cur1;
    struct HashObj* tmp1;
    HASH_ITER(hh, g_usersNeed, cur1, tmp1) {
        HASH_DEL(g_usersNeed, cur1);
        free(cur1);
    }
    struct HashObj* cur2;
    struct HashObj* tmp2;
    HASH_ITER(hh, g_window, cur2, tmp2) {
        HASH_DEL(g_window, cur2);
        free(cur2); 
    }
    #endif
    if (minLength == INT_MAX) {
        return "";
    } else {
        strncpy(result, &s[start], minLength);
    }
    return result;
}
