### leetcode 355
#### 思路
见代码注释
#### 代码
```
typedef struct __TwiterList {
    int userId;
    int twiterId;
    struct __TwiterList* next;
} TwiterList; // 用链表存储每条推特，推特的插入采用头插法。

typedef struct {
    int followeeId;
    UT_hash_handle hh;
}Followee;// 关注者列表

typedef struct {
    int userId;
    Followee* hash; // 这个是关键，把关注者也拿到Twitter列表里面了。那么在计算最近的10条信息时，就可以先搜自己，自己没发，就遍历自己关注的。
    UT_hash_handle hh;
} PostTwiter;

typedef struct {
    TwiterList* twlist;
    PostTwiter* pTw;
} Twitter;


Twitter* twitterCreate() {
    Twitter* obj = (Twitter*)malloc(sizeof(Twitter));
    obj->twlist = NULL;
    obj->pTw = NULL;
    return obj;
}

void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    PostTwiter* hasSent;
    HASH_FIND_INT(obj->pTw, &userId, hasSent);
    if (hasSent == NULL) {
        PostTwiter* add = (PostTwiter*)malloc(sizeof(PostTwiter));
        add->userId = userId;
        add->hash = NULL;
        HASH_ADD_INT(obj->pTw, userId, add); // 先把自己加到Twitter里
    }
    // 自己发送一个Twitter。
    TwiterList* tmpTw = (TwiterList*)malloc(sizeof(TwiterList));
    tmpTw->userId = userId;
    tmpTw->twiterId = tweetId;
    tmpTw->next = NULL;
    if (obj->twlist == NULL) {
        obj->twlist = tmpTw;
    } else {
        tmpTw->next = obj->twlist; //头插法。把这条Twitter加入链表中。
        obj->twlist = tmpTw; 
    }
}

#define RETURN_SIZE 10
int* twitterGetNewsFeed(Twitter* obj, int userId, int* retSize) {
    TwiterList* node = obj->twlist; // 获取Twitter 列表。
    int* res = (int*)malloc(sizeof(int) * RETURN_SIZE);
    memset(res, 0, sizeof(int) * RETURN_SIZE);
    *retSize = 0;
    PostTwiter* find;
    Followee* findFollowee;
    HASH_FIND_INT(obj->pTw, &userId, find);
    if (find == NULL) { //当前用户没有发Twitter。
        return res;
    }
    while (node != NULL && (*retSize) < RETURN_SIZE) {
        if (node->userId == userId) {
            res[(*retSize)] = node->twiterId;
            (*retSize)++;
        } else {
            HASH_FIND_INT(obj->pTw->hash, &node->userId, findFollowee);
            if (findFollowee != NULL) {
                res[(*retSize)++] = node->twiterId;
            }
        }
        node = node->next;
    }
    return res;
}

void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    PostTwiter* find;
    Followee* findFollowee;
    HASH_FIND_INT(obj->pTw, &followerId, find);
    if (find == NULL) {
        PostTwiter* add = (PostTwiter*)malloc(sizeof(PostTwiter));
        add->userId = followerId;
        add->hash = NULL;
        HASH_ADD_INT(obj->pTw, userId, add); // 先添加到推特
    }
    // 在添加到关注列表
    HASH_FIND_INT(obj->pTw->hash, &followeeId, findFollowee);
    if (findFollowee == NULL) {
        Followee* add = (Followee*)malloc(sizeof(Followee));
        add->followeeId = followeeId;
        HASH_ADD_INT(obj->pTw->hash, followeeId, add);
    }
}

void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    PostTwiter* find;
    HASH_FIND_INT(obj->pTw, &followerId, find);
    if (find != NULL) {
        Followee* findFollowee;
        HASH_FIND_INT(obj->pTw->hash, &followeeId, findFollowee);
        if (findFollowee != NULL) {
            HASH_DEL(obj->pTw->hash, findFollowee);
            free(findFollowee);
        }
    }
}

void FreeTwiterlist(Twitter* obj)
{
    TwiterList* head = obj->twlist;
    while (head) {
        TwiterList* tmp = head;
        head = head->next;
        free(tmp);
        tmp = NULL;
    }
}

void FreeFollowee(Twitter* obj)
{
    Followee* cur;
    Followee* tmp;
    if (obj->pTw == NULL) {
        return;
    }
    if (obj->pTw->hash == NULL) {
        return;
    }
    HASH_ITER(hh, obj->pTw->hash, cur, tmp) {
        HASH_DEL(obj->pTw->hash, cur);
        free(cur);
    }
}

void FreeTwiter(Twitter* obj)
{
    PostTwiter* cur;
    PostTwiter* tmp;
    if (obj->pTw == NULL) {
        return;
    }
    HASH_ITER(hh, obj->pTw, cur, tmp) {
        HASH_DEL(obj->pTw, cur);
        free(cur);
    }
}

void twitterFree(Twitter* obj) {
    FreeTwiterlist(obj);
    FreeFollowee(obj);
    FreeTwiter(obj);
    free(obj);
}

/**
 * Your Twitter struct will be instantiated and called as such:
 * Twitter* obj = twitterCreate();
 * twitterPostTweet(obj, userId, tweetId);
 
 * int* param_2 = twitterGetNewsFeed(obj, userId, retSize);
 
 * twitterFollow(obj, followerId, followeeId);
 
 * twitterUnfollow(obj, followerId, followeeId);
 
 * twitterFree(obj);
*/
```