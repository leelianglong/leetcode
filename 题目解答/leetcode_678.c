leetcode 678
题目大意：
1. 字符串中有'(' ')' '*' 要求括号字符串有效，有效的要求如下：
   1.1. 左括号 和 右括号 必须匹配
   1.2. *可以表示任意的左括号，右括号，或者空字符
   1.3. 空字符串也是有效的
   1.4. 左括号一定要在右括号的左边。
   
2. 对于这种明显有栈特点的题目，首先考虑使用栈，栈中要存储什么元素呢？ 这里有个1.4的要求，可得我们要存储它们字符出现的索引，而不是字符的本身。
   这里多了*的处理，我们使用2个栈，分别存储左括号 和 星号出现的索引。
   
3. 先把左括号和*索引入栈，如果遇到右括号时，则出栈，出栈时，先出左括号的，如果左括号栈为空，则出*栈的，如果次数信号栈为空了，则说明字符串已经不满足有效性了。

4.当遍历完字符串后，在分别分析左括号和*号栈，在它们不为空的情况下，分别出栈，在出栈之前先判断一下栈顶元素，如果出现*栈的元素大于左括号栈的，则返回失败，

5.最终查看左括号中是否为空，如果不为空，则字符串也不是有效的。



代码：
typedef struct {
    int* buf;
    int top;
} Stack;

Stack* Init(int n)
{
    Stack* obj = (Stack*)malloc(sizeof(Stack));
    obj->buf = (int*)malloc(sizeof(int) * n);
    obj->top = -1;
    return obj;
}
bool IsEmpty(Stack* obj)
{
    return obj->top < 0;
}

bool Push(Stack* obj, int element)
{
    obj->top++;
    obj->buf[obj->top] = element;
    return true;
}

int GetTop(Stack* obj) 
{
    return obj->buf[obj->top];
}

bool Pop(Stack* obj, int* element)
{
    if (IsEmpty(obj)) {
        return false;
    }
    *element = obj->buf[obj->top];
    obj->top--;
    return true;
}

bool checkValidString(char * s){
    if (strlen(s) == 0) {
        return true;
    }
    int length = strlen(s);
    Stack* charStack = Init(length);
    Stack* starStack = Init(length);
    for (int i = 0; i < length; i++) {
        if (s[i] == '(') {
            Push(charStack, i);
        } else if (s[i] == '*'){
            Push(starStack, i);
        } else {
            if (!IsEmpty(charStack)) {
                int element = 0;
                Pop(charStack, &element);
            } else {
                if (IsEmpty(starStack)) {
                    return false;
                } else {
                    int element = 0;
                    Pop(starStack, &element);
                }
            }
        }
    }
    // 遍历完字符串了，分析2个栈中的数据，要求左括号要在右括号的左边，所以逐个取出栈顶元素进行比较。
    while(!IsEmpty(charStack) && !IsEmpty(starStack)) {
        if (GetTop(charStack) > GetTop(starStack)) { /
            return false;
        }
        int element = 0;
        Pop(charStack, &element);
        Pop(starStack, &element);
    }

    return IsEmpty(charStack);
}
