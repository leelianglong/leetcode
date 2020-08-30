### 题目 leetcode 692

题目要求前K个高频出现的字符串，如果有2个字符串的出现次数一样，则按照字典序输出

思路：
1、 使用UThash， 把字符串添加到hash表.这里要注意，如果hash结构中key是指针形式的，添加节点时，也要使用对应的指针形式。
```
struct StrHash {
    const char* str;
    int times;
    UT_hash_handle hh;
};
这里 str 是指针，所以在添加节点时要使用的接口是：HASH_ADD_KEYPTR（）
        s = (struct my_struct *)malloc(sizeof *s);
        s->name = names[i];
        s->id = i;
        HASH_ADD_KEYPTR( hh, users, s->name, strlen(s->name), s );

```
如果是数组形式的，则直接使用HASH_ADD_STR()接口
```
struct StrHash {
    const char str[100];
    int times;
    UT_hash_handle hh;
};
        s = (struct my_struct *)malloc(sizeof *s);
        strcpy(s->name, names[i]);
        s->id = i;
        HASH_ADD_STR( users, name, s );
```

2、对hash表排序。根据题目要求，要求前k个高频词，如果频度一样，就按字典序排序。所以排序函数如下

```
int TimesSort(struct StrHash* a, struct StrHash* b)
{   if (a->times != b->times) {
        return (b->times - a->times);
    } 
    return strcmp(a->str, b->str);
}

调用 UThash的排序函数直接排序

HASH_SORT(users, TimesSort);
```

### 代码
```
 struct StrHash {
    const char* str;
    int times;
    UT_hash_handle hh;
};

struct StrHash* users;

int TimesSort(struct StrHash* a, struct StrHash* b)
{   if (a->times != b->times) {
        return (b->times - a->times);
    } 
    return strcmp(a->str, b->str);
}

char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize){
    *returnSize = 0;
    if (wordsSize <= 0) {
        return NULL;
    }
    users = NULL;
    char** result = (char**)malloc(sizeof(char*) * wordsSize);
    for (int i = 0; i < wordsSize; i++) {
        struct StrHash* search;
        char* searchStr = words[i];
        HASH_FIND_STR(users, searchStr, search);
        if (search == NULL) {
            struct StrHash* input = (struct StrHash*)malloc(sizeof(struct StrHash));
            input->str = searchStr;
            input->times = 1;
            HASH_ADD_KEYPTR(hh, users, input->str, strlen(input->str), input);
        } else {
            search->times++;
        }
    }
    HASH_SORT(users, TimesSort);
    struct StrHash* cur;
    struct StrHash* tmp;
    HASH_ITER(hh, users, cur, tmp) {
        //printf("\n%s %d", cur->str, cur->times);
        if (*returnSize >= k) {
            break;
        }
        result[*returnSize] = (char*)malloc(strlen(cur->str) + 1);
        memset(result[*returnSize], 0, strlen(cur->str) + 1);
        strcpy(result[*returnSize], cur->str);
        (*returnSize)++;
    }
    return result;
}
```
