## UTHash 使用总结
```
struct HashTable {
  type key;
  type data;
  UT_hash_handle hh;
};

struct HashTable* users;
```
### 1、添加int类型的接口

HASH_ADD_INT(head, keyfield_name, item_ptr)

这里head就是全局变量users,这个users相等时一个表头， keyfield_name实际上是hash结构体中key。 item_ptr, 这里也就是指向待添加的节点的指针。举例：
```
struct HashTable* add;
add = (struct HashTable*)malloc(sizeof(struct HashTable));
add->key = key;
add->data = data;
HASH_ADD_INT(users, key, add);
```

### 2、查找int类型的接口
HASH_FIND_INT (head, key_ptr, item_ptr)

head是users, key_ptr是指向key的指针，item_ptr就是根据key找到hash表节点，举例：
```
struct HashTable* find;
int hashKey = key;
HASH_FIND_INT(users, &hashKey, find);
```

### 3、添加字符串 char str[] = {"hello"};类型的接口
HASH_ADD_STR (head, keyfield_name, item_ptr)

这里的第二个参数直接是key, item_ptr, 就是要添加的hash节点。
```
struct HashStr* tmp = (struct HashStr*)malloc(sizeof(struct HashStr));
strcpy(tmp->key, tempArr);
tmp->times = 1;
HASH_ADD_STR(users, key, tmp);
```

### 4、查找字符串 char str[] = {"hello"};类型的接口
HASH_FIND_STR (head, key_ptr, item_ptr)

```
char tempArr[11] = {0};
strncpy(tempArr, &s[i], 10);
HASH_FIND_STR(users, tempArr, findKey);
```
### 5、 添加指针型字符串 char* key = "hello"类型的接口
HASH_ADD_KEYPTR (hh_name, head, key_ptr, key_len, item_ptr)
这里hh_name,就是hash结构中的handle, hh. head 是users, key_ptr,就是要添加的key的指针， key_len是key的长度， item_ptr,就是要添加的节点指针

```
struct StrHash* input = (struct StrHash*)malloc(sizeof(struct StrHash));
input->str = searchStr;
input->times = 1;
HASH_ADD_KEYPTR(hh, users, input->str, strlen(input->str), input);
```
对于此类型的查找还是可以使用HASH_FIND_STR(users, "hello", hashNode);

### 6、查找结构体类型的key的接口
HASH_FIND (hh_name, head, key_ptr, key_len, item_ptr)

```
typedef struct {
  char a;
  int b;
} record_key_t;
typedef struct {
    record_key_t key;
    /* ... other data ... */
    UT_hash_handle hh;
} record_t;

l.key.a = 'a';
l.key.b = 1;
HASH_FIND(hh, records, &l.key, sizeof(record_key_t), p);
```


### 7、添加结构体类型的key的接口
HASH_ADD (hh_name, head, keyfield_name, key_len, item_ptr)
```
r = (record_t *)malloc(sizeof *r);
memset(r, 0, sizeof *r);
r->key.a = 'a';
r->key.b = 1;
HASH_ADD(hh, records, key, sizeof(record_key_t), r);
```
### 8、hash表排序接口
HASH_SORT (head, cmp)
```
int Cmp(const void* a, const void* b)
{
    return ((struct HashTable*)b)->times - ((struct HashTable*)a)->times;
}

HASH_SORT(users, Cmp);
```
其中cmp是基于什么条件排序的函数。

### 9、删除hash节点的接口
HASH_DEL (head, item_ptr)

item_ptr就是要删除的节点。对于删除了的节点要释放内存。
```
HASH_ITER(hh, users, cur, tmp) {
     HASH_DEL(users, cur);
     free(cur);
}
```

### 10、hash表的迭代接口
HASH_ITER (hh_name, head, item_ptr, tmp_item_ptr)
每次遍历得到的节点就是 item_ptr.对于需要的数据就从这个节点中获取。
```
struct HashTable* cur;
struct HashTable* tmp;

HASH_ITER(hh, users, cur, tmp) {
  result[*returnSize] = cur->key;
     (*returnSize)++;
     if (*returnSize >= k) {
         break;
  }
}
```

小结： 对于查找类接口，第二个参数都是要查找的key的指针，对于添加类接口，第二个参数直接是hash结构中定义的key。
