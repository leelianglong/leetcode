BFS一般是把一些问题抽象成图，从一个点开始，向四周扩散，找到从起点start 到终点target的最近距离。

BFS使用的核心数据结构是队列，即先进先出的线性存储结构。我采用数组来默认队列。这里需要注意下面节点：

1、需要入队的元素结构，例如需要把 TYPE 入队，那么在申请内存时，要使用(TYPE*)malloc(sizeof(TYPE) * 1000);

2、定义2个变量指向队头front和对尾rear。

3、入队操作：queue[rear++] = data; 出队操作 front++; 获取对头元素 data = queue[front]; 判断队列是否为空 （front == rear）


BFS的框架：

void BFS (root) {

  1、申请队列，用例存储元素  
  
  2、如果是树，具有明显的前后顺序关系，这里就不用设置访问标记，否则，设置一个visited[MAX] = {0} 的标记
  
  3、将第一个元素入队，并将访问标记置位 visited[root] = true;
  
  4、以队列不为空为条件，不停的进行入队和出队的循环 while （front ！= rear）{
    
    4.1、获取当前队列大小 curSize = rear - front;
    
    4.2、以curSize为循环大小，依次出队。（这里可以判断，是否到了终点 target，如果到了就退出）
    
    4.3、每出队一个元素，就把和它相邻的元素依次入队。（注意这里相邻的意义）
    
    4.5、进行步数更新。（要在出队的for循环外面）
  }
  
}

下面以LeetCode：559，N叉树的最小高度。

这里就是判断这个N叉树有多少层，

```
int bfs(struct Node* root)
{
    if (root == NULL) {
        return 0;
    }
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * 10000);
    int front = 0; 
    int rear = 0;
    int max = 0;
    queue[rear++] = root; // 根节点入队
    while (front != rear) {
        int queueSize = rear - front;
        for (int k = 0; k < queueSize; k++) {
            struct Node* curNode = queue[front]; // 获取对头元素
            front++; // 出队
            int childNum = curNode->numChildren;
            for (int m = 0; m < childNum; m++) {
                queue[rear++] = curNode->children[m];
            }
        }
        max++; // 一层结束了，高度加1.
    }
    return max;
}

int* maxDepth(struct Node* root) {
    return bfs(root);    
}
```

leetcode 752 :

BFS中比较关键的一点是:

1、如何找相邻的元素? 对于本题，相邻元素的定义是： “每次旋转都只能旋转一个拨轮的一位数字”

对于一个状态，比如“0000”， 有4个轮子，每次只能拨1个，拨的方向有2种，向上，向下；所以一个初始状态有8种相邻的状态。

因此对于出队的一个元素，把8种相邻的元素入队。

2、入队时，要检测一下元素是否被访问过，访问过了，就不在入队了，所以需要一个全局的数组来记录每一个元素是否被访问

3、在求相邻状态时，由于对同一个状态既要求向上转，也要求下下转，所以这个初始状态在求相邻状态时，不能修改这个初始状态，否则有问题。

```
char* UpWheelChangeStr(char* str, char wheelPos)
{
    char tmpSave[5] = {0};
    strcpy(tmpSave, str);
    char* res = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    memset(res, 0, sizeof(char) * (strlen(str) + 1));
    if (tmpSave[wheelPos] == '9') {
        tmpSave[wheelPos] = '0';
    } else {
        tmpSave[wheelPos] += 1;
    }
    strcpy(res, tmpSave);
    return res;
}

char* DownWheelChangeStr(char* str, char wheelPos)
{
    char tmpSave[5] = {0};
    strcpy(tmpSave, str);
    char* res = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    memset(res, 0, sizeof(char) * (strlen(str) + 1));
    if (tmpSave[wheelPos] == '0') {
        tmpSave[wheelPos] = '9';
    } else {
        tmpSave[wheelPos] -= 1;
    }
    strcpy(res, tmpSave); 
    return res;
}

int openLock(char ** deadends, int deadendsSize, char * target){
    int queue[10000][5] = {0};
    int front = 0;
    int rear = 0;
    strcpy(queue[rear++], "0000");
    bool visited[10000] = {0};
    visited[atoi("0000")] = true;
    int step = 0;
    bool isDeadFlg = false;
    
    while (front != rear){
        int curSize = rear - front;
        for (int i = 0; i < curSize; i++) {
            char* curNode = queue[front];
            front++;
            //printf("\n F: %s", curNode);
            for (int j = 0; j < deadendsSize; j++) {
                if (strcmp(curNode, deadends[j]) == 0) {
                    isDeadFlg = true;
                    //printf("\nfind dead: %s", deadends[j]);
                    break;
                }
            }
            if (isDeadFlg) {
                isDeadFlg = false;
               // printf("\nfind dead1");
                continue;
            }
            if (strcmp(curNode, target) == 0) {
                return step;
            }
            for (int k = 0; k < 4; k++) {
                //printf("\n T: %s", curNode);
                char* up = UpWheelChangeStr(curNode, k);
                //printf("\n U:%s", up);
                if (!visited[atoi(up)]) {
                    //printf("\nU: %s", up);
                    strcpy(queue[rear++], up);
                    visited[atoi(up)] = true;
                }
                char* down = DownWheelChangeStr(curNode, k);
                //printf("\n D:%s", down);
                if (!visited[atoi(down)]) {
                   // printf("\nD: %s", down);
                    strcpy(queue[rear++], down);
                    visited[atoi(down)] = true;
                }
            }
        }
        step++;
    }
    return -1;
}
```

