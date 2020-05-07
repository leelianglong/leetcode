/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2019-2020. All rights reserved.
 * Description: 输入若干正整数，反序打印出来（用 list 实现）
 * Create: 2019-11-11
 * Contact: http://rnd-isource.huawei.com/bugs/hw-cstl
 * Note: 为方便编译，未使用安全函数
 */

#include <stdio.h>
#include <stdlib.h>
#include "hlist.h"

/* 使用 list 实现先进后出栈结构 */
typedef struct {
    struct Node node;
    int data;
} IntNode;

static int PushInt(struct List *list, int data)
{
    IntNode *n = (IntNode*)malloc(sizeof(IntNode));
    if (n == NULL) {
        return -1; 
    }
    n->data = data;
    ListAddTail(list, &n->node); // 添加到 tail 处
    return 0;
}

/* 返回 -1 表示已空 */
static int PopInt(struct List *list)
{
    IntNode *n = LIST_TAIL_ENTRY(list, IntNode, node); // 从 tail 处取
    if (n == NULL) {
        return -1;
    }
    int ret = n->data;
    ListRemoveTail(list);
    free(n);
    return ret;
}

int main(void)
{
    struct List list;
    ListInit(&list);

    int data;
    while (true) {
        int ret = scanf("%d", &data);
        if (ret != 1) { // 任意非数字输入可中断
            break;
        }
        (void)PushInt(&list, data); // 忽略内存不够
    } 

    while (true) {
        data = PopInt(&list);
        if (data < 0) {
            break;
        } 
        printf("%d ", data);
    }

    return 0;
}

