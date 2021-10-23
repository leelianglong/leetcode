### 剑指 Offer II 034. 外星语言是否排序
#### 思路
1. 对顺序字符串进行hash处理，记录每个字符的位置。因为顺序字符不会重复，所以他们的位置是唯一的
2. 逐个把words中的2个字符串，各个字符映射到顺序字符串hash表上。比较2个字符串中字符在顺序表中的位置，如果第一个字符串的字符所在的位置大于第二个字符串，则返回false。
#### 代码
```
#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool isAlienSorted(char ** words, int wordsSize, char * order){
    int len = strlen(order);
    int orderMap[26] = {0}; // 存储每个字符的位置。
    for (int i = 0; i < len; i++) {
        orderMap[order[i] - 'a'] = i; 
    } 
    
    for (int i = 0; i < wordsSize - 1; i++) {
        char* s1 = words[i];
        char* s2 = words[i + 1];
        for (int j = 0; j < MAX(strlen(s1), strlen(s2)); j++) {
            int pos1 = j >= strlen(s1) ? -1 : orderMap[s1[j] - 'a'];
            int pos2 = j >= strlen(s2) ? -1 : orderMap[s2[j] - 'a'];
            if (pos1 > pos2) {
                return false;
            } 
            if (pos1 < pos2) {
                break;
            }
        }
    }
    return true;
}
```