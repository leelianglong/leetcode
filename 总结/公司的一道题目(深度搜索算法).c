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


一个参考解法：
解题思路：

【解题思路】
首先理解题目，这是个树的搜索，题目要求搜索出总值等于给定输入的所有路径，并且将找到的路径按照“非递增”的方式输出。这就涉及到两个考点：1搜索树，1 不同的队列按照非递增排序。结合题目附带的代码，main函数可以设计出三段内容：1 使用合适的数据结构保存输入的数据；2 利用合适的算法找出所有路径；3 找出所有总值等于给定输入s的路径集合（这一步可以在步骤2一并实现，不过会增加步骤2的复杂度，容易增加调试时间），并按“非递增”方式输出这些路径的值。题目给定了一些条件，根节点固定是“00”，用例保证至少有一条路径满足要求，可以简化解题步骤。
1、	使用合适的数据结构保存输入的数据
这一步决定了步骤2的算法的复杂度，由于题目中的数不是常规的二叉树，又是单向查找，终结条件就是找到的节点是否叶子节点，可以采用广度优先的算法。将根节点和下一级叶子节点的集合的映射保存起来，采用广度优先算法遍历搜索。
至于每个编号的值，题目明确了是按照编号顺序赋值，可以直接采用一个数组把输入的值依次获取到。
2、	利用合适的算法找出所有路径
步骤1决定了使用广度优先算法，剩下的就是实现方式的事了，可以采用遍历或者递归，递归一般条件设置不好调试很麻烦，因此采用偏暴力的遍历方法。首先初始化一个根节点作为起始搜索结果paths，然后基于这个起始搜索结果，根据节点的子节点集合进行循环遍历
3、	找出所有总值等于给定输入s的路径集合，并按“非递增”方式输出这些路径的值
Paths找到之后，判断是否相等就很简单了，难点在要对待输出paths的集合进行排序，参照输入样例（下图），按照数组的列的顺序依次比较，大的排前面。这个算法如果用暴力破解，没想出来，不过下面这个图，横着看很像4个值很大的数字，那么我们的算法就是把这4个path数组，变成4个double的值，然后排序即可。

/*
* Copyright (c) Huawei Technologies Co., Ltd. 2019-2019. All rights reserved.
* Description: 树形网络
* Note: 缺省代码仅供参考，可自行决定使用、修改或删除
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>

using namespace std;

void searchAllPaths(vector <vector <int> > & paths, map <int, vector <int> > maps)
{
    /*
     * 算法的思路就是，paths已经有一个初始成员root了，那么设置一个while循环遍历paths数组，如果发现数组中的子数组末端有子节点
     * ，那么就把该子数组乘以子节点数量的倍数复制，然后把新增的path添加到paths二维数组中。
     * 设置结束条件end，就是遍历paths中所有成员数组末端，都找不到子节点，就结束
     */
    bool end = false;
    while (!end) {
        end = true;
        int size = paths.size();  // 这里要先取当前循环的次数，因为找到子节点集合时会复制新增path成员，paths.size()会变化
        for (int i = 0; i < size; i++) {
            vector <int>::reverse_iterator ri = paths[i].rbegin();
            int seriNo = *ri;
            auto search = maps.find(seriNo);
            if (search == maps.end()) { // 尾节点是个叶子，遍历下一个
                continue;
            }
            end = false;
            vector <int> searchVec = search->second;
            // 先把当前子序列和第一个元素接上，然后再遍历subVec后面的成员，添加对应队列到paths的末尾
            vector <int> subVec = paths[i];
            paths[i].push_back(searchVec[0]); // 第一个元素原地拼接
            for (int j = 1; j < searchVec.size(); j++) {
                paths.push_back(subVec);
                paths[paths.size() - 1].push_back(searchVec[j]);
            }
        }
    }
    return;
}

int getPathSum(vector <int> path, vector <int> value)
{
    int sum = 0;
    for (int i = 0; i < path.size(); i++) {
        sum += value[path[i]];
    }
    return sum;
}

