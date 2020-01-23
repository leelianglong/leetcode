/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

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
    while(l1) {
        stack1[++top1] = l1->val;
        l1 = l1->next;
    }
    while(l2) {
        stack2[++top2] = l2->val;
        l2 = l2->next;
    }

    int counter1 = 0;
    while(top1 >= 0) {
        tmp1[counter1++] = stack1[top1--];
    }
    int counter2 = 0;
    while (top2 >= 0) {
        tmp2[counter2++] = stack2[top2--];
    }
    int maxCounter = counter1 >= counter2 ? counter1 : counter2;
    int bit = 0;
    for (i = maxCounter - 1; i >= 0; i--) {
        sum[bit] = tmp1[i] + tmp2[i];
        sum[bit + 1] = sum[bit] / 10;
        sum[bit] %= 10;
        bit++;
    }

    for(i = STACK_LENGTH; i >= 0; i--) {
        if (sum[i] != 0) {
            break;
        }
    }

    struct ListNode* head = (struct ListNode*)malloc(sizeof(struct ListNode));
    memset(head, 0, sizeof(struct ListNode));
    struct ListNode* resLink = head;
    struct ListNode* p = head;
    head->val = sum[i];
    head->next = NULL;
    for (j = 0; j < i; j++) {
        struct ListNode* tmpList = (struct ListNode*)malloc(sizeof(struct ListNode));
        resLink->next = tmpList;
        resLink = tmpList;
    }

    for (j = i; j >= 0; j--) {
        p->val = sum[j];
        p = p->next;
    }
    return head;
}
