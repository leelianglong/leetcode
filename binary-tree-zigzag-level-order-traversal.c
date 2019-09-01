#include <stdio.h>
#include <stdlib.h>
/*
给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

例如：
给定二叉树 [3, 9, 20, null, null, 15, 7],

 3
/ \
9  20
   / \
  15  7
返回锯齿形层次遍历如下：

[
    [3],
    [20, 9],
    [15, 7]
]

来源：力扣（LeetCode）
链接：https ://leetcode-cn.com/problems/binary-tree-zigzag-level-order-traversal
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
构造一个栈结构
*/

#define STACK_LENGTH   100

typedef struct {
    int top;
    int data[100];
}Stack;

int InitStack(Stack* para)
{
    int i;
    if (para == NULL) {
        return -1;
    }
    para->top = -1;
    for (i = 0; i < STACK_LENGTH; i++) {
        para->data[i] = 0;
    }
    return 0;
}

int PushStack(Stack* para, int data)
{
    if (para == NULL) {
        return -1;
    }
    if (para->top > STACK_LENGTH - 1) {
        return -1;
    }
    para->top++;
    para->data[para->top] = data;
    return 0;
}

int PopStack(Stack* para, int* data)
{
    if (para == NULL) {
        return -1;
    }
    if (para->top < 0) {
        return -1;
    }
    *data = para->data[para->top];
    para->top--;
    return 0;
}

int main(void)
{
    Stack para = { 0 };
    int i ;
    int ret[10];

    InitStack(&para);
    for (i = 0; i < 10; i++) {
        PushStack(&para, i);
    }

    for (i = 0; i < 10; i++) {
        PopStack(&para, &ret[i]);
    }

    for (i = 0; i < 10; i++) {
        printf("%4d", ret[i]);
    }
}