leetcode 542 (01矩阵，给定一个由0 和 1 组成的矩阵，找到每个元素到最近的0的距离，2个相邻元素的距离是1)

分析：看到最近距离，要朝BFS方向思考，为什么说BFS就能找最近的距离？ 因为从BFS的本质就能够看出，BFS解决的是从某个起点到target的最短距离。它的搜索是

从起点开始向四周扩散，遇到target就停止。

本题的关键点：
1、找到相邻元素，这里的相邻元素是指上下左右4个元素，题目也给出提示了

2、确定队列要存储什么？本题矩阵只有0 和 1，要求某点到最近0的距离，所以不能把元素存储到队列中，要存储的是每次访问元素的坐标。另外对于坐标，是以（x，y）的形式，还是一维的一个数字？ 对于矩阵来说，可以直接存储一个数字，通过数字对每列元素个数取余和取模，换算成坐标。

3、出队后查找其相邻的元素再入队时要注意：使用访问标记，另外出队的元素要和再次入队的元素要有联系，例如本题，再次入队的坐标要在出队的坐标基础上进行4个方向偏移。

4、使用另外一个数据区来存储，修改后的矩阵，搜索时，在原矩阵中搜索，避免在原矩阵中修改了，影响后续的搜索。

```
int visited[10000] = {false};
int queue[10000] = {-1};
int fixColum = 0;
int fixRow = 0;
int direct[4][2] = {
    {1,0}, {0,1},{-1,0},{0,-1}
};

int bfs(int** matrix, int curRow, int curColumn)
{
    for (int i = 0; i < 10000; i++) {
        queue[i] = -1;
        visited[i] = false;
    }
    int front = 0;
    int rear = 0;
    int step = 0;
    queue[rear++] = curRow * fixColum + curColumn;//matrix[curRow][curColumn];
    visited[curRow * fixColum + curColumn] = true;
    //printf("\nenter %d %d", curRow, curColumn);
    while (front != rear) {
        int curSize = rear - front;
        //printf("\nqueue %d %d\n", front, rear);
      //  for(int i = front; i <= rear; i++) {
            //printf("%d ", queue[i]);
      //  }
        for (int i = 0; i < curSize; i++) {
            int head = queue[front++];
            if (matrix[head / fixColum][head % fixColum] == 0) { // 找到最近的0了
                //printf("\n Bfs find");
                return step;
            }
            for (int k = 0; k < 4; k++) {
                int dx = head / fixColum + direct[k][0]; // 这里是关键点：下次搜索要以上次出队的坐标为基础，在此之上进行偏移。
                int dy = head % fixColum + direct[k][1];
                if (dx < 0 || dx > fixRow - 1 || dy < 0 || dy > fixColum - 1) {
                    continue;
                }
                //printf("\n pos (%d %d)", dx, dy);
                //printf("element (%d) visit (%d)",  matrix[dx][dy], visited[dx * fixColum + dy]);
                if (!visited[dx * fixColum + dy]) {
                    queue[rear++] = dx * fixColum + dy;//matrix[dx][dy];
                    visited[dx * fixColum + dy] = true;
                }
            }
        }
        //printf("\n step++");
        step++;
    }
    return -1;
} 

int** updateMatrix(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes){
    fixColum = *matrixColSize;
    fixRow = matrixSize;
    *returnSize = 0;

    int** res = (int**)malloc(sizeof(int*) * matrixSize);
    for (int i = 0; i < matrixSize; i++) {
        res[i] = (int*)malloc(sizeof(int) * fixColum);
    }
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < fixColum; j++) {
            res[i][j] = matrix[i][j];
        }
    }
    //res = matrix;
    for (int i = 0; i < fixRow; i++) {
        for (int j = 0; j < fixColum; j++) {
            if (matrix[i][j] == 1) {
                int pos = bfs(matrix, i, j);
                if (pos > -1) {
                    res[i][j] = pos;
                    //printf("\nfind pos(%d)", pos);
                }
            }
        }
    }
    *returnSize = matrixSize;
    *returnColumnSizes = (int*)malloc(sizeof(int) * matrixSize);
    for (int k = 0; k < matrixSize; k++) {
        (*returnColumnSizes)[k] = fixColum;
    }
    return res;
}
```


