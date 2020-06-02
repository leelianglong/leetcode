#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Location;

typedef struct QNode {
    Location data;
    struct QNode* next;// ����ǽ�����е���ʽ�洢
} QueueNode, *Queue;

typedef struct {
    Queue front;
    Queue rear;
} QueueLink;

// ���г�ʼ����������һ��ͷ�ڵ�
bool InitQueue(QueueLink* ql)
{
    if (ql == NULL) {
        return false;
    }
    ql->front = (Queue)malloc(sizeof(QueueNode));
    ql->rear = ql->front;
    ql->front->next = NULL;
    return true;
}

bool PushQueue(QueueLink* ql, Location data)
{
    Queue tmp = (Queue)malloc(sizeof(QueueNode));
    tmp->next = NULL;
    tmp->data = data;

    ql->rear->next = tmp;
    ql->rear = tmp;
    return true;
}

Location PopQueue(QueueLink* ql)
{
    Location tmp = {0};
    if (ql->front == ql->rear) {
        return tmp;
    }
    Queue tmpfront = ql->front->next; // ע������ڳ�ʼ��ʱ�������˿�ͷ�ڵ㣬�����ƹ�
    tmp = tmpfront->data;
    ql->front->next = tmpfront->next; // ɾ��ͷ�ڵ㡣
    if (ql->rear == tmpfront) { // ˵��tmpfont�Ѿ���β�ڵ㡣
        ql->rear = ql->front;
    }
    free(tmpfront); // �������Ķ���ͷɾ����
    return tmp;
}

Location AccessFrontElement(QueueLink ql)
{
    return ql.front->next->data; // ע���пյ�ͷ�ڵ�
}

Location AccessRearElement(QueueLink ql)
{
    return ql.rear->data;
}

int GetQueueLength(QueueLink ql)
{
    int counter = 0;
    Queue tmp = ql.front;
    while (ql.rear != tmp) {
        counter++;
        tmp = tmp->next;
    }
    return counter;
}

bool CheckQueueIsEmpty(QueueLink ql)
{
    return ql.front == ql.rear ? true : false;
}

void VisitQueue(QueueLink ql)
{
    Queue tmp = ql.front->next;
    while (tmp) {
        printf("(%2d%2d)", tmp->data.x, tmp->data.y);
        tmp = tmp->next;
        printf("\n");
    }
}

int maxDistance(int** grid, int gridSize, int* gridColSize){
    int res = 0;
    int row = gridSize;
    int column = *gridColSize;
    QueueLink ql;
    InitQueue(&ql);
    int i;
    int j;
    Location tmp = {0};
    for (i = 0; i < row;i++) {
        for (j = 0; j < column; j++) {
            if (grid[i][j] == 1) { // ��½��ȫ�����
                tmp.x = i;
                tmp.y = j;
                PushQueue(&ql, tmp);
            }
        }
    }
    if (GetQueueLength(ql) == 0 || GetQueueLength(ql) == row * column) {
        return -1; // ȫ��½�ػ����Ǻ���ֱ���˳�
    }

    while (!CheckQueueIsEmpty(ql)) {
        int s = GetQueueLength(ql);
        int r = 0;
        while (s != 0) {
            Location front = AccessFrontElement(ql); // �Ȼ�ȡ��ͷԪ�ء�
            PopQueue(&ql);
            int direction[4][2] = {
                {1,0},{-1,0},{0,-1},{0,1}
            };
            for (i = 0; i < 4; i++) { // ����4����������
                int nx = front.x + direction[i][0];
                int ny = front.y + direction[i][1];
                if (nx >= row || ny >= column || nx < 0 || ny < 0 
                    || grid[nx][ny] == 1) { // �������½���������
                        continue;
                    }
                
                r++;
                grid[nx][ny] = 1; // �ҵ�һ���������½��
                tmp.x = nx;
                tmp.y = ny;
                PushQueue(&ql, tmp);
            }
            s--;
        }
        if (r > 0) {
            res++;
        }
    }
    return res;
}

int main(void)
{
    QueueLink ql;
    InitQueue(&ql);
    int i;
    Location pair[10] = {
        {1,1},{1,2},{1,3},{1,4},
        {2,1},{2,2},{2,3},{2,4}, 
        {2,5},{2,6}};
    for (i = 0; i < 10; i++) {
        PushQueue(&ql, pair[i]);
    }
    VisitQueue(ql);
    printf("\r\nget length=%d\r\n", GetQueueLength(ql));
    Location data = AccessFrontElement(ql);
    printf("first data(%2d%2d)\r\n", data.x, data.y);
    data = AccessRearElement(ql);
    printf("last data(%2d%2d)\r\n", data.x, data.y);
    PopQueue(&ql);
    PopQueue(&ql);
    PopQueue(&ql);
    PopQueue(&ql);
    data = AccessFrontElement(ql);
    printf("first data(%2d%2d)\r\n", data.x, data.y);
    system("pause");
}