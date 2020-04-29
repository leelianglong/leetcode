/*
* 本题采用并查集来解决。
* 前面是并查集的基本函数
* 关键点： 并查集的元素到底是多少个？ 这个是有实体个数来确定的。不要以题目给的表示方式来确定，本次只有N个同学，但是表示它们之间朋友关系时
*         采用矩阵的形式来给出，所以在使用并查集解答时，不要把元素看成 N*N个，而是看成 N个。
*/

typedef struct {
    int* parent;
    int counter;
} UFstruct;

UFstruct* UFInit(int n)
{
    UFstruct* tmp = (UFstruct*)malloc(sizeof(UFstruct));
    tmp->parent = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        tmp->parent[i] = i;
    }
    tmp->counter = n;
    return tmp;
}

// 查找节点x的根节点，某个节点的根节点的值就是它本身
int UFfind(UFstruct*tmp, int x)
{
    while(x != tmp->parent[x]) {
        x = tmp->parent[x];
    }
    return x;
}

void UFUnion(UFstruct* tmp, int p, int q)
{
    int rootP = UFfind(tmp, p);
    int rootQ = UFfind(tmp, q);
    if (rootQ == rootP) {
        return;
    }
    tmp->parent[rootP] = rootQ;
    tmp->counter--;
}


int findCircleNum(int** M, int MSize, int* MColSize){
    int row = MSize;
    UFstruct* save = UFInit(row);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            if (M[i][j] == 1) {
                UFUnion(save, i, j);
            }
        }
    }
    return save->counter; 
}
