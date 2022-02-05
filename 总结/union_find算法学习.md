union-find 代码如下：
该算法解决图的连通性问题。连同性的性质：

1、自反性，字节P和自身是连同的；

2、对称性，如果节点P 和 Q 是连通的，那么Q 和 P也是连通

3、传递性， 如果节点P 和 Q连通，那么Q 和 P也是连通的。

4、连通性的结构体包含3个元素，分别表示某个节点的父节点 parent， 某个节点有多少个子节点我们称之为重量 weight，以及当前连通分量

5、连通结构主要有3个方法：
find（）主要功能是从某个节点遍历到树根，就是找某个节点的跟节点
union（） 主要功能是把2个节点连通起来，并把连通分量减 1

6、对于实际的问题 leetcode130， parent数组中存储的不是矩阵中某个具体的值本身，而是它们的坐标，连通时，也是把它们的坐标设置成连通的
   另外朋友圈的题目 547，则parent中存储的N个同学，而不是题目中给出的朋友关系的坐标。
   所以这里parent数组中到底需要多大，存储什么，这个就是要连通的实体个数，以及如何表示这些连通实体。
 
关键点： 初始化时，数组内容要是 0 --- n - 1,不能初始化成0；并且初始化化连通分量 为 n. union处理的过程中，2个节点的根节点不一样时，是吧根节点赋值到数组中，不是单个节点本身。

### 常规写法：
```
typedef struct {
    int nodeCounter;
    int* buff;
} UF;


UF* InitUf(int n)
{
   UF* tmp = (UF*)malloc(sizeof(UF));
   tmp->buff = (int*)malloc(sizeof(int) * n);
   tmp->nodeCounter = n;

   for (int i = 0; i < n; i++) {
       tmp->buff[i] = i; // tmp->buff[i]的意义是 节点i 的根节点
   }
   return tmp;
}

/* 用于返回某个节点的根节点 */
int Find(UF* obj, int x)
{
    while (obj->buff[x] != x) {
        x = obj->buff[x];
    }
    return x;
}

void UnionFind(UF* object, int p, int q)
{
    int rootP = Find(object, p);
    int rootQ = Find(object, q);

    if (rootP == rootQ) {
        return;
    }
    object->buff[rootP] = rootQ; // 将2个树合并成一棵树，也就是将一棵树的根节点，接到另一个树的根节点上。
    object->nodeCounter--;
}

int IsConnected(UF* obj, int p, int q)
{
    int rootP = Find(obj, p);
    int rootQ = Find(obj, q);
    return rootP == rootQ;
}

```


### 优化算法

```
typedef struct {
    int* weight;
    int* parent;
    int counter;
} UFStruct;

UFStruct* UFInit(int n)
{
    UFStruct* tmp = (UFStruct*)malloc(sizeof(UFStruct));
    tmp->parent = (int*)malloc(sizeof(int) * n);
    tmp->weight = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        tmp->parent[i] = i;
        tmp->weight[i] = 1; // 初始化时每个节点的子树都是1，每个节点的父节点是自己
    }
    tmp->counter = n;
    return tmp;
}

// 用来查找x节点的根节点
int find (UFStruct* data, int x)
{
    while (data->parent[x] != x) {
        data->parent[x] = data->parent[data->parent[x]]; // 路径压缩
        x = data->parent[x];
    }
    return x;
}

// 把2个节点p  和 q 连通
void union_element(UFStruct* data, int p, int q)
{
    int rootP = find(data, p);
    int rootQ = find(data, q);

    if (rootP == rootQ) { // 节点p和q的根节点一样，他们必然连通
        return;
    }

    if (data->weight[rootP] > data->weight[rootQ]) {
        data->parent[rootQ] = rootP;
        data->weight[rootP] += rootP;
    } else {
        data->parent[rootP] = rootQ;
        data->weight[rootQ] += data->weight[rootP];
    }
    data->counter--;
}

bool isConnected(UFStruct* data, int p, int q)
{
    int rootP = find(data, p);
    int rootQ = find(data, q);
    return rootP == rootQ;
}

```

## 练习题目： 
### leetcode 990
#### 思路
1、把相等的先连接起来

