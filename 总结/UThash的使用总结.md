## UTHash 使用总结

使用UThash只需要包含 uthash.h 头文件即可


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

这里head就是全局变量users,这个users相当是一个表头， keyfield_name实际上是hash结构体中key。 item_ptr, 这里也就是指向待添加的节点的指针。

添加的操作要点是： 要创建一个添加节点 struct HashObj* 需要分配内存，然后初始化这个节点。使用标准的宏，宏中第一个参数是表头，第二个参数是固定的key, 第三个参数就是创建的节点
举例：
```
struct HashTable* add;
add = (struct HashTable*)malloc(sizeof(struct HashTable));
add->key = key;
add->data = data;
HASH_ADD_INT(users, key, add);
```

### 2、查找int类型的接口
HASH_FIND_INT (head, key_ptr, item_ptr)

head是users, key_ptr是指向key的指针，item_ptr就是根据key找到hash表节点，

查找的操作：先定义一个struct HashObj* 的节点，无需初始化，另外把查找的值设置成key, 使用HASH_FIND_INT()宏，第一个参数是表头，第二个参数是 &key, 第三参数是 查找节点。
举例：
```
struct HashTable* find;
int hashKey = key;
HASH_FIND_INT(users, &hashKey, find);
```

### 3、添加字符串 char str[] = {"hello"};类型的接口
HASH_ADD_STR (head, keyfield_name, item_ptr)

这里的第二个参数直接是key, item_ptr, 就是要添加的hash节点。

添加字符串时，直接将字符串拷贝到添加节点里面。
添加字符串的标准宏HASH_ADD_STR()的第二个参数是任然是key.

```
struct HashStr {
    char key[11];
    int id;
    UT_hash_handle hh;
};

struct HashStr* tmp = (struct HashStr*)malloc(sizeof(struct HashStr));
strcpy(tmp->key, tempArr);
tmp->times = 1;
HASH_ADD_STR(users, key, tmp);
```

### 4、查找字符串 char str[] = {"hello"};类型的接口
HASH_FIND_STR (head, key_ptr, item_ptr)

这里把要查找的字符串当作key, 把字符串的地址传到宏中，第3个参数是查找节点。

```
char tempArr[11] = {0};
strncpy(tempArr, &str[i], 10);
HASH_FIND_STR(users, tempArr, findKey);

```
### 5、 添加指针型字符串 char* key = "hello"类型的接口
HASH_ADD_KEYPTR (hh_name, head, key_ptr, key_len, item_ptr)
这里hh_name,就是hash结构中的handle, hh. head 是users, key_ptr,就是要添加的key的指针， key_len是key的长度， item_ptr,就是要添加的节点指针

```
struct StrHash{
   const char* str;
   int id;
   UT_hash_handle hh;
};

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

record_t l;
record_t* users;

l.key.a = 'a';
l.key.b = 1;
HASH_FIND(hh, users, &l.key, sizeof(record_key_t), p);
```


### 7、添加结构体类型的key的接口
HASH_ADD (hh_name, head, keyfield_name, key_len, item_ptr)
```
r = (record_t *)malloc(sizeof *r);
memset(r, 0, sizeof *r);
r->key.a = 'a';
r->key.b = 1;
HASH_ADD(hh, users, key, sizeof(record_key_t), r);
```
注意这里最后的参数r 不是hash节点，而是添加的元素节点的指针。


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

HASH_CLEAR(hh, users);
当前接口一次删除所有的节点

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

### 11、hash count 接口
计算当前hash表中有多少个元素
HASH_COUNT(users)  这里users是hash表头
```
unsigned int num_users;
num_users = HASH_COUNT(users);
printf("there are %u users\n", num_users);
```


###小结

1、对于查找类接口，第二个参数都是要查找的key的指针，对于添加类接口，第二个参数直接是hash结构中定义的key。

2、对于全局变量 users的定义， 要在外面定义，然后在函数执行开始的地方，初始化成 NULL，就会避免全局变量对多个用例的影响。也可以在函数退出前使用HASH_ITER（）来逐个释放hash节点。

3、对于字符串 和 单个数字的添加操作时，HASH_ADD_XX()的最后一个参数是hash节点，只不过这个节点中包含了要添加的值。对于结构体的添加方式来说，最后一个参数是要添加的结构体指针。

3、对于结构体的hash操作来讲，HASH_ADD的参数是 hh, users, key, key的长度，添加节点。 总共4个参数
