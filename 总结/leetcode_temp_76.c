struct HashObj {
    int key;
    int times;
    UT_hash_handle hh;
};

struct HashObj* g_usersNeed;
struct HashObj* g_window;

char * minWindow(char * s, char * t){
    if (s == NULL || t == NULL || strlen(t) > strlen(s)) {
        return NULL;
    }    
    char* result = (char*)malloc(sizeof(char) * (strlen(s) + 1));
    memset(result, 0, sizeof(char) * (strlen(s) + 1));
    struct HashObj* add;
    struct HashObj* find;
    int targetSize = 0;

    for (int i = 0; i < strlen(t); i++) {
        int key = t[i];
        HASH_FIND_INT(g_usersNeed, &key, find);
        if (find == NULL) {
            add = (struct HashObj*)malloc(sizeof(struct HashObj));
            add->key = t[i];
            add->times = 1;
            HASH_ADD_INT(g_usersNeed, key, add);
            targetSize++;
        } else {
            find->times++;
        }
    } 
    int right = 0;
    int match = 0;
    int minLength = INT_MAX;
    int left = 0;
    int start = 0;
    while (right < strlen(s)) {
        int c1 = s[right];
        int key = c1;
        HASH_FIND_INT(g_usersNeed, &key, find);
        if (find != NULL) {
            add = (struct HashObj*)malloc(sizeof(struct HashObj));
            add->key = c1;
            add->times = 1;
            HASH_ADD_INT(g_window, key, add);
            int winKey = c1;
            struct HashObj* winFind;
            HASH_FIND_INT(g_window, &winKey, winFind);
            if (find->times == winFind->times) {
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
            find = NULL;
            HASH_FIND_INT(g_usersNeed, &c2, find);
            struct HashObj* winFind1;
            HASH_FIND_INT(g_window, &c2, winFind1);
            if (find != NULL) {
                find->times--;
                if (find->times > winFind1->times) {
                    match--;
                }
            }
            left++;
        }
    }
    if (minLength == INT_MAX) {
        return NULL;
    } else {
        strncpy(result, &s[start], minLength);
    }
    return result;
}
