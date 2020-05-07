/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: 简单 UT
 * Create: 2019-11-11
 * Contact: http://rnd-isource.huawei.com/bugs/hw-cstl
 */

#include <stdio.h>
#include "hlist.h"
#include "hhash.h"

/* For Test */

#define SHOULD(cond) \
    (void)printf("Line #%-3d ... ... %s\n", \
                 __LINE__, \
                 (cond) ? "OK." : "Failed!")

#define SHOULDNT(cond) SHOULD(!(cond))


/* Node */

struct DataEntry {
    int key;
    int value;
    struct Node node;
};

void TEST_NodeEntry(void)
{
    struct DataEntry e; /* Not used. */
    struct DataEntry *p;
    p = NODE_ENTRY(&e.node, struct DataEntry, node);
    SHOULD(p == &e);
}

#define MAXN 100
static struct DataEntry *GetEntryArray(int cnt)
{
    static struct DataEntry entries[MAXN];
    SHOULD(cnt <= MAXN);

    int i;
    for (i = 0; i < cnt; i++) {
        struct DataEntry *entry = &entries[i];
        entry->key = i;
        entry->value = i;
        entry->node.next = NULL;
        entry->node.prev = NULL;
    }
    return entries;
}

/* List */

void TEST_ListInit(void)
{
    struct List list;
    ListInit(&list);
    SHOULD(ListEmpty(&list));
    // No need ListDeinit here.
}

void TEST_ListInsert(void)
{
    struct List list;
    ListInit(&list);

    struct DataEntry *n = GetEntryArray(3);
    ListAddHead(&list, &n[0].node);
    ListAddTail(&list, &n[2].node);
    ListInsert(&n[2].node, &n[1].node);  /* -> 0..1..2 */

    SHOULD(list.base.next == &n[0].node);
    SHOULD(n[0].node.next == &n[1].node);
    SHOULD(n[1].node.next == &n[2].node);
    SHOULD(n[2].node.next == &list.base);

    SHOULD(ListIsHead(&list, &n[0].node));
    SHOULDNT(ListIsTail(&list, &n[0].node));

    SHOULDNT(ListIsHead(&list, &n[1].node));
    SHOULDNT(ListIsTail(&list, &n[1].node));

    SHOULDNT(ListIsHead(&list, &n[2].node));
    SHOULD(ListIsTail(&list, &n[2].node));
    // No need ListDeinit here.
}

void TEST_ListRemove(void)
{
    struct List list;
    ListInit(&list);

    struct DataEntry *n = GetEntryArray(3);
    ListAddTail(&list, &n[0].node);
    ListAddTail(&list, &n[1].node);
    ListAddTail(&list, &n[2].node);         /* -> 0..1..2 */

    ListRemove(&n[1].node);                 /* -> 0..2 */
    SHOULD(n[0].node.next == &n[2].node);
    SHOULD(n[2].node.prev == &n[0].node);

    ListRemoveTail(&list);                  /* -> 0 */
    SHOULD(ListIsHead(&list, &n[0].node));
    SHOULD(ListIsTail(&list, &n[0].node));

    ListAddHead(&list, &n[1].node);         /* -> 1..0 */
    ListReplace(&n[0].node, &n[2].node);    /* -> 1..2 */
    SHOULD(ListIsHead(&list, &n[1].node));
    SHOULD(ListIsTail(&list, &n[2].node));
    // No need ListDeinit here.
}

void TEST_ListForEach(void)
{
    struct List list;
    ListInit(&list);

    struct DataEntry *n = GetEntryArray(3);
    ListAddTail(&list, &n[0].node);
    ListAddTail(&list, &n[1].node);
    ListAddTail(&list, &n[2].node);

    struct Node *node, *tmp;
    struct DataEntry *entry;
    int i = 0;
    LIST_FOR_EACH(node, &list) {
        entry = NODE_ENTRY(node, struct DataEntry, node);
        entry->value += i++;
    }
    SHOULD(i == 3);
    SHOULD(n[0].value == n[0].key + 0);
    SHOULD(n[1].value == n[1].key + 1);
    SHOULD(n[2].value == n[2].key + 2);

    LIST_FOR_EACH_SAFE(node, tmp, &list) {
        entry = NODE_ENTRY(node, struct DataEntry, node);
        entry->value += i++;
        ListRemove(node);
    }
    SHOULD(i == 6);
    SHOULD(ListEmpty(&list));
    SHOULD(n[0].value == n[0].key + 0 + 3);
    SHOULD(n[1].value == n[1].key + 1 + 4);
    SHOULD(n[2].value == n[2].key + 2 + 5);

    LIST_FOR_EACH(node, &list) {
        entry = NODE_ENTRY(node, struct DataEntry, node);
        entry->value += i++;
    }
    SHOULD(i == 6);
    // No need ListDeinit here.
}

