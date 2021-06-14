### 思路参考
链地址法：
设哈希表的大小为 base，则可以设计一个简单的哈希函数 hash(x) = x mod base。

我们开辟一个大小为 base 的数组，数组的每个位置是一个链表。当计算出哈希值之后，就插入到对应位置的链表当中。

由于我们使用整数除法作为哈希函数，为了尽可能避免冲突，应当将 base 取为一个质数,在这里我们取 769。
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
    tmp->next = head->next; // 注意这里是头插法，每次都查到head后面，但是head始终在头部
    head->next = tmp;
}

void ListDelete(struct List* head, int x)
{
    for (struct List* it = head; it->next; it = it->next) {
        if (it->next->val == x) { // 单链表删除操作时，要使用 it->next->val 来遍历，这样才能保留要删除节点的父节点，这样才能删除。
            struct List* tmp = it->next;
            it->next = tmp->next;
            free(tmp);// 注意是否内存，并退出
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
    if (!ListContains(&(obj->data[h]),key)) { // 由于是hash set 只保留不重复的数据。
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
```



## 上面的算法没有实现对hashset的搜索，下面补全。
1. 注意当前的数据分布情况是，hashset是一个结构体，该结构体成员是一个指向链表的指针。
2. 然后分配base个链表头节点，这些链表头节点是内存相邻的。
3. 向hashset中添加元素时，根据key计算出hashcode，就是寻找是要放在那个头结点里面，然后再分配一个链表节点，接到head上。
4. 遍历hashset时，是全遍历，针对base个head。 查看那个head->next不为空，则认为是有值的，拿出该值。
#### 代码
```
struct list {
    int val;
    struct list* next;
};

void listPut(struct list* head, int x)
{
    struct list* tmp = (struct list*)malloc(sizeof(struct list));
    tmp->val = x;
    tmp->next = NULL;
    tmp->next = head->next;
    head->next = tmp;
}

bool listContains(struct list* head, int x)
{
    for (struct list* it = head; it->next; it = it->next) {
        if (it->next->val == x) {
            return true;
        }
    }
    return false;
}

typedef struct {
    struct list* data;
    int size;
} HashSet;

const int base = 769;  // 该值应该还是选择的有问题，对于大量的数据，计算的结果不对

int hashCode(int key)
{
    return key % base >= 0 ? key % base : (key % base) + base;
}

HashSet* createHashSet(void)
{
    HashSet* obj = (HashSet*)malloc(sizeof(HashSet));
    obj->data = (struct list*)malloc(sizeof(struct list) * base);
    obj->size = 0;
    for (int i = 0; i < base; i++) {
        obj->data[i].val = INT_MIN;
        obj->data[i].next = NULL;
    }
    return obj;
}

bool contiansElement(HashSet* obj, int x)
{
    int hash = hashCode(x);
    return listContains(&(obj->data[hash]), x);
}

void addElement(HashSet* obj, int x)
{
    int hash = hashCode(x);
    if (!listContains(&(obj->data[hash]), x)) {
        listPut(&(obj->data[hash]), x);
        obj->size++;
    }
}

int getHashSetSize(HashSet* obj)
{
    return obj->size;
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    *returnSize = 0;
    int length = nums1Size > nums2Size ? nums2Size : nums1Size;
    if (length == 0) {
        return NULL;
    }
    int* res = (int*)malloc(sizeof(int) * length);
    memset(res, 0, sizeof(int) * length);
    HashSet* obj1 = createHashSet();
    for (int i = 0; i < nums1Size; i++) {
        addElement(obj1, nums1[i]);
    }
    int hash1Size = getHashSetSize(obj1);


    HashSet* obj2 = createHashSet();
    for (int i = 0; i < nums2Size; i++) {
        addElement(obj2, nums2[i]);
    }
    int hash2Size = getHashSetSize(obj2);

    if (hash1Size > hash2Size) {
        int count = 0;
        for (int i = 0; i < base; i++) {
            if(obj2->data[i].next) {
                int num = obj2->data[i].next->val;
                if (contiansElement(obj1, num)) {
                    res[*returnSize] = num;
                    (*returnSize)++;
                }
                count++;
                if (count == hash2Size) {
                    break;
                }
            }
        }
    } else {
        int count = 0;
        for (int i = 0; i < base; i++) {
            if (obj1->data[i].next) {
                int num = obj1->data[i].next->val;
                if (contiansElement(obj2, num)) {
                    res[*returnSize] = num;
                    (*returnSize)++;
                }
                count++;
                if (count == hash1Size) {
                    break;;
                }
            }
        }
    }

    return res;
}
```