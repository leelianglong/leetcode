#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int* buff; //���л���
    int buffSize; //���д�С
    int rear;  // ��β
    int front; // ��ͷ
} MyCircularQueue;

bool myCircularQueueIsEmpty(MyCircularQueue* obj);
bool myCircularQueueIsFull(MyCircularQueue* obj);

MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* queue = NULL;
    queue = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    if (queue == NULL) {
        return queue;
    }
    queue->buffSize = k;
    queue->rear = 0;
    queue->front = 0;
    queue->buff = (int*)malloc(sizeof(int) * (k));
    memset(queue->buff, -1, sizeof(int) * (k));// ��ʼ����ʱ�򣬰��ڴ����ó�-1.���������жϿա�
    return queue;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (obj == NULL) {
        return false;
    }
    if (myCircularQueueIsFull(obj)) {
        return false;
    }
    if (myCircularQueueIsEmpty(obj)) { // �����Ǹ����ɣ�����յ�ʱ�򣬾Ͳ�Ҫrear�����ˡ�
        obj->buff[obj->front] = value; 
        return true;
    }

    obj->rear = (obj->rear + 1) % obj->buffSize;
    if (obj->rear == obj->front) { //˵����û�г��ӣ����Բ��ܲ���
        return false;
    }
    obj->buff[obj->rear] = value;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (obj == NULL) {
        return false;
    }
    if (myCircularQueueIsEmpty(obj)) {
        return false;
    }
    obj->buff[obj->front] = -1; // ���Ѿ����ӵ�Ԫ�����óɷǷ�ֵ��
    if (obj->front != obj->rear) {
        obj->front++;
    }
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (obj == NULL) {
        return -1;
    }
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->buff[obj->front];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (obj == NULL) {
        return -1;
    }
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->buff[obj->rear];  
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return (obj->front == obj->rear && obj->buff[obj->front] == -1);
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return ((obj->front == 0) && (obj->rear == obj->buffSize - 1)) 
        || (obj->front == obj->rear + 1);
}

void myCircularQueueFree(MyCircularQueue* obj) {
    if (obj == NULL) {
        return;
    }    
    if (obj->buff != NULL) {
        free(obj->buff);
        obj->buff = NULL;
    }
    free(obj);
}



int main(void)
{
    int k = 3;
    MyCircularQueue* test =  myCircularQueueCreate(k);
    bool result = myCircularQueueEnQueue(test, 1);
    printf("\r\n insert result=%u\r\n", result);
    result = myCircularQueueEnQueue(test, 2);
    printf("\r\n insert result=%u\r\n", result);
    result = myCircularQueueEnQueue(test, 3);
    printf("\r\n insert result=%u\r\n", result);
    result = myCircularQueueEnQueue(test, 4);
    printf("\r\n insert result=%u\r\n", result);

    int rear = myCircularQueueRear(test);
    printf("\r\n rear=%u\r\n", rear);
    bool isFull = myCircularQueueIsFull(test);
    printf("\r\n isFull=%u\r\n", isFull);   

    result = myCircularQueueDeQueue(test);
    printf("\r\n del result=%u\r\n", result); 
    result = myCircularQueueEnQueue(test, 4);
    printf("\r\n insert result=%u\r\n", result);  
    rear = myCircularQueueRear(test);
    printf("\r\n rear=%u\r\n", rear);    
    system("pause");
}