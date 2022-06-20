### 题目
```
给你一个二叉树的根结点，返回其结点按 垂直方向（从上到下，逐列）遍历的结果。
如果两个结点在同一行和列，那么顺序则为 从左到右。

输入：root = [3,9,20,null,null,15,7]
输出：[[9],[3,15],[20],[7]]

输入：root = [3,9,8,4,0,1,7]
输出：[[4],[9],[3,0,1],[8],[7]]

输入：root = [3,9,8,4,0,1,7,null,null,null,2,5]
输出：[[4],[9,5],[3,0,1],[8,2],[7]]

```

### 思路
1.采用队列，进行层次遍历。
2.需要定义一个数据结构，存储当前节点与位置的关系。
3.我们把root节点的位置定义成一个常数，例如题解中定义的500，然后层次遍历各节点，对于其左子树这个位置就减一，对于右子树这个位置就加一。
4.使用2个变量minId,maxId,用来标记当前层最左端和最右端的位置
5.下面curId这个变量就是一条垂线，在这个线上的元素都应该放在一起，这条线上有多少个元素，由columnSizes[curId]表示。
6.遍历结束后，把minId映射到0位置，然后取出相应的元素



### 代码
```
typedef struct {
    struct TreeNode* node;//记录当前节点，
    int id; // 记录当前节点所在位置。以root 为0，左子树的位置--， 右子树的位置++。
} TreeNode;

#define CNT 10000
#define SIZE 1000
int** verticalOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    *returnSize = 0;
    if (root == NULL) {
        return NULL;
    }
    TreeNode queue[CNT];
    int res[SIZE][SIZE];
    int columnSizes[CNT] = {0};
    int minId = INT_MAX;
    int maxId = INT_MIN;
    int front = 0;
    int rear = 0;
    queue[rear].node = root;
    queue[rear].id = 500; // 500的含义就是把root的位置定义为500，然后左子树的位置就减一，右子树的位置就加1.
    rear++;

    while (front < rear) {
        int curSize = rear - front;
        //printf("curSize=%d\n", curSize);
        for (int i = 0; i <curSize; i++) {
            struct TreeNode* curNode = queue[front].node;
            int curId = queue[front].id;
            minId = fmin(minId, curId);
            maxId = fmax(maxId, curId); // 这里maxId 和 minId就记录了最宽的层有多少个节点。
            printf("111 curId=%d maxId=%d minId=%d\n", curId, maxId, minId);
            res[curId][columnSizes[curId]] = curNode->val;
            columnSizes[curId]++; // 当前列的元素又多了一个
            front++;
            if (curNode->left) {
                queue[rear].node = curNode->left;
                queue[rear].id = curId - 1; // 左子树位置减一
                rear++;
            }
            if (curNode->right) {
                queue[rear].node = curNode->right;
                queue[rear].id = curId + 1; // 右子树位置加1
                rear++;
            }
        }
    }
    int idSize = maxId - minId + 1; // 计算最宽的层有多少个。
    int**result = (int**)calloc(idSize, sizeof(int*));
    *returnColumnSizes = (int*)calloc(idSize, sizeof(int));

    for (int i = 0; i < idSize; i++) {
        result[i] = res[i + minId]; // root 节点的位置是500，这里去掉偏移。
        (*returnColumnSizes)[i] = columnSizes[i + minId];
    }
    *returnSize = idSize;
    return result;
}
```
