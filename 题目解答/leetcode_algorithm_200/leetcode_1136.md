### 题目
```
已知有 N 门课程，它们以 1 到 N 进行编号。

给你一份课程关系表 relations[i] = [X, Y]，用以表示课程 X 和课程 Y 之间的先修关系：课程 X 必须在课程 Y 之前修完。

假设在一个学期里，你可以学习任何数量的课程，但前提是你已经学习了将要学习的这些课程的所有先修课程。

请你返回学完全部课程所需的最少学期数。

如果没有办法做到学完全部这些课程的话，就返回 -1。

输入：N = 3, relations = [[1,3],[2,3]]
输出：2
解释：
在第一个学期学习课程 1 和 2，在第二个学期学习课程 3。

输入：N = 3, relations = [[1,2],[2,3],[3,1]]
输出：-1
解释：
没有课程可以学习，因为它们相互依赖。

```
### 思路
### 代码
```
#define MAX_NUM 5001
int minimumSemesters(int n, int** relations, int relationsSize, int* relationsColSize){
    int head = 0;
    int rear = 0;
    int queue[MAX_NUM];
    int* res = malloc(sizeof(int) * MAX_NUM);
    memset(res, 0, sizeof(int) * MAX_NUM);
    /* 首先将需要学习的课程加入 */
    for (int i = 0; i < relationsSize; i++) {
        res[relations[i][1]]++;
    }
    /* 将入度为0的课程加进来，注意从1开始 */
    for (int i = 1; i <= n; i++) {
        if (res[i] == 0) {
            queue[rear++] = i; /* 将课程编号加入到队列中 */
        }
    }

    int ans = 0;
    while(head < rear) {
        int tmpRear = rear;
        while (head < tmpRear) {
            for (int i = 0; i < relationsSize; i++) {
                /* 若找到依赖的课程，将其入度减一 */
                if (queue[head] == relations[i][0]) {
                    res[relations[i][1]]--;
                    /* 若入度变为0，则将其加入到队列中 */
                    if (res[relations[i][1]] == 0) {
                        queue[rear++] = relations[i][1];
                    }
                }
            }
            /* 注意：需要计算后再将head++ */
            head++;
        }
        /* ans代表bfs的循环圈数，也是每轮需要学习的课程数 */
        ans++;
    }

    /* 若加入队列的个数与课程数相同，说明找到了拓扑排序 */
    if (rear == n) {
        return ans;
    } else {
        return -1;
    }
}

作者：fuchao
链接：https://leetcode.cn/problems/parallel-courses/solution/ping-xing-ke-cheng-bi-jiao-rong-yi-li-ji-6f33/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
```
