### 题目 删除链表倒数第K个节点，并返回头结点。

思路：
1、使用快慢双指针，快指针先前行n个节点，然后满指针和快指针一起走，当快指针到底结尾时，就停下来。此时慢指针刚好指向要删除的节点的前一个节点。把它后面

的节点删除即可

2、这里需要注意的是，结束判定的条件是 fast->next != NULL,  不要使用 fast ！= NULL， 使用后者的话，slow就指向要删除的节点了，就不号删除了。

另外还有一个特殊点就是，删除倒数的节点等于链表长度或者大于时，要把原来的head删除返回。


### 代码
```
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    if (head == NULL) {
        return NULL;
    }
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    int i = 0;
    while (fast != NULL && i < n) {
        fast = fast->next;
        i++;
    }
    if (fast == NULL) {
        head = head->next;
        return head;
    }
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    slow->next = slow->next->next;
    return head;
}
```
