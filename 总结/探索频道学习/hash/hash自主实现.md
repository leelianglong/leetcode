### 思路参考
链地址法：
设哈希表的大小为 base，则可以设计一个简单的哈希函数 hash(x)=x mod base。

我们开辟一个大小为 base 的数组，数组的每个位置是一个链表。当计算出哈希值之后，就插入到对应位置的链表当中。

由于我们使用整数除法作为哈希函数，为了尽可能避免冲突，应当将 base 取为一个质数。在这里，我们取 769
### 代码
```
struct List {
    int val;
    struct List* next;
};

void ListPut(struct List* head, int x)
{
    struct List* tmp = (struct List*)malloc(sizeof(struct List));
    tmp->val = x;
    tmp->next = head->next;
    head->next = tmp;
}

void ListDelete(struct List* head, int x)
{
    for (struct List* it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            struct List* tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
    }
}

bool ListContains(struct List* head, int x)
{
    for (struct List* it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            return true;
        }
    }
    return false;
}


void ListFree(struct List* head)
{
    while (head->next) {
        struct List* tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

const int base = 769;
int hashCode(int key)
{
    return key % base;
}

typedef struct {
    struct List* data;
} MyHashSet;

/** Initialize your data structure here. */

MyHashSet* myHashSetCreate() {
    MyHashSet* obj = (MyHashSet*)malloc(sizeof(MyHashSet));
    obj->data = (struct List*)malloc(sizeof(struct List) * base);
    for (int i = 0; i < base; i++) {
        obj->data[i].val = 0;
        obj->data[i].next = NULL;
    }
    return obj;
}

void myHashSetAdd(MyHashSet* obj, int key) {
    int h = hashCode(key);
    if (!ListContains(&(obj->data[h]),key)) {
        ListPut(&(obj->data[h]), key);
    }
}

void myHashSetRemove(MyHashSet* obj, int key) {
    int h = hashCode(key);
    ListDelete(&(obj->data[h]), key);
}

/** Returns true if this set contains the specified element */
bool myHashSetContains(MyHashSet* obj, int key) {
    int h = hashCode(key);
    return ListContains(&(obj->data[h]), key);
}

void myHashSetFree(MyHashSet* obj) {
    for (int i = 0; i < base; i++) {
        ListFree(&(obj->data[i]));
    }
    free(obj->data);
}

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 
 * myHashSetRemove(obj, key);
 
 * bool param_3 = myHashSetContains(obj, key);
 
 * myHashSetFree(obj);
*/
```