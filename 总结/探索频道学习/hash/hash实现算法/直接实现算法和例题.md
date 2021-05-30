### 手动实现hash的算法
#### 代码
1. 当前代码来自于leetcode_146
```
struct LinkListNode {
    int key;
    int val;
    struct LinkListNode* pre;
    struct LinkListNode* next;
};

#define HASH_SIZE 2048
#define HASH_EMPTY -1
#define HASH_KEY int
#define HASH_VAL struct LinkListNode* // val的类型，双链表节点

struct HashNode {
    HASH_KEY key;
    HASH_VAL val;
    struct HashNode* next; // hash冲突解决
};

struct HashNode* Hash_CreateNode(HASH_KEY key, HASH_VAL val, struct HashNode* next)
{
    struct HashNode* obj = (struct HashNode*)malloc(sizeof(struct HashNode));
    obj->key = key;
    obj->val = val;
    obj->next = next; // 头插法
    return obj;
}

struct HashNode** Hash_InitObj(void)
{
    struct HashNode** obj = (struct HashNode**)malloc(sizeof(struct HashNode*) * HASH_SIZE);
    for (int i = 0; i < HASH_SIZE; i++) {
        obj[i] = Hash_CreateNode(HASH_EMPTY, 0, NULL);
    }
    return obj;
}

int Hash_CalcuSeed(HASH_KEY key)
{
    if (key == INT_MIN) {
        key = INT_MAX;
    } else if (key < 0 ) {
        key = -key;
    }
    return key % HASH_SIZE;
}

bool Hash_PutNode(struct HashNode** obj, HASH_KEY key, HASH_VAL val)
{
    int hash = Hash_CalcuSeed(key);
    struct HashNode* curNode = obj[hash];
    if (curNode->key == HASH_EMPTY) { // 当前key在hash表中不存在，则直接添加。
        curNode->key = key;
        curNode->val = val;
        return true;
    }

    while (true) {
        if(curNode->key == key) { // 当前的key已经存在，则覆盖原有的数据， 返回false。
            curNode->val = val;
            return false;
        }
        if(curNode->next == NULL) {
            break;
        }
        curNode = curNode->next;
    }
    curNode->next = Hash_CreateNode(key, val, NULL); // 找到结束的位置，然后把这个key添加进来。
    return true;
}

bool Hash_GetNode(struct HashNode** obj, HASH_KEY key, HASH_VAL* result)
{
    int hash = Hash_CalcuSeed(key);
    struct HashNode* curNode = obj[hash];
    while (curNode != NULL && curNode->key != HASH_EMPTY) {
        if (curNode->key == key) {
            *result = curNode->val;
            return true;
        }
        curNode = curNode->next;
    }
    result = NULL;
    return false;
}

bool Hash_RemoveNode(struct HashNode** obj, HASH_KEY key)
{
    int hash = Hash_CalcuSeed(key);
    struct HashNode* curNode = obj[hash];
    if (curNode->key == key) {
        if (curNode->next == NULL) { // 要删除下一个节点，当前节点的下一个节点不存在了，可以直接把当前节点的key设置成空
            curNode->key = HASH_EMPTY;
            curNode->val = 0;
            return true;
        } else {
            struct HashNode* delNode = curNode->next; // 要删除的是当前节点的下一个。
            curNode->val = curNode->next->val;
            curNode->key = curNode->next->key;
            curNode->next = curNode->next->next; // 这样就把delNode删除了
            free(delNode);
            return true;
        }
    }
    // 当前key节点对应的hash值对应的节点中的key和这个参数key不一样，说明有冲突了，需要继续找。
    while (curNode->next != NULL) {
        struct HashNode* next = curNode->next;
        if (next->key == key) {
            curNode->next = next->next;
            free(next);
            return true;
        }
        curNode = curNode->next;
    }
    return false;
}
```


### 题目，leetcode 187

题目要求重复的字符串。这个字符串的长度是10，在给定的字符串中有重复出现的。

学习：下面的的手动实现hash的算法。

### 代码
```
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
size_t get_hash(char *str)
{//ensure strlen(str)>=10
    register size_t hash=0;
    for(int i=0;i<10;i++)
    {
        hash=hash*131+str[i];
    }
    return hash;
}
struct Hash{
    size_t val;//保存hash,相同的hash视为同一字符串
    bool save;//是否已经保存，用于去重
    struct Hash *next_hash;//链表处理hash冲突
};

char ** findRepeatedDnaSequences(char * s, int* returnSize){
    int hash_size=strlen(s)-9;
    char **ret=NULL;
    *returnSize=0;
    if(hash_size<2)return ret;
    struct Hash **hash_map=calloc(hash_size,sizeof(struct Hash *));
    for(int i=0;i<hash_size;i++)
    {
        size_t hash_key=get_hash(s+i);
        struct Hash *hash_node=hash_map[hash_key%hash_size];
        struct Hash * new_node=NULL;
        if(!hash_node)
        {
            new_node=(struct Hash *)malloc(sizeof(struct Hash));
            new_node->next_hash=NULL;
            new_node->val=hash_key;
            new_node->save=false;
            hash_map[hash_key%hash_size]=new_node;
        }
        else
        {
            while(hash_node)
            {
                if(hash_node->val==hash_key)
                {
                    if(!hash_node->save)
                    {
                        hash_node->save=true;
                        (*returnSize)++;
                        ret=(char **)realloc(ret,sizeof(char *)*(*returnSize));
                        ret[(*returnSize)-1]=(char *)calloc(11,sizeof(char));
                        strncpy(ret[(*returnSize)-1],s+i,sizeof(char)*10);
                        printf("%s\n",ret[(*returnSize)-1]);
                    }
                    break;
                }
                else
                {
                    if(!hash_node->next_hash)
                    {
                        new_node=(struct Hash *)malloc(sizeof(struct Hash));
                        new_node->next_hash=NULL;
                        new_node->val=hash_key;
                        new_node->save=false;
                        hash_node->next_hash=new_node;
                        break;
                    }
                    hash_node=hash_node->next_hash;
                }
            }
        }
    }
    for(int i=0;i<hash_size;i++)
    {
        struct Hash *hash=hash_map[i];
        while(hash)
        {
            struct Hash *tmp=hash;
            hash=hash->next_hash;
            free(tmp);
        }
    }
    free(hash_map);
    return ret;
}

作者：mu-mian-hua-yu
链接：https://leetcode-cn.com/problems/repeated-dna-sequences/solution/c-hash-by-mu-mian-hua-yu-2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
