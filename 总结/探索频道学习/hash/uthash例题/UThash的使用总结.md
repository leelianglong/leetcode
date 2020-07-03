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
add->pos = pos;
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
