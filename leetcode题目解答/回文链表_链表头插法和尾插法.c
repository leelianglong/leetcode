/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
*/

#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode* next;  
};

#define MAX_LENGTH  1024

typedef struct ListNode Node, *LinkNode;

typedef struct _STACK {
    int top;
    int data[MAX_LENGTH];
} STACK,*LINK_STACK;

int InitStack(LINK_STACK* ls)
{
    if (ls == NULL) {
        return 0;
    }
    (*ls) = (LINK_STACK)malloc(sizeof(STACK));
    (*ls)->top = -1;
    return 1;
}

int PushStack(LINK_STACK* ls, int data)
{
    int deepth = (*ls)->top;
    if (ls == NULL || deepth >= MAX_LENGTH - 1) {
        return 0;
    }
    (*ls)->top++;
    (*ls)->data[(*ls)->top] = data;
    return 1;
}

int PopStack(LINK_STACK* ls, int *data)
{
    int deepth = (*ls)->top;
    if (ls == NULL || deepth < 0) {
        return 0;
    }
    *data = (*ls)->data[(*ls)->top];
    (*ls)->top--;
    return 1;
}


int isPalindrome(struct ListNode* head){
	int i;
    int counter = 0;
    LinkNode tmp = head;
	LinkNode move = head;
    LINK_STACK ls = {0};
	int data = 0;

    if (tmp == NULL) {
        return 0;
    }
    while (tmp != NULL) {
        counter++;
        tmp = tmp->next;
    }

    InitStack(&ls);
    for (i = 0; i < counter/2;i++){
		PushStack(&ls, (*move).val);
        move = move->next;
    }
	if (counter % 2 == 1) {
		move = move->next;
	}
    for (i = 0; i < counter/2; i++) {
        PopStack(&ls, &data);
        if (data != move->val) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    LinkNode head = NULL;
    LinkNode tmp = NULL;
	LinkNode p = NULL;
	LinkNode q = NULL;
    int i;
#if 0
	// ͷ�巨
    for (i = 0; i < 10 ; i++) {
        tmp = (LinkNode)malloc(sizeof(Node));
        tmp->val = i;
        tmp->next = head;
        head = tmp;
    }

	for (i = 0; i < 10; i++) {
		printf("%4d",head->val);
		head = head->next;
	}
#endif
    //β�巨
	head = (LinkNode)malloc(sizeof(Node));
	head->val = 1;
	head->next = NULL;
	p = head;
	for (i = 1; i < 2 ; i++) {
        tmp = (LinkNode)malloc(sizeof(Node));
        tmp->val = 2;
        tmp->next = NULL;
		p->next = tmp;
		p = tmp;
    }

	isPalindrome(head);
}

