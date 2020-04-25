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




