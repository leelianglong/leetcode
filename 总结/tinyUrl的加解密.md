### 题目 leetcode 535
1.tinyurl的基本原理如下：
https://blog.csdn.net/bdss58/article/details/74784428/
2.相当于是使用6个随机的字符对应一个URL地址。
3.使用固定的http://tinyurl.com/ 和 6个随机字符，够成一个key, 对应一个标准的URL，把它放在hash表中，压缩的过程就是返回这个key.
4.解压的过程就是，通过上面的key把标准的URL找出来。

### 代码
```
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
    //printf("\nL=%s", longUrl);
    //printf("\nH=%s", chooseSixCha);
    char* res;
    char key[26] = {0};
    strcpy(key, fixPre);
    strcpy(&key[19], chooseSixCha);
    //printf("\nKey=%s", key);
    struct HashObj* find;
    HASH_FIND_STR(users, key, find);
    if (find == NULL) {
        //printf("\n not find");
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
    //printf("\nencode:%s", res);
    return res;
}

/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl) {
    char* res;
    char key[26] = {0};
    //printf("\ndecode shortURL=%s", shortUrl);
    strcpy(key, shortUrl);
    struct HashObj* find;
    //printf("\ndecode key=%s", key);
    HASH_FIND_STR(users, key, find);
    if (find != NULL) {
        //printf("\n decode find it");
        //printf("\n decode find url=%s", find->url);
        res = (char*)malloc(sizeof(char) * (1 + strlen(find->url)));
        memset(res, 0, sizeof(char) *(1 + strlen(find->url)));
        strcpy(res, find->url);
    }
    //printf("\n decode find res=%s", res);
    return res;
}

// Your functions will be called as such:
// char* s = encode(s);
// decode(s);
```
