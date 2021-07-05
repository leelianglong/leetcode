### leetcode 946
#### 思路
1. 使用一个栈用来辅助验证，让push数组中数字入栈的，取出栈顶元素，和pop数组中的数字比较，如果相等，则把该元素出栈，pop数组中继续下一个比较。如果不相等，则把push数组中的这个数字入栈。
2. 当push数组中数字遍历完了之后，查看辅助栈中是否为空，如果为空，则说明是栈的序列，反之不是
#### 代码
```
#define COUNT  1002
typedef struct {
    int data[COUNT];
    int top;
} Stack;

Stack* Init(void)
{
    Stack* obj = (Stack*)malloc(sizeof(Stack));
    memset(obj->data, 0, sizeof(int) * COUNT);
    obj->top = -1;
    return obj;
}

bool IsEmpty(Stack* obj)
{
    return obj->top == -1;
}

bool isFull(Stack* obj)
{
    return obj->top == COUNT - 1;
}

void push(Stack* obj, int element)
{
    if (isFull(obj)) {
        return;
    }
    obj->top++;
    obj->data[obj->top] = element;
}

void pop(Stack* obj, int* element)
{
    if (IsEmpty(obj)) {
        return;
    }
    *element = obj->data[obj->top];
    obj->top--;
}

int getTop(Stack* obj)
{   
    return obj->data[obj->top];
}

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize){
    Stack* obj = Init();
    int element = 0;
    int index = 0;

    for (int i = 0; i < pushedSize; i++) {
        push(obj, pushed[i]);
        while (!IsEmpty(obj) && getTop(obj) == popped[index]) {
            pop(obj, &element);
            index++;
        }
    }
    return IsEmpty(obj);
}
```