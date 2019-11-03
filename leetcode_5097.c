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
    tmp->score = 0; //�ɼ�������ĵ�һ��ֵ�ǿ�ֵ��������Ч�Ľڵ�ֵ�ں��档
    tmp->next = NULL; 
    return tmp;
}

/*��Ŀ��ʾ���У���Ҫ����playerID��˳�����*/
void leaderboardAddScore(Leaderboard* obj, int playerId, int score) {
    Leaderboard* tmp = obj;
    while (tmp) {
        if (tmp->playerId == playerId) {
            tmp->score += score;
            return;
        } 
        tmp = tmp->next;
    }

    //���б���û��Ҫ�����ID��������Ҫ��������һ���ڵ㣬���뵽��ȷλ�ã�����ID�Ĵ�С˳�򡣴�С����
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
        //˵���ҵ������β�ˡ�ֱ�Ӱ�������Ľڵ����β������
        p->next = node;
        return;
    }
    //˵���ҵ�һ��ID����Ҫ�����ID����ʱ��Ҫ������Ľڵ���뵽���ǰ��
    node->next = p->next;
    p->next = node;

    return;
}


//����ʹ��qsort���������С�
int cmp(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}

// ��ĿҪ����ǰk������ѡ�ֵ��ܳɼ�����ʾ��˵��k��ֵ��10000.
int leaderboardTop(Leaderboard* obj, int K) {
    int* saveScore = (int*)malloc(sizeof(int) * 10001);
    if (saveScore == NULL) {
        return -1;
    }
    memset(saveScore, 0, sizeof(int) * 10001);
    Leaderboard* tmp = obj->next; //����ĵ�һ���ڵ㲻����Чֵ��
    int counter = 0;
    while (tmp) {
        saveScore[counter++] = tmp->score; //�����ǰ����нڵ��ֵ�����������С�
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
    Leaderboard* tmp = obj; // ����ܹؼ����ڱ��������ҵ�����һ��Ҫɾ��ʱ����ʱ�Ѿ���֪�������ϼ��ڵ���ʲô�ˣ����û���������Ļ���
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
        tmp = obj; //�Ȼ�ȡҪ�ͷŵ�ֵ��
        obj = obj->next; //������һ���ͷŵ�ֵ��
        free(tmp);
    }
}