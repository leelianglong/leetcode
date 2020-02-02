#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// 合并链表时只改变指针指向，不改变节点内容，关键点是创建一个亚节点，用来遍历用。如果2个链表都
// 有的情况下，进行比较排序，如果一个链表没有节点后，就把剩余的链表接到合成后的链表上。
struct ListNode* MergeList(struct ListNode* left, struct ListNode* right)
{
    if (left == NULL || right == NULL) {
        return NULL;
    }
    struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
    memset(tmp, 0, sizeof(struct ListNode));
    struct ListNode* res = tmp; // 创建一个多余节点。
    while (left != NULL && right != NULL) {
        if (left->val > right->val) {
            tmp->next = right;
            right = right->next;
        } else {
            tmp->next = left;
            left = left->next;
        } // 上面的判断，把亚节点接到左序列 或者 右序列上。这里是按照升序来排列的。
        tmp = tmp->next;  // 这里是把亚节点向前移动一个节点。
    }
    // 把剩下的序列接到亚节点上。
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
    // 快慢指针的起始节点相差一个，在遍历的过程中，慢指针逐个遍历，快指针跳跃2个。
    struct ListNode* fast = head->next;
    struct ListNode* slow = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    } // 该循环退出后，slow已经指向中间节点
    struct ListNode* left = sortList(slow->next);
    slow->next = NULL; //将中间节点的下一个节点设置为空
    struct ListNode* right = sortList(head); // 这里执行2次sortList实际上就是在二分法，找到最终还剩余二个元素时，就合并排序。
    return MergeList(left, right); 
}


// 当前链表不包含头节点。
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