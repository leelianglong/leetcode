/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: 输入若干单词，统计去重后单词数量（用 hash 实现）
 * Create: 2019-11-11
 * Contact: http://rnd-isource.huawei.com/bugs/hw-cstl
 * Note: 为方便编译，未使用安全函数
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hhash.h"

/* 简单起见，假设单词最长 255 */
#define WORD_BUF_LEN 256

/* 使用 hash 实现快速查找，实现去重 */
typedef struct {
    struct Node node;
    char word[WORD_BUF_LEN];
} WordNode;

static bool WordNodeEqual(const struct Node *a, const struct Node *b)
{
    WordNode *na = NODE_ENTRY(a, WordNode, node);
    WordNode *nb = NODE_ENTRY(b, WordNode, node);
    return strcmp(na->word, nb->word) == 0;
}

static size_t WordNodeKey(const struct Node *node, size_t bktSize)
{
    WordNode *n = NODE_ENTRY(node, WordNode, node);
    size_t k = BkdrHash(n->word);
    return k % bktSize;
}

static void FreeWordNode(struct Node *node)
{
    WordNode *n = NODE_ENTRY(node, WordNode, node);
    free(n);
}

static bool WordExist(struct HashTable *ht, const char *word)
{
    WordNode cmp;
    (void)strcpy(cmp.word, word);
    struct Node *n = HashFind(ht, &cmp.node);
    return n != NULL;
}

static int AddNewWord(struct HashTable *ht, const char *word)
{
    WordNode *n = (WordNode*)malloc(sizeof(WordNode));
    if (n == NULL) {
        return -1;
    }
    (void)strcpy(n->word, word);
    HashAdd(ht, &n->node);
    return 0;
}

int main(void)
{
    // 哈希桶初设 1K，节点增加到4倍量后，自动 double
    int bktSize = 1024;
    int nodePerBkt = 4;
    int wordCnt = 0;

    struct HashTable ht;
    int ret = HashInit(&ht, bktSize, WordNodeEqual, WordNodeKey);
    if (ret != 0) {
        return -1;
    }

    while (true) {
        static char word[WORD_BUF_LEN];
        int ret = scanf("%s", word);
        if (ret != 1) { // 用 Ctrl-Z 可中断输入
            break;
        }

        if (WordExist(&ht, word)) {
            continue;
        }

        (void)AddNewWord(&ht, word); // 忽略内存不够
        wordCnt++;
        if (wordCnt >= bktSize * nodePerBkt) {
            bktSize = 2 * bktSize;
            (void)HashReset(&ht, (size_t)bktSize, NULL, NULL);
        }
    } 

    (void)printf("Total count = %d\n", wordCnt);
    HashDeinit(&ht, FreeWordNode);
    return 0;
}

