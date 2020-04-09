
int maxSpent = INT_MAX;
void step(int n, int curIdx, int dst, int visitedCnt, int** maps, int curSpent, int* visit, int k);

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int K){
    int maps[101][101] = {0};
    for (int i = 0; i < flightsSize; i++) {
        maps[flights[i][0]][flights[i][1]] = flights[i][2];
    }
    //int visit[101] = {0};
    int curSpent = 0;
    int visitedCnt = 0;
    int* visit = (int*)malloc(sizeof(int) * 101);
    
    visit[src] = false;
    step(n, src, dst, visitedCnt, maps, curSpent, visit, K);
    return maxSpent == INT_MAX ? -1 : maxSpent;
}

void step(int n, int curIdx, int dst, int visitedCnt, int** maps, int curSpent, int* visit, int k) {
    if (visitedCnt > k) {
        return;
    }
    int i = 0;
    for (i = 0; i < n; i++) {
        if (visit[i] == 1) {
            continue;
        }
        if (maps[curIdx][i] == 0) {
            continue;
        }
        if ((curSpent) + maps[curIdx][i] > maxSpent) {
            continue;
        }
        if (i == dst) {
            continue;
        }
       // if (maps[curIdx][i] != 0)// && visit[0] == 0)// &&  (curSpent) + maps[curIdx][i] < maxSpent) 
        {
            //if (i == dst) {
           //     maxSpent = (curSpent) + maps[curIdx][i];
           //     continue;
           // }
            //int spent = (curSpent) + maps[curIdx][i];
            //visit[i] = 1;
           // step(n, i, dst, visitedCnt + 1, maps, spent, visit, k);
            //visit[i] = 0;
        }
    }
}
