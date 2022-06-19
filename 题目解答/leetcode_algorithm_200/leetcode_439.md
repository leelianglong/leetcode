### 题目
```
给定一个表示任意嵌套三元表达式的字符串 expression ，求值并返回其结果。

你可以总是假设给定的表达式是有效的，并且只包含数字， '?' ，  ':' ，  'T' 和 'F' ，其中 'T' 为真， 'F' 为假。表达式中的所有数字都是 一位 数(即在 [0,9] 范围内)。

条件表达式从右到左分组(大多数语言中都是这样)，表达式的结果总是为数字 'T' 或 'F' 。
输入： expression = "T?2:3"
输出： "2"
解释： 如果条件为真，结果为 2；否则，结果为 3。

输入： expression = "F?1:T?4:5"
输出： "4"
解释： 条件表达式自右向左结合。使用括号的话，相当于：
 "(F ? 1 : (T ? 4 : 5))" --> "(F ? 1 : 4)" --> "4"
or "(F ? 1 : (T ? 4 : 5))" --> "(T ? 4 : 5)" --> "4"

输入： expression = "T?T?F:5:3"
输出： "F"
解释： 条件表达式自右向左结合。使用括号的话，相当于：
"(T ? (T ? F : 5) : 3)" --> "(T ? F : 3)" --> "F"
"(T ? (T ? F : 5) : 3)" --> "(T ? F : 5)" --> "F"

```

### 思路
1.因为是从右开始的结合的，所以倒序访问。
2.遇到问号出栈，根据规则计算，然后在入栈。

### 代码
```
#define CNT 10002

typedef struct {
    char sysbol[CNT];
    int sysbolTop;
} SysbolStack;

SysbolStack* sysbolStackinit()
{
    SysbolStack* obj = (SysbolStack*)calloc(1, sizeof(SysbolStack));
    memset(obj->sysbol, 0, sizeof(char) * CNT);
    obj->sysbolTop  = -1;
    return obj;
}

void sysbolStackpush(SysbolStack* obj, char num)
{
    obj->sysbolTop++;
    obj->sysbol[obj->sysbolTop] = num;
}

char sysbolStackpop(SysbolStack* obj) {
    char element = obj->sysbol[obj->sysbolTop];
    obj->sysbolTop--;
    return element;
}

char getTop(SysbolStack* obj)
{
    return obj->sysbol[obj->sysbolTop];
}

bool empty(SysbolStack* obj)
{
    return obj->sysbolTop == 1;
}

void reverve(char* s)
{
    int len = strlen(s);
    int i = 0;
    int j = len;
    for (i = 0, j = len - 1; i <= j; i++, j--) {
        char tmp = s[j];
        s[j] = s[i];
        s[i] = tmp;
    }
}

#define IS_NUM(a)   ((a >= '0') && (a <= '9'))

char * parseTernary(char * s){
    int len = strlen(s);
    char sysbol = 0;
    SysbolStack* obj = sysbolStackinit();
    for (int i = len - 1; i >= 0; i--) {
        if (s[i] == 'T' || s[i] == 'F' || IS_NUM(s[i])) {
            sysbolStackpush(obj, s[i]);
            continue;
        }
        if (s[i] == '?') {
            char a1 = sysbolStackpop(obj);
            char b1 = sysbolStackpop(obj);
            sysbol = s[i - 1] == 'T' ? a1 : b1;
            i--;
            sysbolStackpush(obj, sysbol);
        }
    }
    char* res = (char*)calloc(2, sizeof(char));
    res[0] = sysbol;
    return res;
}
```
