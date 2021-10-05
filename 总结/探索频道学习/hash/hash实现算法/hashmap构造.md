#### 思路
1. 通过链地址法构造hashmap， hashmap和hashset的区别在于前者需要存储(key,val)对，后者仅仅存储key,如果有重复的则不要放在hashset中。

#### 代码
```
struct list {
    int val;
    int key;
    struct list* next;
};

void listPut(struct list* head, int val, int key)
{
    struct list* tmp = (struct list*)malloc(sizeof(struct list));
    tmp->val = val;
    tmp->key = key;
    tmp->next = head->next;
    head->next = tmp;
}

void listDelete(struct list* head, int key)
{
    for (struct list* it = head; it->next; it = it->next) {
        if (it->next->key == key) {
            struct list* tmp = it->next;
            it->next = tmp->next;
            free(tmp);
            break;
        }
    }
}

struct list* listFind(struct list* head, int key)
{
    for (struct list* it = head; it->next; it = it->next) {
        if (it->next->key == key) {
            return it->next;
        }
    }
    return NULL;
}

bool listContains(struct list* head, int key)
{
    for (struct list* it = head; it->next; it = it->next) {
        if (it->next->key == key) {
            return true;
        }
    }
    return false;
}

void listFree(struct list* head)
{
    while (head->next) {
        struct list* tmp = head->next;
        head->next = tmp->next;
        free(tmp);
    }
}

const int base = 769;

typedef struct {
    struct list* data;
} MyHashMap;

/** Initialize your data structure here. */

int hashCode(int key)
{
    return key % base; // 这个hash函数需要注意，如果key是负数的话，那么返回值也就是负数了，这里是要作为数组下标的，需要处理。
}

MyHashMap* myHashMapCreate() {
    MyHashMap* obj = (MyHashMap*)malloc(sizeof(MyHashMap));
    obj->data = (struct list*)malloc(sizeof(struct list) * base);
    for (int i = 0; i < base; i++) {
        obj->data[i].key = 0;
        obj->data[i].val = 0;
        obj->data[i].next = NULL;
    }
    return obj;
}

/** value will always be non-negative. */
void myHashMapPut(MyHashMap* obj, int key, int value) {
    int hash = hashCode(key);
    struct list* tmp = listFind(&obj->data[hash], key);
    if (tmp == NULL) {
        listPut(&obj->data[hash], value, key);
    } else {
        tmp->val = value;
    }
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int myHashMapGet(MyHashMap* obj, int key) {
    int hash = hashCode(key);
    struct list* tmp = listFind(&(obj->data[hash]), key);
    if (tmp == NULL) {
        return -1;
    }
    return tmp->val;
}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
void myHashMapRemove(MyHashMap* obj, int key) {
    int hash = hashCode(key);
    listDelete(&(obj->data[hash]), key);
}

void myHashMapFree(MyHashMap* obj) {
    for (int i = 0; i < base; i++) {
        listFree(&(obj->data[i]));
    }
    free(obj);
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 
 * int param_2 = myHashMapGet(obj, key);
 
 * myHashMapRemove(obj, key);
 
 * myHashMapFree(obj);
*/
```