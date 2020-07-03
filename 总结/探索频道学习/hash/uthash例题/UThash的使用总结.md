## UTHash 使用总结

struct HashTable {
  type key;
  type data;
  UT_hash_handle hh;
};

struct HashTable* users;

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
