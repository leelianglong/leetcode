#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int playerId;
    int score;
    struct Leaderboard* next;
} Leaderboard;

Leaderboard* leaderboardCreate(void) {
    Leaderboard* tmp = (Leaderboard*)malloc(sizeof(Leaderboard));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->playerId = 0;
    tmp->score = 0; //可见该链表的第一个值是空值，真正有效的节点值在后面。
    tmp->next = NULL; 
    return tmp;
}

/*题目的示例中，需要按照playerID的顺序插入*/
void leaderboardAddScore(Leaderboard* obj, int playerId, int score) {
    Leaderboard* tmp = obj;
    while (tmp) {
        if (tmp->playerId == playerId) {
            tmp->score += score;
            return;
        } 
        tmp = tmp->next;
    }

    //当列表中没有要插入的ID。下面需要重新申请一个节点，插入到正确位置，按照ID的大小顺序。从小到大。
    Leaderboard* node = (Leaderboard*)malloc(sizeof(Leaderboard));
    if (node == NULL) {
        return;
    }
    node->score = score;
    node->playerId = playerId;
    node->next = NULL;

    Leaderboard* p = obj;
    Leaderboard* q = obj->next;
    while (q && q->playerId < playerId) {
        p = p->next;
        q = q->next;
    }
    if (!q) {
        //说明找到链表结尾了。直接把新申请的节点放在尾部即可
        p->next = node;
        return;
    }
    //说明找到一个ID大于要插入的ID，此时需要把申请的节点插入到这个前面
    node->next = p->next;
    p->next = node;

    return;
}


//打算使用qsort降序来排列。
int cmp(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}

// 题目要求是前k名参赛选手的总成绩。提示中说明k的值是10000.
int leaderboardTop(Leaderboard* obj, int K) {
    int* saveScore = (int*)malloc(sizeof(int) * 10001);
    if (saveScore == NULL) {
        return -1;
    }
    memset(saveScore, 0, sizeof(int) * 10001);
    Leaderboard* tmp = obj->next; //链表的第一个节点不是有效值。
    int counter = 0;
    while (tmp) {
        saveScore[counter++] = tmp->score; //这里是把所有节点的值都放在数组中。
        tmp = tmp->next; 
    }

    qsort(saveScore, 10001, sizeof(int), cmp);

    int sum = 0;
    for (counter = 0; counter < K; counter++) {
        sum += saveScore[counter];
    }
    return sum;
}

void leaderboardReset(Leaderboard* obj, int playerId) {
    Leaderboard* p = obj->next;
    Leaderboard* tmp = obj; // 这个很关键，在遍历链表找到其中一个要删除时，此时已经不知道它的上级节点是什么了，如果没有这个定义的话。
    while (p) {
        if (p->playerId == playerId) {
            tmp->next = p->next;
            return;
        }
        tmp = tmp->next;
        p = p->next;
    }
}

void leaderboardFree(Leaderboard* obj) {
    Leaderboard* tmp;
    while (obj) {
        tmp = obj; //先获取要释放的值。
        obj = obj->next; //更新下一次释放的值。
        free(tmp);
    }
}