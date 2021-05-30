### leetcode 146
#### 思路
1. LRU（least recent used）最近最少使用的，实际上是一种缓存淘汰策略，也就是说我们认为最近使用的是有用的，很久没有使用的被认为是无用的，当缓存满了的时候，需要把没有用的缓存删除，腾出空间用来装新的。
2. 当前算法需要提供2个接口：get(key), put(key, val),即根据key要获取值，或者根据key,val把他们放入缓存。这里的get() 和 put都需要在O(1)的时间复杂度下获取。
3. 缓存的中数据需要有序，需要区别出有用和无用的，可以使用一个队列，把最近使用的放在队头，把不用的放在队尾。这里有添加删除的操作，可以使用链表，操作方便。
4. get要满足O(1),则需要hash，根据key直接得到val。所以当前算法需要结合链表和hash来实现。

#### 代码
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/********************************链表 操作*****************************************/
struct LinkListNode {
    int key;
    int val;
    struct LinkListNode* pre;
    struct LinkListNode* next;
};

struct LinkListNode* LL_CreateNode(int key, int val)
{
    struct LinkListNode* res = (struct LinkListNode*)malloc(sizeof(struct LinkListNode));
    memset(res, 0, sizeof(struct LinkListNode));
    res->key = key;
    res->val = val;
    return res;
}

void LL_AddFirstNode(struct LinkListNode* head, struct LinkListNode* nxtNode)
{
    nxtNode->pre = head;
    nxtNode->next = head->next;
    head->next->pre = nxtNode;
    head->next = nxtNode; // 典型的双向链表插入操作。把nxtNode插到head后面。
}

void LL_RemoveNode(struct LinkListNode* delNode)
{
    delNode->next->pre = delNode->pre;
    delNode->pre->next = delNode->next;
    free(delNode);
}

void LL_MoveNode(struct LinkListNode* from, struct LinkListNode* to)
{
    from->pre->next = from->next;
    from->next->pre = from->pre;
    from->next = to->next;
    from->pre = to;
    to->next->pre = from;
    to->next = from;
}


/********************************hash 操作*****************************************/
#define HASH_SIZE 2048
#define HASH_EMPTY -1
#define HASH_KEY int
#define HASH_VAL struct LinkListNode* // val的类型，双链表节点

struct HashNode {
    HASH_KEY key;
    HASH_VAL val;
    struct HashNode* next; // hash冲突解决
};

struct HashNode* Hash_CreateNode(HASH_KEY key, HASH_VAL val, struct HashNode* next)
{
    struct HashNode* obj = (struct HashNode*)malloc(sizeof(struct HashNode));
    obj->key = key;
    obj->val = val;
    obj->next = next; // 头插法
    return obj;
}

struct HashNode** Hash_InitObj(void)
{
    struct HashNode** obj = (struct HashNode**)malloc(sizeof(struct HashNode*) * HASH_SIZE);
    for (int i = 0; i < HASH_SIZE; i++) {
        obj[i] = Hash_CreateNode(HASH_EMPTY, 0, NULL);
    }
    return obj;
}

int Hash_CalcuSeed(HASH_KEY key)
{
    if (key == INT_MIN) {
        key = INT_MAX;
    } else if (key < 0 ) {
        key = -key;
    }
    return key % HASH_SIZE;
}

bool Hash_PutNode(struct HashNode** obj, HASH_KEY key, HASH_VAL val)
{
    int hash = Hash_CalcuSeed(key);
    struct HashNode* curNode = obj[hash];
    if (curNode->key == HASH_EMPTY) { // 当前key在hash表中不存在，则直接添加。
        curNode->key = key;
        curNode->val = val;
        return true;
    }

    while (true) {
        if(curNode->key == key) { // 当前的key已经存在，则覆盖原有的数据， 返回false。
            curNode->val = val;
            return false;
        }
        if(curNode->next == NULL) {
            break;
        }
        curNode = curNode->next;
    }
    curNode->next = Hash_CreateNode(key, val, NULL); // 找到结束的位置，然后把这个key添加进来。
    return true;
}