2、再查看不相等的，看看不相等的和之前已经判断相等是不是有冲突，如果有冲突，则要返回false

3、UF算法，关键要选择好空间大小，例如这里就要选择26，不是表达式的个数，因为无论表达式是什么，他们都说由26个字母组成的。
   另外，对存储空间的初始化也很关键，要初始化成0---N - 1， 不能初始化成0
   
#### 代码
```
typedef struct {
	int* buff;
	int nodeCounter;
} UF;

UF* InitUf(int n)
{
	UF* obj = (UF*)malloc(sizeof(UF));
	obj->buff = (int*)malloc(sizeof(int) * n);
	//memset(obj->buff, 0, sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            obj->buff[i] = i;
        }
	obj->nodeCounter = n;
	return obj;
}

int Find(UF* obj, int x)
{
	while ( obj->buff[x] != x) {
		x = obj->buff[x];
	}
	return x;
}

void Uinon(UF* obj, int p, int q)
{
	int rootP = Find(obj, p);
	int rootQ = Find(obj, q);
	if (rootP == rootQ) {
		return;
	}
	obj->buff[rootP] = rootQ;
	obj->nodeCounter--;
}

bool Connected(UF* obj, int p, int q)
{
	int rootP = Find(obj, p);
	int rootQ = Find(obj, q);
	return rootP == rootQ;
}

bool equationsPossible(char ** equations, int equationsSize){
    UF* obj = InitUf(26);
	for (int i = 0; i < equationsSize; i++) {
		if (equations[i][1] == '=') {
			Uinon(obj, equations[i][0] - 'a', equations[i][3] - 'a');
		}
	}
	
	for (int i = 0; i < equationsSize; i++) {
		if (equations[i][1] == '!') {
			if (Connected(obj, equations[i][0] - 'a', equations[i][3] - 'a')) {
				return false;
			}
		}
	}
	return true;
}
```

### leetcode 200

#### 思路
1. 当前并查集的数据空间是整个二维矩阵的所有坐标
2. 要算岛屿的数量，先把相邻的陆地连起来。还有剩下的就是没有相邻的陆地 和 水。
3. 在合并相邻陆地的时候，并查集中已经把count减减了，所以剩下的就是不相邻的陆地 和 水了，这里的陆地实际上也就是岛屿了，所以从总的数据空间中 - 相邻陆地数目 - 水的数量， 剩下的就是岛屿

#### 代码
```
typedef struct {
    int* buff; // 用于存储数据
    int counter; // 表示数据多少
} UnionFind;

UnionFind* InitUf(int counter)
{
    UnionFind* obj = (UnionFind*)malloc(sizeof(UnionFind));
    obj->buff = (int*)malloc(sizeof(int) * counter);
    memset(obj->buff, 0, sizeof(int) * counter);
    obj->counter = counter;
    for (int i = 0; i < counter; i++) {
        obj->buff[i] = i;
    }
    return obj;
}

int Find(UnionFind* obj, int p)
{
    while(p != obj->buff[p]) {
        p = obj->buff[p];
    }
    return p;
}

// 把2个元素连通在一起
void Union(UnionFind* obj, int p, int q)
{
    int rootP = Find(obj, p);
    int rootQ = Find(obj, q);
    if (rootP == rootQ) {
        return;
    }
    obj->buff[rootP] = rootQ;
    obj->counter--; // 连通在一起就把这个counter减1.
}

int dircet[4][2] = {{1,0},{0,1}, {-1, 0}, {0, -1}};
int numIslands(char** grid, int gridSize, int* gridColSize){
    if (gridSize <= 0) {
        return 0;
    }
    int row = gridSize;
    int col = *gridColSize;
    UnionFind* obj = InitUf(row * col);
    int p;
    int q;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == '0') {
                continue;
            }
            p = i * col + j;
            for (int k = 0; k < 4; k++) {
                int dx = i + dircet[k][0];
                int dy = j + dircet[k][1];
                if (grid[dx][dy] == '0') {
                    continue;
                }
                
                if ( dx < 0 || dx > row -1 || dy < 0 || dy > col - 1) {
                    continue;
                }
                q = dx * col + dy;
                Union(obj, p, q);
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (grid[i][j] == '0') {
                counter++;
            }
        }
    }
    printf("\ncounter=%u, %u\n", counter,obj->counter);
    return obj->counter - counter;
}
```

