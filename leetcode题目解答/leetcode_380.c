#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./uthash-master/src/uthash.h"

#define DATA_LENGTH    5000

struct hash {
    int key; // hash 表中key.
    int value; // 保存key在数组arr中的下标值。
    UT_hash_handle hh;
};

typedef struct {
    int* arr; // 存放已插入的所有元素
    int size; // 记录数组中元素的个数
    struct hash* hashTable; // 哈希表，便于O(1)时间插入和删除元素
} RandomizedSet;

RandomizedSet* randomizedSetCreate() {
    RandomizedSet* res = (RandomizedSet*)malloc(sizeof(RandomizedSet));
    res->arr = (int*)malloc(sizeof(int) * DATA_LENGTH);
    memset(res->arr, -1, sizeof(int) * DATA_LENGTH);
    res->size = 0;
    res->hashTable = NULL;
    return res;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    struct hash* hs;

    HASH_FIND_INT(obj->hashTable, &val, hs);
    if (!hs) { // 如果没有找到,就创建一个节点。
        hs = (struct hash*)malloc(sizeof(struct hash));
        hs->key = val;
        obj->arr[obj->size] = val;// 存入数组并记录其在数组中存储的下标值。
        hs->value = obj->size;
        obj->size++;
        HASH_ADD_INT(obj->hashTable, key, hs);
        return true;
    }
    return false;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    struct hash* hs1;
    struct hash* hs2;
    
    HASH_FIND_INT(obj->hashTable, &val, hs1);
    // 如果存在，则将数组中的最后一个元素放到当前位置，确保0---obj->size中的元素有效。
    if (hs1) {
        obj->arr[hs1->value] = obj->arr[obj->size - 1];
        HASH_FIND_INT(obj->hashTable, &obj->arr[obj->size - 1], hs2);
        hs2->value = hs1->value;
        obj->size--;
        HASH_DEL(obj->hashTable, hs1);
        return true; 
    }
    return false;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    return (obj->arr[rand() % obj->size]); // 对整个hash表大小取余确保不越界。
}

void randomizedSetFree(RandomizedSet* obj) {
    free(obj->hashTable);
    free(obj->arr);    
}

int main(void)
{
    RandomizedSet* hash = randomizedSetCreate();
    bool result = randomizedSetInsert(hash, 1);
    printf("\r\nresult=%u\r\n", result);
    result = randomizedSetInsert(hash, 2);
    printf("\r\nresult=%u\r\n", result); 
    result = randomizedSetInsert(hash, 2);  
    printf("\r\nresult=%u\r\n", result); 
    result = randomizedSetGetRandom(hash);
    printf("\r\nresult=%u\r\n", result); 
    system("pause");
}