void outputVector(vector <int> path, vector <int> weight)
{
    for (int i = 0; i < path.size(); i++) {
        cout << weight[path[i]];
        if (i < (path.size() - 1)) {
            cout << " ";
        }
    }
    cout << endl;
}

void outputUnassend(vector <vector <int> > paths, vector <int> weight)
{
    int maxSize = 0;
    vector <double> value; // 定义一个double类型的动态数组，用于装载转换后的数字

    // 先找出输出列表中最长的子数组的长度，作为double数字的进位次数
    for (int i = 0; i < paths.size(); ++i) {
        maxSize = paths[i].size() > maxSize ? paths[i].size() : maxSize;
    }

    // 先把每个子数组第一个值装载到double数组中对应的值
    for (int i = 0; i < paths.size(); ++i) {
        value.push_back(weight[paths[i][0]]);
    }

    for (int i = 1; i < maxSize; ++i) {
        int maxValue = 0;
        // 先计算当前这一列各数组成员最大的数值是哪个，取出来计算需要进多少位
        for (int j = 0; j < paths.size(); ++j) {
            if (i < paths[j].size()) {
                maxValue = weight[paths[j][i]] > maxValue ? weight[paths[j][i]] : maxValue;
            }
        }
        // 计算进位数
        int multiNum = 1 + log10(maxValue);

        // 按照进位数，将数字value乘以对应的倍数再加上本队列对应的值
        for (int j = 0; j < paths.size(); ++j) {
            if (i < paths[j].size()) {
                value[j] = value[j] * pow(10 , multiNum) + weight[paths[j][i]];
            } else {
                value[j] = value[j] * pow(10 , multiNum);
            }
        }
    }

    /* 
     * 根据value数组元素的大小，由大到小输出对应的path。
     * 这里value数组的下标和paths下标是一样的，但是value排序后就错乱了，不好输出，
     * 需要设计一个关联数据结构，把value和paths关联起来并将value排序，C++现成的就是map，插入后天然排好序。
     * 考虑到value可能相等，采用multimap
     */
    multimap <double, vector <int> > multiMp;
    for (int i = 0; i < paths.size(); ++i) {
        multiMp.insert(make_pair(value[i], paths[i]));
    }

    multimap <double, vector <int> >::reverse_iterator it = multiMp.rbegin();
    for (; it != multiMp.rend(); ++it) {
        outputVector(it->second, weight);
    }

    return;
}

int main(void)
{
    int n, m, s;
    map <int, vector <int> > relation;
    vector <vector <int> > paths;    // 二维动态数组，用于广度优先搜索算法时作为队列使用
    vector <int> weight;

    // 1.1 使用数组weight保存每个容器的值
    cin >> n >> m >> s;
    for (int loop = 0; loop < n; loop++) {
        int w;
        cin >> w;
        weight.push_back(w);
    }

    // 1.2 使用MAP来保存容器编号parent和对应子节点容器编号集合data的关系
    for (int loop = 0; loop < m; loop++) {
        int parent;
        int childCnt;
        vector <int> data;
        cin >> parent >> childCnt;
        for (int loop2 = 0; loop2 < childCnt; loop2++) {
            int child;
            cin >> child;
            data.push_back(child);
        }
        relation.insert(make_pair(parent, data));
    }

    // 2.1 把所有编号排个序，然后把值取到一个MAP中，这一步题目存在歧义，先忽略
    // 2.2 先把根节点00构造成一个初始化path，开始遍历
    vector <int> root(1, 0);
    paths.push_back(root);
    searchAllPaths(paths, relation);

    // 3.1 遍历所有path，检查总和是否和输入相等，相等就保存到输出数组output中，不在原二维数组上操作，主要是麻烦
    vector <vector <int> > output;
    for (int i = 0; i < paths.size(); i++) {
        int sum = getPathSum(paths[i], weight);
        if (sum == s) {
            output.push_back(paths[i]);
        }
    }
    // 3.2按照非递增序输出
    outputUnassend(output, weight);
    return 0;
}