### leetcode 547
#### 思路
1. 有n个城市，有相邻的也有没有相邻的。
2. 定义省份的概念是：直接相邻的或者间接相邻的城市。
3. 有N X N的矩阵，用来标示这N个城市是否相邻。
4. 计算省份的个数

#### 代码
```
typedef struct {
    int* root;
    int count;
} UnionFind;

UnionFind* Init(int count)
{
    UnionFind* obj = (UnionFind*)malloc(sizeof(UnionFind));
    obj->root = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        obj->root[i] = i;
    }
    obj->count = count;
    return obj;
}

int find(UnionFind* obj, int x)
{
    while (x != obj->root[x]) {
        x = obj->root[x];
    }
    return x;
}

void Union(UnionFind* obj, int x, int y)
{
    int rootp = find(obj,x);
    int rootq = find(obj,y);
    if (rootp == rootq) {
        return;
    }
    obj->root[rootp] = rootq;
    obj->count--;
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize){
    int row = isConnectedSize;
    UnionFind* obj = Init(row);
    for (int i = 0; i < row; i++) {
        for (int j = i + 1; j < row; j++) {
            if (isConnected[i][j] == 1) {
                Union(obj, i, j);
            }
        }
    }
    return obj->count;
}
```

### leetcode 684
#### 思路
1. 题意是一颗树，树里有一个附件加的边，这个边不属于树， 这个边使树中存在环了。
2. 现在需要找到这个附加边，并把它删除，注意这个边一定是靠后的边。
3. 这个怎么和并查集联系？ 实际上一个树就是一个集合，他们有共同的一个跟节点。所以当前就依次遍历各个边，如果还不属于一个集合，就把这条边添加到集合中，如果发现当前的这条边已经和现有集合是一起的话，说明这个边就是多余的。


#### 代码
```
typedef struct {
    int* buff;
    int count;
} UnionFind;

UnionFind* Init(int count)
{
    UnionFind* obj = (UnionFind*)malloc(sizeof(UnionFind));
    obj->buff = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        obj->buff[i] = i;
    }
    obj->count = count;
    return obj;
}

int find(UnionFind* obj, int x)
{
    while (x != obj->buff[x]) {
        x  = obj->buff[x];
    }
    return x;
}

void Union(UnionFind* obj, int x, int y)
{
    int rootp = find(obj, x);
    int rootq = find(obj, y);
    if (rootp == rootq) {
        return;
    }
    obj->buff[rootq] = rootp;
    obj->count--;
}

bool IsConnected(UnionFind* obj, int x, int y)
{
    int rootp = find(obj, x);
    int rootq = find(obj, y);
    return rootp == rootq;
}

int* findRedundantConnection(int** edges, int edgesSize, int* edgesColSize, int* returnSize){
    UnionFind * obj = Init(edgesSize + 1);
    *returnSize = 2;
    int * res = (int*)malloc(sizeof(int) * 2);
    memset(res, 0, sizeof(int) * 2);

    for (int i = 0; i < edgesSize; i++) {
        if (IsConnected(obj, edges[i][0], edges[i][1])) {
            res[0] = edges[i][0];
            res[1] = edges[i][1];
        } else {
            Union(obj, edges[i][0], edges[i][1]);
        }
    }
    return res;
}
```

### leetcode 947
#### 思路
主要把在同一行的同一列的石子合并到一起。用总的石子数 减去 并查集中剩余的石子数， 就是移除的石子数。