/* 简单的 NodeFunc, 将 value 自增，以标记 */
static void NodeInc(struct Node *node)
{
    struct DataEntry *p = NODE_ENTRY(node, struct DataEntry, node);
    p->value++;
}

static void NodeIncX(struct Node *node, void *arg)
{
    struct DataEntry *p = NODE_ENTRY(node, struct DataEntry, node);
    int *pi = (int*)arg;
    p->value += *pi;
    (*pi)++;
}

void TEST_ListIterate(void)
{
    struct List list;
    ListInit(&list);

    struct DataEntry *n = GetEntryArray(3);
    struct DataEntry *entry;
    entry = LIST_HEAD_ENTRY(&list, struct DataEntry, node);
    SHOULD(entry == NULL);
    entry = LIST_TAIL_ENTRY(&list, struct DataEntry, node);
    SHOULD(entry == NULL);

    ListAddTail(&list, &n[0].node);
    ListAddTail(&list, &n[1].node);
    ListAddTail(&list, &n[2].node);

    int a = 0;
    ListIterate(&list, NodeIncX, &a);
    SHOULD(a == 3);
    SHOULD(n[0].value == n[0].key + 0);
    SHOULD(n[1].value == n[1].key + 1);
    SHOULD(n[2].value == n[2].key + 2);
    // No need ListDeinit here.
}

void TEST_ListDeinit(void)
{
    struct List list;
    ListInit(&list);

    struct DataEntry *n = GetEntryArray(3);
    ListAddTail(&list, &n[0].node);
    ListAddTail(&list, &n[1].node);
    ListAddTail(&list, &n[2].node);

    ListDeinit(&list, NodeInc);
    SHOULD(n[0].value == n[0].key + 1);
    SHOULD(n[1].value == n[1].key + 1);
    SHOULD(n[2].value == n[2].key + 1);
}

void TEST_ListEntry(void)
{
    struct List list;
    ListInit(&list);

    struct DataEntry *n = GetEntryArray(3);
    struct DataEntry *entry;
    entry = LIST_HEAD_ENTRY(&list, struct DataEntry, node);
    SHOULD(entry == NULL);
    entry = LIST_TAIL_ENTRY(&list, struct DataEntry, node);
    SHOULD(entry == NULL);

    ListAddTail(&list, &n[0].node);
    ListAddTail(&list, &n[1].node);
    ListAddTail(&list, &n[2].node);
    entry = LIST_HEAD_ENTRY(&list, struct DataEntry, node);
    SHOULD(entry == &n[0]);
    entry = LIST_NEXT_ENTRY(entry, &list, struct DataEntry, node);
    SHOULD(entry == &n[1]);
    entry = LIST_PREV_ENTRY(entry, &list, struct DataEntry, node);
    SHOULD(entry == &n[0]);
    entry = LIST_PREV_ENTRY(entry, &list, struct DataEntry, node);
    SHOULD(entry == NULL);
    entry = LIST_TAIL_ENTRY(&list, struct DataEntry, node);
    SHOULD(entry == &n[2]);
    entry = LIST_NEXT_ENTRY(entry, &list, struct DataEntry, node);
    SHOULD(entry == NULL);

    int i = 0;
    LIST_FOR_EACH_ENTRY(entry, &list, struct DataEntry, node) {
        entry->value += i++;
    }
    SHOULD(i == 3);
    SHOULD(n[0].value == n[0].key + 0);
    SHOULD(n[1].value == n[1].key + 1);
    SHOULD(n[2].value == n[2].key + 2);

    struct DataEntry *tmp;
    LIST_FOR_EACH_ENTRY_SAFE(entry, tmp, &list, struct DataEntry, node) {
        entry->value += i++;
        ListRemove(&entry->node);
    }
    SHOULD(i == 6);
    SHOULD(ListEmpty(&list));
    SHOULD(n[0].value == n[0].key + 0 + 3);
    SHOULD(n[1].value == n[1].key + 1 + 4);
    SHOULD(n[2].value == n[2].key + 2 + 5);

    LIST_FOR_EACH_ENTRY(entry, &list, struct DataEntry, node) {
        entry->value += i++;
    }
    SHOULD(i == 6);     /* 空表遍历 */
    LIST_FOR_EACH_ENTRY_SAFE(entry, tmp, &list, struct DataEntry, node) {
        entry->value += i++;
    }
    SHOULD(i == 6);     /* 空表遍历 */

    ListAddTail(&list, &n[0].node);
    ListAddTail(&list, &n[1].node);
    ListAddTail(&list, &n[2].node);
    LIST_FOR_EACH_ENTRY_REVERSE(entry, &list, struct DataEntry, node) {
        entry->value += i++;
    }
    SHOULD(i == 9);
    SHOULD(n[0].value == n[0].key + 0 + 3 + 8);
    SHOULD(n[1].value == n[1].key + 1 + 4 + 7);
    SHOULD(n[2].value == n[2].key + 2 + 5 + 6);

    LIST_FOR_EACH_ENTRY_REVERSE_SAFE(entry, tmp, &list, struct DataEntry, node) {
        entry->value += i++;
        ListRemove(&entry->node);
    }
    SHOULD(i == 12);
    SHOULD(ListEmpty(&list));
    SHOULD(n[0].value == n[0].key + 0 + 3 + 8 + 11);
    SHOULD(n[1].value == n[1].key + 1 + 4 + 7 + 10);
    SHOULD(n[2].value == n[2].key + 2 + 5 + 6 + 9);
    // No need ListDeinit here.
}