bool Hash_GetNode(struct HashNode** obj, HASH_KEY key, HASH_VAL* result)
{
    int hash = Hash_CalcuSeed(key);
    struct HashNode* curNode = obj[hash];
    while (curNode != NULL && curNode->key != HASH_EMPTY) {
        if (curNode->key == key) {
            *result = curNode->val;
            return true;
        }
        curNode = curNode->next;
    }
    result = NULL;
    return false;
}

bool Hash_RemoveNode(struct HashNode** obj, HASH_KEY key)
{
    int hash = Hash_CalcuSeed(key);
    struct HashNode* curNode = obj[hash];
    if (curNode->key == key) {
        if (curNode->next == NULL) { // 要删除下一个节点，当前节点的下一个节点不存在了，可以直接把当前节点的key设置成空
            curNode->key = HASH_EMPTY;
            curNode->val = 0;
            return true;
        } else {
            struct HashNode* delNode = curNode->next; // 要删除的是当前节点的下一个。
            curNode->val = curNode->next->val;
            curNode->key = curNode->next->key;
            curNode->next = curNode->next->next; // 这样就把delNode删除了
            free(delNode);
            return true;
        }
    }
    // 当前key节点对应的hash值对应的节点中的key和这个参数key不一样，说明有冲突了，需要继续找。
    while (curNode->next != NULL) {
        struct HashNode* next = curNode->next;
        if (next->key == key) {
            curNode->next = next->next;
            free(next);
            return true;
        }
        curNode = curNode->next;
    }
    return false;
}

typedef struct {
    int count;
    int capacity;
    struct LinkListNode* head;
    struct LinkListNode* tail;
    struct HashNode** hashMap; // map中的val存储了struct LinkListNode* 节点
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* res = (LRUCache* )malloc(sizeof(LRUCache));
    res->hashMap = Hash_InitObj();
    res->capacity = capacity;
    res->count = 0;
    res->head = LL_CreateNode(HASH_EMPTY, 0);
    res->tail = LL_CreateNode(HASH_EMPTY, 0);
    res->head->next = res->tail;
    res->tail->pre = res->head;
    return res;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if (obj->capacity == 0) {
        return -1;
    }
    struct LinkListNode* resNode;
    Hash_GetNode(obj->hashMap, key, &resNode); // 根据key在hash中找到val。
    if (!resNode) {
        return -1;
    }
    LL_MoveNode(resNode, obj->head); // 把当前使用的这个key对应的节点移动到缓存的头部，因为它刚用了。
    return resNode->val;
}

void lRUCacheTailOut(LRUCache* obj)
{
    if (obj->count < obj->capacity) { // 容量未满不用淘汰
        obj->count++;
        return;
    }
    struct LinkListNode* delNode = obj->tail->pre; // 把最后的节点拿出来，它是要删除的 
    Hash_RemoveNode(obj->hashMap, delNode->key); // 把hash中的这个节点删除
    LL_RemoveNode(delNode); // 把链表中的这个节点也删除
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj->capacity == 0) {
        return;
    }
    struct LinkListNode* putNode;
    Hash_GetNode(obj->hashMap, key, &putNode); // 先在hash中查找key,
    if (putNode) { // 找到了，就把它提到链表头表示最近使用的，并且修改它的val值。
        putNode->val = value;
        LL_MoveNode(putNode, obj->head);
        return;
    }
    lRUCacheTailOut(obj); // 在hash中找不到，意味着缓存满了，需要把没有使用的移除。 并把基于这个key创建一个节点添加到缓存中
    putNode = LL_CreateNode(key, value);
    LL_AddFirstNode(obj->head, putNode);
    Hash_PutNode(obj->hashMap, key, putNode);
}

void lRUCacheFree(LRUCache* obj) {
    if (obj) {
        for (int i = 0; i < HASH_SIZE; i++) {
            free(obj->hashMap[i]);
        }
        free(obj->head);
        free(obj->tail);
        free(obj);
    }
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
```