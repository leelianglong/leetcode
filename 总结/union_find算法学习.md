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

## 练习题目： leetcode 990

### 思路
1、把相等的先连接起来
2、再查看步相等的，看看不相等的和之前已经判断相等是不是有冲突，如果有冲突，则要返回false
3、UF算法，关键要选择好空间大小，例如这里就要选择26，不是表达式的个数，因为无论表达式是什么，他们都说由26个字母组成的。
   另外，对存储空间的初始化也很关键，要初始化成0---N - 1， 不能初始化成0
   
### 思路
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
