### 题目 图像渲染
思路：
该题目的意思是给定一个初始节点，在整个二维矩阵中和这个起始节点相邻（上下左右，其相邻节点再相邻）并且值和这个起始点的值一样的点改成一个新的颜色值。

1、常规思路是先找到需要修改的点，并把这些坐标存储下来，整个矩阵遍历完了，再逐个遍历需要修改的坐标，并把他们的值进行修改成新的值
这里是常规的DFS遍历，注意一下几点：
1.1、对于新的坐标点一定要新定义变量，在原来坐标基础上加上direct

1.2、对于找到的坐标，可以使用一维数组存储即可，二维坐标转一维的技巧 (x * 列的长度 + y), 写代码要仔细，注意行列变量。
这个坐标可以作为位置信息入栈，也可以作为访问标记数组的下标。

2、遍历结束后，在依次出栈，把出栈的元素，转换成坐标，并把对应的坐标改成新的颜色值。坐标转换时

x = data / 列的长度；
y = data % 列的长度；
注意一定要对列的长度取整合取余

3、其实该题限定了颜色值最大是65535，我们可以使用高16位来缓存改变后的值，比较时只比较低16位，在原地修改


### 代码
```

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct {
    int* data;
    int top;
} Stack;

Stack* CreateStack(int k)
{
    Stack* obj = NULL;
    obj = (Stack*)malloc(sizeof(Stack));
    if (obj == NULL) {
        return obj;
    }
    obj->data = (int*)malloc(sizeof(int) * k);
    memset(obj->data, 0, sizeof(int) * k);
    obj->top = -1;
    return obj;
}

bool IsStackEmpty(Stack* obj)
{
    if (obj == NULL) {
        return false;
    }
    return obj->top == -1;
}

bool PushStack(Stack* obj, int data) {
    if (obj == NULL) {
        return false;
    }
    obj->top++;
    obj->data[obj->top] = data;
    return true;
}

int PopStack(Stack* obj) {
    int data = INT_MIN;
    if (IsStackEmpty(obj)) {
        return data;
    }
    data = obj->data[obj->top];
    obj->top--;
    return data;
}

Stack* obj = NULL;
int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void dfs(int** image, int imageSize, int* imageColSize, int target,
    int x, int y, int* visit) {
    for (int k = 0; k < 4; k++) {
        int curRow = x + direct[k][0];
        int curColumn = y + direct[k][1];
        if (curRow < 0 || curRow > imageSize - 1 || curColumn < 0 || curColumn > *imageColSize -1) {
            continue;
        }
        if (image[curRow][curColumn] != target) {
            continue;
        }
        if (visit[curRow * (*imageColSize) + curColumn] != 0) {
            continue;
        }
        visit[curRow * (*imageColSize) + curColumn] = 1;
        PushStack(obj, curRow * (*imageColSize) + curColumn);
        dfs(image, imageSize, imageColSize, target, curRow, curColumn, visit);
    }
}

int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int newColor, int* returnSize, int** returnColumnSizes){
    int row = imageSize;
    int column = *imageColSize;
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * (row));
    memset((*returnColumnSizes), 0, sizeof(int) * (row));
    for (int i = 0; i < row; i++) {
        (*returnColumnSizes)[i] = column;
    }
    obj = CreateStack(row * column + 1);
    int target = image[sr][sc];
    int* visit = (int*)malloc(sizeof(int) * (row * column + 1));
    memset(visit, 0, sizeof(int) * (row * column + 1));
    visit[sr * (column) + sc] = 1;
    PushStack(obj, sr * (column) + sc);
    dfs(image, imageSize, imageColSize, target, sr, sc,visit);
    while(!IsStackEmpty(obj)) {
        int data = PopStack(obj);
        image[data / column][data % column] = newColor;
    }
    *returnSize = imageSize;
    return image;
}

int main(void)
{

    system("pause");
}
```
