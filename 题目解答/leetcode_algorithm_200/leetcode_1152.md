### 题目
```
给定两个字符串数组 username 和 website 和一个整数数组 timestamp 。给定的数组长度相同，其中元组 [username[i], website[i], timestamp[i]] 表示用户 username[i] 在时间 timestamp[i] 访问了网站 website[i] 。

访问模式 是包含三个网站的列表(不一定是完全不同的)。

例如，["home"， "away"， "love"]， ["leetcode"， "love"， "leetcode"]，和 ["luffy"， "luffy"， "luffy"] 都是模式。
一种 访问模式 的 得分 是访问该模式中所有网站的用户数量，这些网站在该模式中出现的顺序相同。

例如，如果模式是 [“home”，“away”，“love”] ，那么分数就是用户数量 x , x 访问了 “home” ，然后访问了 “away” ，然后访问了 “love” 。
同样，如果模式是 ["leetcode"， "love"， "leetcode"] ，那么分数就是用户数量 x ，使得 x 访问了"leetcode"，然后访问了 "love" ，之后又访问了 "leetcode" 。
另外，如果模式是 [“luffy”，“luffy”，“luffy”] ，那么分数就是用户数量 x ，这样 x 就可以在不同的时间戳上访问 “luffy” 三次。
返回 得分 最大的 访问模式 。如果有多个访问模式具有相同的最大分数，则返回字典序最小的。

输入：username = ["joe","joe","joe","james","james","james","james","mary","mary","mary"], timestamp = [1,2,3,4,5,6,7,8,9,10], website = ["home","about","career","home","cart","maps","home","home","about","career"]
输出：["home","about","career"]
解释：本例中的元组是:
["joe","home",1],["joe","about",2],["joe","career",3],["james","home",4],["james","cart",5],["james","maps",6],["james","home",7],["mary","home",8],["mary","about",9], and ["mary","career",10].
模式("home", "about", "career") has score 2 (joe and mary).
模式("home", "cart", "maps") 的得分为 1 (james).
模式 ("home", "cart", "home") 的得分为 1 (james).
模式 ("home", "maps", "home") 的得分为 1 (james).
模式 ("cart", "maps", "home") 的得分为 1 (james).
模式 ("home", "home", "home") 的得分为 0(没有用户访问过home 3次)。

输入: username = ["ua","ua","ua","ub","ub","ub"], timestamp = [1,2,3,4,5,6], website = ["a","b","a","a","b","c"]
输出: ["a","b","a"]

```

### 思路
1. 通过3重循环把3个网站的名字通过字符串的形式连接起来，让后以此为key，建立与用户名之间的hash数组，并记录下该用户访问的次数。

### 代码
下面代码只有少部分用例通过
```
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct {
    char name[51];
    char website[11];
    int timestamp;
} Info;

int cmp(const void* a, const void* b)
{
    Info* aa = (Info*)a;
    Info* bb = (Info*)b;
    int ret = strcmp(aa->name, bb->name);
    if (ret == 0) {
        return aa->timestamp - bb->timestamp;
    }
    return ret;
}

#define KEY_LEN 50
struct HashObj {
    char key[KEY_LEN];
    int val;
    char lastName[50];
    UT_hash_handle hh;
};

char ** mostVisitedPattern(char ** username, int usernameSize, int* timestamp, int timestampSize, char ** website, int websiteSize, int* returnSize){
    Info* info = (Info*)calloc(usernameSize, sizeof(Info));
    for (int i = 0; i < usernameSize; i++) {
        strcpy(info[i].name, username[i]);
        strcpy(info[i].website, website[i]);
        info->timestamp = timestamp[i];
    }
    qsort(info, usernameSize, sizeof(info[0]), cmp);
    *returnSize = 0;
    struct HashObj* users = NULL;
    int max = 0;
    char* maxKey;
    int l = 0;
    int r = 0;
    char** result = (char**)calloc(3, sizeof(char*));
    for (int i = 0; i < 3; i++) {
        result[i] = (char*)calloc(11, sizeof(char));
    }
    while (r <= usernameSize) { // 遍历所有用户
        if (r != usernameSize && strcmp(info[r].name, info[l].name) == 0) {
            r++;
            continue; // 找到不相同的元素
        }
        // 把3个网站名字连起来。
        for (int i = 0; i < r - 2; i++) {
            for (int j = i + 1; j < r - 1; j++) { // 一定要从 i + 1 开始
                for (int k = j + 1; j < r; k++) { // 一定要从就+ 1开始
                    char* combine = (char*)calloc(KEY_LEN, sizeof(char));
                    sprintf(combine, "%s#%s#%s", info[i].website, info[j].website, info[k].website);
                    printf("%s\n", combine);
                    struct HashObj* find;
                    HASH_FIND_STR(users, combine, find);
                    if (find == NULL) {
                        struct HashObj* add = (struct HashObj*)calloc(1, sizeof(struct HashObj));
                        strcpy(add->key, combine);
                        strcpy(add->lastName, info[i].name);
                        add->val = 1;
                        HASH_ADD_STR(users, key, add);
                    } else if (strcmp(info[i].name, find->lastName) == 0) {
                        continue;
                    }
                    find->val++;
                    strcpy(find->lastName, info[i].name);

                    if (find->val > max || find->val == max && strcmp(combine, maxKey) < 0) {
                        max = find->val;
                        strcpy(result[0], info[i].website);
                        strcpy(result[1], info[j].website);
                        strcpy(result[2], info[k].website);
                        maxKey = combine;
                    }
                }
            }
        }
        l = r;
        r++;
    }
    *returnSize = 3;
    return result;
}
```
