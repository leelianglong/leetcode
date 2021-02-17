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
### leetocde 212
#### 思路
1. 先创建字典树，将words中的单词添加到字典树中
2. 使用dfs(实际上是回溯)在二维数组 board上都搜索，这里需要准备的参数主要有，board， 当前坐标，返回结果存储，中间临时结果存储。
3. 在dfs时，当遍历的当前字符的当前trie节点不为空时，说明当前这个字符是我们需要的，把这个字符暂存下来。接下来就把字典树走到下一个节点去
4. 当当前节点已经是某个前缀的结束节点时，就可以把暂存的字符串拷贝到返回的结果中，并把当前这个结束节点置为false。
5. 典型的4个方向进行搜索。注意这里没有使用访问标记，在四个方向搜索前，先把当前坐标的字符保存下来，然后置为一个不可能的值。当4个方向搜索完了之后，在把这个坐标上的字符回复。

#### 代码
```
#define      LEN         26
typedef struct __Trie {
    bool isEnd;
    struct __Trie* next[LEN];
} Trie;

Trie* Create(void)
{
    Trie* obj = (Trie*)malloc(sizeof(Trie));
    obj->isEnd = false;
    memset(obj->next, 0, sizeof(obj->next));
    return obj;
}

void Insert(Trie* obj, char* word)
{
    Trie* tmp = obj;
    for (int i = 0; i < strlen(word); i++) {
        if (tmp->next[word[i] - 'a'] == NULL) {
            tmp->next[word[i] - 'a'] = Create();
        }
        tmp = tmp->next[word[i] - 'a'];
    }
    tmp->isEnd = true;
}

int row;
int column;
int direction[4][2] = {{1,0},{0,1}, {-1,0}, {0,-1}};
void dfs(char** board, Trie* tree, int x, int y, char** res, int* returnSize, char* tmpSave, int pos)
{
    if (tree->next[board[x][y] - 'a']) {
        tree = tree->next[board[x][y] - 'a']; // 遍历下一个节点
        tmpSave[pos++] = board[x][y];
        if (tree->isEnd) {
            res[*returnSize] = (char*)malloc(sizeof(char) * (pos + 1));
            memset(res[*returnSize], 0, sizeof(char) * (pos + 1));
            strncpy(res[*returnSize], tmpSave, pos);
            (*returnSize)++;
            tree->isEnd = false;
        }
        char ch = board[x][y];
        board[x][y] = '#';
        for (int i = 0; i < 4; i++) {
            int xx = x + direction[i][0];
            int yy = y + direction[i][1];
            if (xx < 0 || yy < 0 || xx >= row || yy >= column) {
                continue;
            }
            if (board[xx][yy] == '#') {
                continue;
            }
            dfs(board, tree, xx, yy, res, returnSize, tmpSave, pos);
        }
        board[x][y] = ch;
    }
}


#define  COUNT 30001
char ** findWords(char** board, int boardSize, int* boardColSize, char ** words, int wordsSize, int* returnSize){
    *returnSize = 0;
    if (boardSize == 0 || boardColSize[0] == 0 || wordsSize == 0) {
        return NULL;
    }
    row = boardSize;
    column = boardColSize[0];
    char** res = (char**)malloc(sizeof(char*) * COUNT);
    Trie* obj = Create();
    for (int i = 0; i < wordsSize; i++) {
        Insert(obj, words[i]);
    }
    char* tmpSave = (char*)malloc(sizeof(char) * (12));
    memset(tmpSave, 0, sizeof(char) * 12);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            dfs(board, obj, i, j, res, returnSize, tmpSave, 0);
        }
    }
    return res;
}
```

### leetcode 720
#### 思路
1.创建字典树。把所有的字符串都添加到字典树中
2.逐个遍历字符串中的每个字符，在字典树中查找是不是结束符。如果是结束字符，则遍历下一个节点，如果不是结束符，则说明当前这个字符串是无关的，不需要考虑。这是因为，按照题意，最长的字符串是有字符串中每个字符串，逐个增加一个字符得到的。则意味着字符串中每个字符都有可能是结束符的。
3.把一个字符串遍历完了，就把它同结果集中的字符串比较长短，使结果集中的字符串始终最长，如果结果集和当前字符串是等长的，取字典序较小的。
#### 代码
```
#define LEN  26
typedef struct __Trie {
    bool isEnd;
    struct __Trie* next[LEN];
} Trie;

Trie* Create(void)
{
    Trie* obj = (Trie*)malloc(sizeof(Trie));
    obj->isEnd = false;
    memset(obj->next, 0, sizeof(obj->next));
    return obj;
}

void Insert(Trie* obj, char* word)
{
    Trie* tmp = obj;
    for (int i = 0; i < strlen(word); i++) {
        if (tmp->next[word[i] - 'a'] == NULL) {
            tmp->next[word[i] - 'a'] = Create();
        }
        tmp = tmp->next[word[i] - 'a'];
    }
    tmp->isEnd = true;
}

char * longestWord(char ** words, int wordsSize){
    Trie* obj = Create();
    for (int i = 0; i < wordsSize; i++) {
        Insert(obj, words[i]);
    }
    char* res = (char*)malloc(sizeof(char) * 31);
    memset(res, 0, sizeof(char) * 31);
    bool flg = true;
    for (int i = 0; i < wordsSize; i++) {
        Trie* tmp = obj;
        flg = true;
        for (int j = 0; j < strlen(words[i]); j++) {
            if (tmp->next[words[i][j] - 'a']->isEnd == false) { 
                flg = false;
                break;
            }
            tmp = tmp->next[words[i][j] - 'a'];
        }
        if (flg) {
            if (strlen(words[i]) > strlen(res)) {
                strncpy(res, words[i], strlen(words[i]));
            } else if (strlen(words[i]) == strlen(res) && strcmp(words[i], res) < 0){
                strncpy(res, words[i], strlen(words[i]));
            }
        }
    }
    return res;
}
```
