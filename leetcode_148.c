#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// �ϲ�����ʱֻ�ı�ָ��ָ�򣬲��ı�ڵ����ݣ��ؼ����Ǵ���һ���ǽڵ㣬���������á����2������
// �е�����£����бȽ��������һ������û�нڵ�󣬾Ͱ�ʣ�������ӵ��ϳɺ�������ϡ�
struct ListNode* MergeList(struct ListNode* left, struct ListNode* right)
{
    if (left == NULL || right == NULL) {
        return NULL;
    }
    struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
    memset(tmp, 0, sizeof(struct ListNode));
    struct ListNode* res = tmp; // ����һ������ڵ㡣
    while (left != NULL && right != NULL) {
        if (left->val > right->val) {
            tmp->next = right;
            right = right->next;
        } else {
            tmp->next = left;
            left = left->next;
        } // ������жϣ����ǽڵ�ӵ������� ���� �������ϡ������ǰ������������еġ�
        tmp = tmp->next;  // �����ǰ��ǽڵ���ǰ�ƶ�һ���ڵ㡣
    }
    // ��ʣ�µ����нӵ��ǽڵ��ϡ�
    if (left != NULL) {
        tmp->next = left;
    } 
    if (right != NULL) {
        tmp->next = right;
    }
    return res->next;
}

struct ListNode* sortList(struct ListNode* head){
    if (head == NULL || head->next == NULL) {
        return head;
    }
    // ����ָ�����ʼ�ڵ����һ�����ڱ����Ĺ����У���ָ�������������ָ����Ծ2����
    struct ListNode* fast = head->next;
    struct ListNode* slow = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    } // ��ѭ���˳���slow�Ѿ�ָ���м�ڵ�
    struct ListNode* left = sortList(slow->next);
    slow->next = NULL; //���м�ڵ����һ���ڵ�����Ϊ��
    struct ListNode* right = sortList(head); // ����ִ��2��sortListʵ���Ͼ����ڶ��ַ����ҵ����ջ�ʣ�����Ԫ��ʱ���ͺϲ�����
    return MergeList(left, right); 
}


// ��ǰ��������ͷ�ڵ㡣
struct ListNode* CreateList(int* data, int dataLength, int* counter)
{
    if (data == NULL) {
        return NULL;
    }

    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (head == NULL) {
        return NULL;
    }
    head->val = data[(*counter)++];
    head->next = NULL;
    struct ListNode* p = head;
    int i;
    for (i = 1; i < dataLength; i++) {
        struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = data[(*counter)++];
        tmp->next = NULL;
        p->next = tmp;
        p = tmp;
    }
    return head;
}

void VistList(struct ListNode* node)
{
    while(node) {
        printf("%4d", node->val);
        node = node->next;
    }
}

int main(void)
{
    int test[] = {1,2,3,4,5,6,7,8,9,10};
    int returnCounter = 0;
    struct ListNode* result = CreateList(test, sizeof(test) / sizeof(test[0]), 
        &returnCounter);
    VistList(result);
    sortList(result);
    system("pause");
}