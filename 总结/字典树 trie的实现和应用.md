## 概念
### 性质
1. 字典树节点本身不存储完整单词，只存储当前节点到下一个节点的关系
2. 从跟节点到某一个节点的整个路径上经过的字符链接起来，是该节点对应的字符串
3. 每个节点到它的所有子节点路径代表的字符都不相同
## 实现
### 基于26个小写字符的字典树的创建，查询，前缀查询的实现代码
```
#define LEN 26
typedef struct _Trie {
    bool isEnd;
    struct _Trie* next[LEN];
} Trie;

/** Initialize your data structure here. */
Trie* trieCreate() {
    Trie* obj = (Trie*)malloc(sizeof(Trie));
    obj->isEnd = false;
    memset(obj->next, 0, sizeof(obj->next));
    return obj;    
}

/** Inserts a word into the trie. */
void trieInsert(Trie* obj, char * word) {
    Trie* tmp = obj;
    for (int i = 0; i < strlen(word); i++) {
        if (tmp->next[word[i] - 'a'] == NULL) {
            tmp->next[word[i] - 'a'] = trieCreate();
        }
        tmp = tmp->next[word[i] - 'a'];
    }
    tmp->isEnd = true; // 插入结束后，表面这个单词已经结束
}

/** Returns if the word is in the trie. */
bool trieSearch(Trie* obj, char * word) {
    Trie* tmp = obj;
    for (int i = 0; i < strlen(word); i++) {
        if (tmp->next[word[i] - 'a'] == NULL) {
            return false;
        }
        tmp = tmp->next[word[i] - 'a'];
    }
    return tmp->isEnd; // 看看最终有没有这个单词的标记符 true，有的话就是查到了
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool trieStartsWith(Trie* obj, char * prefix) {
    Trie* tmp = obj;
    for (int i = 0; i < strlen(prefix); i++) {
        if (tmp->next[prefix[i] - 'a'] == NULL) {
            return false;
        }
        tmp = tmp->next[prefix[i] - 'a']; // 找下一个节点
    }
    return true; // 只要没有遇到空，那肯定就有这个前缀。
}

void trieFree(Trie* obj) {
    if (obj == NULL) {
        return;
    }
    for (int i = 0; i < LEN; i++) {
        if (obj->next[i]) {
            trieFree(obj->next[i]);
        }
    }
    free(obj);
}
```

## 应用