#### 代码
```
typedef struct {
    int* buff;
    int count;
} UnionFind;

UnionFind* Init(int count)
{
    UnionFind* obj = (UnionFind*)malloc(sizeof(UnionFind));
    obj->buff = (int*)malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        obj->buff[i] = i;
    }
    obj->count = count;
    return obj;
}

int find(UnionFind* obj, int x)
{
    while(x != obj->buff[x]) {
        x = obj->buff[x];
    }
    return x;
}

void Union(UnionFind* obj, int x, int y)
{
    int rootp = find(obj, x);
    int rootq = find(obj, y);
    if (rootp == rootq) {
        return;
    }
    obj->buff[rootq] = rootp;
    obj->count--;
}

bool IsConnected(UnionFind* obj, int x, int y)
{
    int rootp = find(obj, x);
    int rootq = find(obj, y);

    return rootp == rootq;   
}

int removeStones(int** stones, int stonesSize, int* stonesColSize){
    UnionFind* obj = Init(stonesSize);

    for (int i = 0; i < stonesSize - 1; i++) {
        for (int j = i + 1; j < stonesSize; j++) {
            if (stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1]) { // 把同一行的 或者 同一列的元素合并。
                Union(obj, i, j);
            }
        }
    }
    return stonesSize - obj->count; // 用总的石子数，减去并查集中剩余的石子数，就是移除的石子数
}
```

### 剑指 Offer II 111. 计算除法
### 思路
1. 通过已知的表达式推导出其他表达式的值。这种适合并查集。这里涉及到权重(weight),不同于一般的并查集。
2. 表达式的值就是这个weight。注意需要通过不同的换算得到具体的值。
3. 注意这里weight的计算：
 g_save[x].weight = g_save[x].weight * g_save[orign].weight
 
 g_save[rootx].weight = g_save[y].weight * values / g_save[x].weight

### 代码
```
#define STR_LEN 6
typedef struct {
    char keyName[STR_LEN];
    int parentId;
    double weight;
}Union;

#define  NODE_MAX_COUNT 40
Union g_save[NODE_MAX_COUNT];
int g_nodeCnt;

int findRoot(int x)
{
    if (x != g_save[x].parentId) {
        int orign = g_save[x].parentId;
        g_save[x].parentId = findRoot(orign);
        g_save[x].weight = g_save[x].weight * g_save[orign].weight;
    }
    return g_save[x].parentId;
}

void UnionFind(int x, int y, double values)
{
    int rootx = findRoot(x);
    int rooty = findRoot(y);
    if (rootx != rooty) {
        g_save[rootx].parentId = rooty;
        g_save[rootx].weight = g_save[y].weight * values / g_save[x].weight;
    }
}

int findStr(char* str)
{
    for (int i = 0; i < g_nodeCnt; i++) {
        if (strcmp(g_save[i].keyName, str) == 0) {
            return i;
        }
    }
    return -1;
}

double getResult(const char* str1, const char* str2)
{
    int key1 = findStr(str1);
    if (key1 == -1) {
        return -1.0;
    }

    int key2 = findStr(str2);
    if (key2 == -1) {
        return -1.0;
    }

    int rootx = findRoot(key1);
    int rooty = findRoot(key2);
    if (rootx == rooty) {
        return g_save[key1].weight / g_save[key2].weight;
    }
    return -1.0;
}
double* calcEquation(char *** equations, int equationsSize, int* equationsColSize, double* values, int valuesSize, char *** queries, int queriesSize, int* queriesColSize, int* returnSize){
    g_nodeCnt = 0;
    for (int i = 0; i < NODE_MAX_COUNT; i++) {
        g_save[i].parentId = i;
        g_save[i].weight = 1.0;
        memset(g_save[i].keyName, 0, STR_LEN);
    }

    for (int i = 0; i < equationsSize; i++) {
        char* name1 = equations[i][0];
        char* name2 = equations[i][1];
        int keyIdx1 = findStr(name1);
        if (keyIdx1 == -1) {
            keyIdx1 = g_nodeCnt;
            strncpy(g_save[keyIdx1].keyName, name1, strlen(name1));
            g_nodeCnt++;
        }
        int keyIdx2 = findStr(name2);
        if (keyIdx2 == -1) {
            keyIdx2 = g_nodeCnt;
            strncpy(g_save[keyIdx2].keyName, name2, strlen(name2));
            g_nodeCnt++;
        }
        UnionFind(keyIdx1, keyIdx2, values[i]);
    }
    double* res = (double*)malloc(sizeof(double) * queriesSize);
    memset(res, 0, sizeof(double) * queriesSize);
    for (int i = 0; i < queriesSize; i++) {
        char* str1 = queries[i][0];
        char* str2 = queries[i][1];
        res[i] = getResult(str1, str2);
    }
    *returnSize = queriesSize;
    return res;
}
```
