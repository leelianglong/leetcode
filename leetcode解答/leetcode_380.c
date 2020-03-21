#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./uthash-master/src/uthash.h"

#define DATA_LENGTH    5000

struct hash {
    int key; // hash ����key.
    int value; // ����key������arr�е��±�ֵ��
    UT_hash_handle hh;
};

typedef struct {
    int* arr; // ����Ѳ��������Ԫ��
    int size; // ��¼������Ԫ�صĸ���
    struct hash* hashTable; // ��ϣ������O(1)ʱ������ɾ��Ԫ��
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
    if (!hs) { // ���û���ҵ�,�ʹ���һ���ڵ㡣
        hs = (struct hash*)malloc(sizeof(struct hash));
        hs->key = val;
        obj->arr[obj->size] = val;// �������鲢��¼���������д洢���±�ֵ��
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
    // ������ڣ��������е����һ��Ԫ�طŵ���ǰλ�ã�ȷ��0---obj->size�е�Ԫ����Ч��
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
    return (obj->arr[rand() % obj->size]); // ������hash���Сȡ��ȷ����Խ�硣
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
