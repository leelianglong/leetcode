/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: 使用 hlist.h hhash.h 实现 LRU 缓存机制
 *              原题：leetcode 146 (https://leetcode-cn.com/problems/lru-cache)
 * Create: 2019-11-11
 * Contact: http://rnd-isource.huawei.com/bugs/hw-cstl
 * Note: 接口定义受限于 leetcode，可能不符合《编程规范》要求
 */

#include "hlist.h"
#include "hhash.h"

typedef struct {
    int capacity;
    int curCnt;
    struct List recent;     // 用链表记录"最近使用"顺序；tail 最近
    struct HashTable ht;    // 用 HASH 实现快速查找
} LRUCache;

typedef struct {
    struct Node nodeInList;
    struct Node nodeInHash;
    int key;
    int value;
} LRUNode;

static size_t HashBktSize(int capacity)
{
    size_t bktSize = capacity / 4;     // 可能不是性能最佳，未测试
    bktSize = bktSize < 4 ? 4 : bktSize;
    return bktSize;
}

static bool HashEqual(const struct Node *a, const struct Node *b)
{
    LRUNode *na = NODE_ENTRY(a, LRUNode, nodeInHash);
    LRUNode *nb = NODE_ENTRY(b, LRUNode, nodeInHash);
    return na->key == nb->key;
}

static size_t HashKey(const struct Node *node, size_t bktSize)
{
    LRUNode *n = NODE_ENTRY(node, LRUNode, nodeInHash);
    size_t k = TwIntHash((unsigned int)n->key);
    return k % bktSize;
}

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache = (LRUCache*)malloc(sizeof(LRUCache));
    if (cache == NULL) { return NULL; }
    cache->capacity = capacity;
    cache->curCnt = 0;
    ListInit(&cache->recent);

    size_t bktSize = HashBktSize(capacity);
    int ret = HashInit(&cache->ht, bktSize, HashEqual, HashKey);
    if (ret != 0) {
        free(cache);
        return NULL;
    }
    return cache;
}

int lRUCacheGet(LRUCache *lru, int key)
{
    LRUNode cmpNode = { .key = key };
    struct Node *node = HashFind(&lru->ht, &cmpNode.nodeInHash);
    if (node == NULL) { return -1; }

    // 按题意，get 操作也属于"使用"
    LRUNode *entry = NODE_ENTRY(node, LRUNode, nodeInHash);
    ListRemove(&entry->nodeInList);
    ListAddTail(&lru->recent, &entry->nodeInList);
    return entry->value;
}

void lRUCachePut(LRUCache *lru, int key, int value)
{
    LRUNode *entry;
    LRUNode cmpNode = { .key = key };
    struct Node *node = HashFind(&lru->ht, &cmpNode.nodeInHash);
    if (node != NULL) {
        entry = NODE_ENTRY(node, LRUNode, nodeInHash);
        ListRemove(&entry->nodeInList);
    } else {
        if (lru->curCnt < lru->capacity) {
            entry = (LRUNode*)malloc(sizeof(LRUNode));
            if (entry == NULL) { return; }
            lru->curCnt++;
        } else {
            // 重复利用本来要被丢弃的节点
            entry = LIST_HEAD_ENTRY(&lru->recent, LRUNode, nodeInList);
            if (entry == NULL) { return; }
            ListRemove(&entry->nodeInList);
            HashRemove(&entry->nodeInHash);
        }
        entry->key = key;
        HashAdd(&lru->ht, &entry->nodeInHash);
    }
    entry->value = value;
    ListAddTail(&lru->recent, &entry->nodeInList);
}

static void FreeListNode(struct Node *node)
{
    LRUNode *entry = NODE_ENTRY(node, LRUNode, nodeInList);
    free(entry);
}

void lRUCacheFree(LRUCache *lru)
{
    HashDeinit(&lru->ht, NULL); // LRUNode 只能释放一次
    ListDeinit(&lru->recent, FreeListNode);
    free(lru);
}

