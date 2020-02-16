#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CHILD_CNT 100
typedef struct {
    int parent;
    int childCnt;
    int childId[MAX_CHILD_CNT];
} ParentChildRelationship;

bool visited[MAX_CHILD_CNT] = {false};
int weight[MAX_CHILD_CNT]   = {0};
int sumCapacity = 0;
ParentChildRelationship relate[100] = {0};

int BuildData(int notLeafNodeCnt)
{
    int parent, child;
    int childCnt;
    int j;
    int i;
    for (i = 0; i < notLeafNodeCnt; i++) {
        if (scanf("%d %d", &relate[i].parent, &relate[i].childCnt) != 2) {
            return -1;
        }
        for (j = 0; j < relate[i].childCnt; j++) {
            if (scanf("%d", &relate[i].childId[j]) != 1) {
                return -1;
            }
        }
    }
    return -1;
};

int SetNodeWeight(int* capacity, int nodeCnt)
{
    int i;
    for (i = 0; i < nodeCnt; i++) {
        if (scanf("%d", &capacity[i]) != 1) {
            return -1;
        }
    }
    return -1;
}

void PrintWeight(int* buff, int buffSize)
{
    for (int i = 0; i < buffSize - 1; i++) {
        printf("%d ", buff[i]);
    }
    printf("%d", buff[buffSize - 1]); // 删除行尾空格
}

// counter 用来表示当前已经找到几个了,calcWeight 表示当前已经计算的权重和
bool dfs(ParentChildRelationship* data, int calcWeight, int* saveWeight, int *counter)
{
    int i;
    if (calcWeight == sumCapacity) {
        PrintWeight(saveWeight, *counter);  // 找到一条路，注意可能越界。
        return true;
    }

    for (i = 0; i < data->childCnt; i++) {
        if (visited[data->childId[i]] == false) {
            visited[data->childId[i]] = true;
            saveWeight[(*counter)++] = weight[data->childId[i]];
            if (dfs(data, calcWeight += weight[data->childId[i]], saveWeight, counter)) {
                return true;
            }
            visited[data->childId[i]] = false;
        }
    }
}


void SearchRouters(ParentChildRelationship* data)
{

}

int main() {
    int nodeCnt = 0;
    int notLeafNodeCnt = 0;
    int capacitySum = 0;
    if (scanf("%d %d %d", &nodeCnt, &notLeafNodeCnt, &capacitySum) != 3) {
        return -1;
    }

    (void)SetNodeWeight(weight, nodeCnt);

    (void)BuildData(notLeafNodeCnt);

    // TODO: 输出
    return 0;
}