/* Hash */

static bool DataEntryEqual(const struct Node *a, const struct Node *b)
{
    struct DataEntry *d1 = NODE_ENTRY(a, struct DataEntry, node);
    struct DataEntry *d2 = NODE_ENTRY(b, struct DataEntry, node);
    return d1->key == d2->key;
}

static size_t DataEntryKey(const struct Node *node, size_t bktSize)
{
    struct DataEntry *e = NODE_ENTRY(node, struct DataEntry, node);
    return e->key % bktSize;
}

void TEST_HashInit(void)
{
    struct HashTable ht;
    size_t bktSize = 8;
    int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
    SHOULD(ret == 0);
    HashDeinit(&ht, NodeInc);
}

void TEST_HashAdd(void)
{
    struct HashTable ht;
    size_t bktSize = 10;
    size_t nodeCnt = 15;
    int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
    SHOULD(ret == 0);

    struct DataEntry *n = GetEntryArray(nodeCnt);
    size_t i;
    for (i = 0; i < nodeCnt; i++) {
        HashAdd(&ht, &n[i].node);
    }

    struct List *list;
    struct DataEntry *entry;

    /* 检查 HASH 底层 */
    list = &ht.bkts[0];     /* 第 0 个 HASH 桶: 0..10 */
    entry = LIST_HEAD_ENTRY(list, struct DataEntry, node);
    SHOULD(entry->value == 0);
    entry = LIST_TAIL_ENTRY(list, struct DataEntry, node);
    SHOULD(entry->value == 10);

    list = &ht.bkts[6];     /* 第 6 个 HASH 桶: 6 */
    entry = LIST_HEAD_ENTRY(list, struct DataEntry, node);
    SHOULD(entry->value == 6);
    SHOULD(ListIsTail(list, &entry->node)); /* 6 应是唯一节点 */

    HashDeinit(&ht, NodeInc);
}

void TEST_HashFind(void)
{
    struct HashTable ht;
    size_t bktSize = 10;
    size_t nodeCnt = 15;
    int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
    SHOULD(ret == 0);

    struct DataEntry *n = GetEntryArray(nodeCnt);
    size_t i;
    for (i = 0; i < nodeCnt; i++) {
        HashAdd(&ht, &n[i].node);
    }
    
    struct Node *node;
    struct DataEntry *entry;
    struct DataEntry cmpNode;

    /* 查找节点 0 */
    cmpNode.key = 0;
    node = HashFind(&ht, &cmpNode.node);
    SHOULD(node != NULL);
    entry = NODE_ENTRY(node, struct DataEntry, node);
    SHOULD(entry != NULL);
    SHOULD(entry->value == 0);

    /* 查找 16，应找不到 */
    cmpNode.key = 16;
    node = HashFind(&ht, &cmpNode.node);
    SHOULD(node == NULL);

    HashDeinit(&ht, NodeInc);
}

void TEST_HashRemove(void)
{
    struct HashTable ht;
    size_t bktSize = 10;
    size_t nodeCnt = 15;
    int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
    SHOULD(ret == 0);

    struct DataEntry *n = GetEntryArray(nodeCnt);
    size_t i;
    for (i = 0; i < nodeCnt; i++) {
        HashAdd(&ht, &n[i].node);
    }

    struct Node *node;
    struct DataEntry cmpNode;

    cmpNode.key = 0;
    node = HashFind(&ht, &cmpNode.node);
    SHOULD(node != NULL);
    HashRemove(node);       /* 删除 0 */
    HashRemove(&n[1].node); /* 删除 1 */

    /* 删除后 */
    cmpNode.key = 0;
    node = HashFind(&ht, &cmpNode.node);
    SHOULD(node == NULL);
    cmpNode.key = 1;
    node = HashFind(&ht, &cmpNode.node);
    SHOULD(node == NULL);

    HashDeinit(&ht, NodeInc);
}

