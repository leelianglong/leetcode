union-find 代码如下：
```
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int* size = NULL; // 用于存储每颗树的子节点树
int* parent = NULL; // 用于存储每个节点的父节点
int counter = 0;  // 连通分量个数

void UFInit(int n)
{
    parent = (int*)malloc(sizeof(int) * n);
    memset(parent, 0, sizeof(int) * n);

    size = (int*)malloc(sizeof(int) * n);
    memset(size, 0, sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1; // 初始化时每个节点的子树都是1，每个节点的父节点是自己
    }
    counter = n;
}

// 用来查找x节点的根节点
int find (int x)
{
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

// 把2个节点p  和 q 连通
void union_element(int p, int q)
{
    int rootP = find(p);
    int rootQ = find(q);

    if (rootP == rootQ) { // 节点p和q的根节点一样，他们必然连通
        return;
    }

    if (size[rootP] > size[rootQ]) {
        parent[rootQ] = rootP;
        size[rootP] += rootP;
    } else {
        parent[rootP] = rootQ;
        size[rootQ] += size[rootP];
    }
    counter--;
}

bool isConnected(int p, int q)
{
    int rootP = find(p);
    int rootQ = find(q);
    return rootP == rootQ;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
```
