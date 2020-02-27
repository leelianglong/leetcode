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
    struct QNode* next;// 这个是解决队列的链式存储
} QueueNode, *Queue;

typedef struct {
    Queue front;
    Queue rear;
} QueueLink;

// 队列初始化仅仅创建一个头节点
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
    Queue tmpfront = ql->front->next; // 注意队列在初始化时，设置了空头节点，这里绕过
    tmp = tmpfront->data;
    ql->front->next = tmpfront->next; // 删除头节点。
    if (ql->rear == tmpfront) { // 说明tmpfont已经是尾节点。
        ql->rear = ql->front;
    }
    free(tmpfront); // 把真正的队列头删除。
    return tmp;
}

Location AccessFrontElement(QueueLink ql)
{
    return ql.front->next->data; // 注意有空的头节点
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
            if (grid[i][j] == 1) { // 将陆地全部入队
                tmp.x = i;
                tmp.y = j;
                PushQueue(&ql, tmp);
            }
        }
    }
    if (GetQueueLength(ql) == 0 || GetQueueLength(ql) == row * column) {
        return -1; // 全是陆地或者是海洋，直接退出
    }

    while (!CheckQueueIsEmpty(ql)) {
        int s = GetQueueLength(ql);
        int r = 0;
        while (s != 0) {
            Location front = AccessFrontElement(ql); // 先获取队头元素。
            PopQueue(&ql);
            int direction[4][2] = {
                {1,0},{-1,0},{0,-1},{0,1}
            };
            for (i = 0; i < 4; i++) { // 进行4个方向搜索
                int nx = front.x + direction[i][0];
                int ny = front.y + direction[i][1];
                if (nx >= row || ny >= column || nx < 0 || ny < 0 
                    || grid[nx][ny] == 1) { // 如果还是陆地则继续找
                        continue;
                    }
                
                r++;
                grid[nx][ny] = 1; // 找到一个海洋，填海造陆。
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