void TEST_HashIterate(void)
{
    struct HashTable ht;
    size_t bktSize = 10;
    size_t nodeCnt = 15;
    int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
    SHOULD(ret == 0);

    struct DataEntry *n = GetEntryArray(nodeCnt);
    size_t i;
    for (i = 0; i < nodeCnt; i++) {
        HashAdd(&ht, &n[i].node);
    }

    int a = 0;
    HashIterate(&ht, NodeIncX, &a);
    SHOULD(a == (int)nodeCnt);
    SHOULD(n[0].value == 0 + 0);
    SHOULD(n[10].value == 10 + 1);
    SHOULD(n[1].value == 1 + 2);

    HashDeinit(&ht, NodeInc);
}

void TEST_HashReset(void)
{
    struct HashTable ht;
    size_t bktSize = 10;    /* 初始桶大小为 10 */
    size_t nodeCnt = 15;    /* 一共 15 个节点 */
    int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
    SHOULD(ret == 0);

    struct DataEntry *n = GetEntryArray(nodeCnt);
    size_t i;
    for (i = 0; i < nodeCnt; i++) {
        HashAdd(&ht, &n[i].node);
    }

    struct List *list;
    struct DataEntry *entry;

    /* 10 个桶时，节点 6，应该是桶内唯一 */
    list = &ht.bkts[6]; 
    entry = LIST_HEAD_ENTRY(list, struct DataEntry, node);
    SHOULD(entry->value == 6);
    SHOULD(ListIsTail(list, &entry->node));

    /* 桶大小 10 -> 8 */
    bktSize = 8;
    HashReset(&ht, bktSize, NULL, NULL);

    /* 8 个桶时，节点 6, 14 应该共桶 */
    list = &ht.bkts[6]; 
    entry = LIST_HEAD_ENTRY(list, struct DataEntry, node);
    SHOULD(entry->value == 6 || entry->value == 14);
    SHOULDNT(ListIsTail(list, &entry->node));

    HashDeinit(&ht, NodeInc);
}

void TEST_HashDeinit(void)
{
    struct HashTable ht;
    size_t bktSize = 10;
    size_t nodeCnt = 15;
    int ret = HashInit(&ht, bktSize, DataEntryEqual, DataEntryKey);
    SHOULD(ret == 0);

    struct DataEntry *n = GetEntryArray(nodeCnt);
    size_t i;
    for (i = 0; i < nodeCnt; i++) {
        HashAdd(&ht, &n[i].node);
    }

    struct DataEntry *entry;

    /* 删除节点 0 */
    HashRemove(&n[0].node);

    HashDeinit(&ht, NodeInc);

    /* deinit 会将表中节点 value 自增，比 key 大 1 */
    entry = NODE_ENTRY(&n[0].node, struct DataEntry, node);
    SHOULD(entry->value == entry->key);     /* 不在表中，未自增 */
    entry = NODE_ENTRY(&n[1].node, struct DataEntry, node);
    SHOULD(entry->value == entry->key + 1); /* 表中节点，被自增 */
}

#include "lru_cache.c"
/* 原题用例，参考: https://leetcode-cn.com/problems/lru-cache */
void TEST_LruCache(void)
{
    LRUCache *cache = lRUCacheCreate(2);
    SHOULD(cache != NULL);

    lRUCachePut(cache, 1, 1);
    lRUCachePut(cache, 2, 2);
    int ret;
    ret = lRUCacheGet(cache, 1);
    SHOULD(ret == 1);
    lRUCachePut(cache, 3, 3);
    ret = lRUCacheGet(cache, 2);
    SHOULD(ret == -1);
    lRUCachePut(cache, 4, 4);
    ret = lRUCacheGet(cache, 1);
    SHOULD(ret == -1);
    ret = lRUCacheGet(cache, 3);
    SHOULD(ret == 3);
    ret = lRUCacheGet(cache, 4);
    SHOULD(ret == 4);
}

int main(void)
{
    TEST_NodeEntry();

    TEST_ListInit();
    TEST_ListInsert();
    TEST_ListRemove();
    TEST_ListForEach();
    TEST_ListIterate();
    TEST_ListDeinit();
    TEST_ListEntry();

    TEST_HashInit();
    TEST_HashAdd();
    TEST_HashFind();
    TEST_HashRemove();
    TEST_HashIterate();
    TEST_HashReset();
    TEST_HashDeinit();

    TEST_LruCache();

    return 0;
}

