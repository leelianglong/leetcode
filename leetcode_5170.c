#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Ŀǰ�㷨��ʱ�ˡ�
typedef struct QNode {
    int data;
    struct QNode* next;
} Queue, *QueueNodeList;

typedef struct {
    QueueNodeList front;
    QueueNodeList rear;
} QueueLink;

bool InitQueue(QueueLink* ql)
{
    // ���иտ�ʼʱ����ͷ�Ͷ�β��ָ��ͬһ����ַ
    ql->front = ql->rear = (QueueNodeList)malloc(sizeof(Queue));
    if (ql->front == NULL) {
        return false;
    }
    ql->front->data = -1; //ʵ���������ʼ��һ���ǽڵ㡣��һ���ڵ㲢û�д�ֵ
    ql->front->next = NULL; // ��ʼ��ʱ���Ѷ�ͷ����һ���ڵ�ָ��NULL�������쳣���Ӳ���
    return true;
}

void DestroyQueue(QueueLink* ql)
{
    while (ql->front) {
        ql->rear = ql->front->next;
        free(ql->front);
        ql->front = ql->rear;
    }
}

bool CheckQueueIsEmpty(QueueLink ql)
{
    return ql.front == ql.rear ? true : false;
}

int GetQueueLength(QueueLink ql)
{
    QueueNodeList tmp = ql.front;
    int size = 0;
    while (tmp != ql.rear) {
        tmp = tmp->next;
        size++;
    }
    return size;
}

void PushQueue(QueueLink* ql, int data) 
{
    QueueNodeList tmp = (QueueNodeList)malloc(sizeof(Queue));
    memset(tmp, 0, sizeof(Queue));
    tmp->next = NULL; // ��������Ϊ����βָ�룬Ҫȷ����ָ����ȷ�ĵط�
    tmp->data = data;
    ql->rear->next = tmp;
    ql->rear = tmp;
    return;
}

int PopQueue(QueueLink* ql)
{
    if (ql->front == ql->rear) {
        return -1;
    }
    QueueNodeList tmpQNode = ql->front->next; // �ڳ�ʼ������ʱ��ͷ�ڵ�ʱ�ǽڵ㣬������Ч�������Ǵ�����һ����ʼ�ġ�
    int tmpData = tmpQNode->data;
    ql->front->next = tmpQNode->next;
    if (ql->rear == tmpQNode) {
        ql->rear = ql->front; // ˵��Ҫɾ���Ľڵ��Ѿ�������ˣ��Ͱ�β�ڵ�ָ��front��
    }
    free(tmpQNode);// ��ͷ�ڵ��ͷš�
    return tmpData;
}

// ֻ�Ƿ��ʲ�Ҫ�ƶ�ͷָ�롣
int AccessFrontData(QueueLink ql)
{
    return ql.front->next->data;
}

bool JudgeRepeatElement(QueueLink ql, int data)
{
    QueueNodeList tmp = ql.front->next;
    while (tmp != ql.rear) {
        if (data == tmp->data) {
            return true;
        }
    }
    if (data == ql.rear->data) {
        return true;
    }
    return false;
}

void VisitQueue(QueueLink ql)
{
    QueueNodeList tmp = ql.front->next; 
    while (tmp != ql.rear) {
        printf("%2d", tmp->data);
        tmp = tmp->next;
    }
    printf("%2d", ql.rear->data); // ���β�ڵ�Ҳ������ֵ
}

bool validateBinaryTreeNodes(int n, int* leftChild, int leftChildSize, int* rightChild, int rightChildSize){
    if (n <= 0 || leftChild == NULL || rightChild == NULL || leftChildSize < 0 || rightChildSize < 0) {
        return false;
    }
    QueueLink ql;
    InitQueue(&ql);
    PushQueue(&ql, 0);
    int* visited = (int*)malloc(sizeof(int) * n);
    memset(visited, false, sizeof(int) * n);
    int i;
    while(!CheckQueueIsEmpty(ql)) {
        int length = GetQueueLength(ql);
        for (i = 0; i < length; i++) {
            int node = AccessFrontData(ql);
            PopQueue(&ql);
            visited[node] = true;
            if (leftChild[node] != -1) {
                if (!visited[leftChild[node]]) {
                    if (!JudgeRepeatElement(ql,leftChild[node])) {
                        PushQueue(&ql, leftChild[node]); // ���ܽ���ͬ�Ľڵ���ӣ��������γɻ�
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }

            if (rightChild[node] != -1) {
                if (!visited[rightChild[node]]) {
                    if (!JudgeRepeatElement(ql,rightChild[node])) {
                        PushQueue(&ql, rightChild[node]);
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
    }
    for (i = 0; i < n; i++) {
        if (visited[i] == false) {
            return false;
        }
    }
    return true;
}

int main(void)
{
    QueueLink ql;
    InitQueue(&ql);
    int i;
    for (i = 0; i < 10; i++) {
        PushQueue(&ql, i);
    }
    VisitQueue(ql);
    printf("\r\nprint del queue\r\n");
    for (i = 0; i < 5; i++) {
        int tmp = PopQueue(&ql);
        printf("%2d\r\n", tmp);
    }
    system("pause");
}
