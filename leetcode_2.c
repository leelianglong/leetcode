#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

#define  STACK_LENGTH     100
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    int stack1[STACK_LENGTH] = {0};
    int stack2[STACK_LENGTH] = {0};
    int tmp1[STACK_LENGTH] = {0};
    int tmp2[STACK_LENGTH] = {0};
    int sum[STACK_LENGTH + 1] = {0};
    int top1 = -1;
    int top2 = -1;
    int i;
    int j;
    if (l1 == NULL || l2 == NULL) {
        return NULL;
    }

    //�ڵ���ջ
    while(l1) {
        stack1[++top1] = l1->val;
        l1 = l1->next;
    }
    while(l2) {
        stack2[++top2] = l2->val;
        l2 = l2->next;
    }

    //���洦��2��ջ��һ����Ļ�����ô������һ��ʹ��0���롣
    int top = top1 > top2 ? top1 : top2;
    if (top1 != top) {
        while (top1 < top) {
            stack1[++top1] = 0;
        }
    }
    if (top2 != top) {
        while (top2 < top) {
            stack2[++top2] = 0;
        }
    }

    // ��ջ��ȡ�����ݣ�ʵ������
    int counter1 = 0;
    while(top1 >= 0) {
        tmp1[counter1++] = stack1[top1--];
    }
    int counter2 = 0;
    while (top2 >= 0) {
        tmp2[counter2++] = stack2[top2--];
    }

    int maxCounter = counter1 >= counter2 ? counter1 : counter2; // 2������ӣ������λ�������нϴ�ġ�
    int bit = 0;
    for (i = maxCounter - 1; i >= 0; i--) {
        sum[bit] += tmp1[i] + tmp2[i]; // ע�������+=��
        sum[bit + 1] += sum[bit] / 10; //�ǵý�λҪ�ۼӡ�
        sum[bit] %= 10;
        bit++;
    }
    
    //�Ӹ�λ��ʼ��������������һ��λ�á�
    for(i = STACK_LENGTH; i >= 0; i--) {
        if (sum[i] != 0) {
            break;
        }
    }

    // ���潫�� sum�е����ַŵ������У�ע��ŵ�˳��
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    memset(head, 0, sizeof(struct ListNode));
    struct ListNode* resLink = head;
    struct ListNode* p = head;
    head->val = sum[0];
    head->next = NULL;
    for (j = 1; j <= i; j++) {
        struct ListNode* tmpList = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmpList->val = sum[j];
        tmpList->next = NULL;
        resLink->next = tmpList;
        resLink = tmpList;
    }
    return head;
}

//�����Ǵ�������
struct ListNode* CreateLink(int* data, int counter)
{
    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    head->val = data[0];
    head->next = NULL;

    struct ListNode* p = NULL;
    p = head;
    int i;
    for (i = 1; i < counter; i++) {
        struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = data[i];
        tmp->next = NULL;
        p->next = tmp;
        p = tmp;
    }
    return head;
}

void VistLinkNode(struct ListNode* node)
{
    while (node != NULL) {
        printf("%4d", node->val);
        node = node->next;
    }
}

int main(void)
{
    int data1[] = {9, 8};
    int counter1 = sizeof(data1) / sizeof(data1[0]);
    struct ListNode* num1 = CreateLink(data1, counter1);
    VistLinkNode(num1);
    printf("\n");

    int data2[] = {1};
    int counter2 = sizeof(data2) / sizeof(data2[0]);
    struct ListNode* num2 = CreateLink(data2, counter2);
    VistLinkNode(num2);
    printf("\n");

    struct ListNode* result = addTwoNumbers(num1, num2);
    VistLinkNode(result);
    system("pause");
}