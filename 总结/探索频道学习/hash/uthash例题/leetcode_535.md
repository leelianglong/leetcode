### leetcode 535
#### 思路
1. hash 实际上也可以通过数组模拟，再传入一个长的URL时，根据rand()在 seed中随机选择6个字符，再加上固定前缀 http://tinyurl.com/ 组成一个可以
2. 使用这个key来关联这个长的URL。 把这个key放在数组中，并把它关联的完整的URL也放在数组中。
3. 编码的返回结果就是http://tinyurl.com/XXXXXX。
4. 解码的时候，就是在数组中找寻上面编码返回的字符串作为key，找到其对应的完整URL。
#### 代码
```
#define COUNT 10000
typedef struct {
    char key[26];
    char val[5000];
} Hash;

Hash obj[COUNT] = {0};

const char* seed = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool hasKey(char* key)
{
    for (int i = 0; i < COUNT; i++) {
        if (strcmp(obj[i].key, key) == 0) {
            return true;
        }
    }
    return false;
}

/** Encodes a URL to a shortened URL. */
char* encode(char* longUrl) {
    char key[7] = {0};
    do {
        for (int i = 0; i < 6; i++) {
            key[i] = seed[rand() % 62];
        } 
    } while (hasKey(key)); // 找到一个单独的key

    char* hashKey = (char*)malloc(sizeof(char) * 26);
    memset(hashKey, 0, sizeof(char) * 26);
    sprintf(hashKey, "http://tinyurl.com/%s", key);  
    for (int i = 0; i < COUNT; i++) {
        if (strlen(obj[i].key) == 0) { // 找到一个空位把这个key填充进来
            strcpy(obj[i].key, hashKey);
            strcpy(obj[i].val, longUrl);
            break;
        }
    } 
    return hashKey;
}

/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl) {
    for (int i = 0; i < COUNT; i++) {
        if (strcmp(obj[i].key, shortUrl) == 0) {
            return obj[i].val;
        }
    }
    return shortUrl;
}
```

#### 使用UT_HASH的版本
```
/*
### 题目 leetcode 535
1.tinyurl的基本原理如下：
https://blog.csdn.net/bdss58/article/details/74784428/
2.相当于是使用6个随机的字符对应一个URL地址。
3.使用固定的http://tinyurl.com/ 和 6个随机字符，够成一个key, 对应一个标准的URL，把它放在hash表中，压缩的过程就是返回这个key.
4.解压的过程就是，通过上面的key把标准的URL找出来。
*/

struct HashObj {
    char key[26];
    char* url;
    UT_hash_handle hh;
};
struct HashObj* users;
char base[] = {"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
/** Encodes a URL to a shortened URL. */
char* encode(char* longUrl) {
    char fixPre[] = "http://tinyurl.com/";
    char chooseSixCha[7] = {0};
    for (int i = 0; i < 6; i++) {
        chooseSixCha[i] = base[rand() % 62]; // 这里对62取余的原因在于上面base中有62个字符。rand() 大小是100以内的随机数？？？，目的在于随机取出6个字符和固定的前缀来表示一个URL。
    }
    char* res;
    char key[26] = {0};
    strcpy(key, fixPre);
    strcpy(&key[19], chooseSixCha);
    struct HashObj* find;
    HASH_FIND_STR(users, key, find);
    if (find == NULL) {
        struct HashObj* add = (struct HashObj*)malloc(sizeof(struct HashObj));
        strcpy(add->key, key);
        add->url = (char*)malloc(sizeof(char) * (strlen(longUrl) + 1));
        memset(add->url, 0, sizeof(char) *  (strlen(longUrl) + 1));
        strcpy(add->url, longUrl);
        HASH_ADD_STR(users, key, add); // 把key 和 标准的URL存入hash，解密时，根据这个key获取标准的URL。
        res = (char*)malloc(sizeof(char) * 26);
        memset(res, 0, sizeof(char) * 26);
        strcpy(res, key);
    }
    return res;
}

/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl) {
    char* res;
    char key[26] = {0};
    strcpy(key, shortUrl);
    struct HashObj* find;
    HASH_FIND_STR(users, key, find);
    if (find != NULL) {
        res = (char*)malloc(sizeof(char) * (1 + strlen(find->url)));
        memset(res, 0, sizeof(char) *(1 + strlen(find->url)));
        strcpy(res, find->url);
    }
    return res;
}
```