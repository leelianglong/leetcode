#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*该题的思路是：在有向图中找是否有环*/

bool find(int num, int **parr, int row, int column, int vst[num], int index) {
    int i;
    static int counter = 0;
    printf("\r\n%2d\r\n", counter);
    counter++;
    if(vst[index]) {  // 如果当前节点访问过了，意味着出现了环。
        printf("\r\nfirst %2d\r\n", index);
        return true;
    }
    for(i=0; i<row; i++){
        if(parr[index][i] != 1) {
            printf("\r\nindex %2d %2d\r\n", index, i);
            continue;
        }
        vst[index] = 1;
        if(find(num, parr, row, column, vst, i)) {
            printf("\r\nsecond %2d\r\n", i);
            return true; // 表示找到i 这个点了。
        }
        vst[index] = 0;
    }

    return false;
}

// 这里每个课只依赖一门课程，所以这里prerequisitesColSize 始终是2.
bool canFinish(int num, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    if(!num || !prerequisites ||!prerequisitesSize || !prerequisitesColSize[0])
        return true;

    bool ret = true;
    int i,j;
    int vst[num];
    int **arr = (int **)malloc(sizeof(int *) * num);
    memset(arr, 0, sizeof(int*) * num);
    for(i=0; i<num; i++){
        arr[i] = (int *)malloc(sizeof(int) * (num));
        memset(arr[i], 0, sizeof(int) * (num));
    }

    for(i=0; i<prerequisitesSize; i++){
        arr[prerequisites[i][0]][prerequisites[i][1]] = 1;
        printf("\r\n%2d %2d\r\n", prerequisites[i][0], prerequisites[i][1]);
    }

    for(i=0; i<num; i++){
        memset(vst, 0, sizeof(vst));
        if(find(num, arr, num, (num), vst, i)){  //  这里是在一个 num  * num 的矩阵中找到访问过的点后，就表示出现环了。
            ret = false;
            break;
        }
    }

    for(i=0; i<num; i++){
        free(arr[i]);
    }
    free(arr);

    return ret;
}


int main() {
    int tmp[5][2] = {
            {3,4},
            {2,5},
            {1,7},
            {0,1},
            {6,7}
    };
    int** test = (int**)malloc(sizeof(int*) * (sizeof(tmp) / sizeof(tmp[0])));
    int i;
    int j;
    for (i = 0; i < (sizeof(tmp) / sizeof(tmp[0])); i++) {
        test[i] = (int*)malloc(sizeof(int) * 2);
    }

    for (i = 0; i < (sizeof(tmp) / sizeof(tmp[0])); i++) {
        for (j = 0; j < 2; j++) {
            test[i][j] = tmp[i][j];
        }
    }
    printf("\r\nhello test\r\n");
    int courseNum = 8;
    int prerequisitesColSize = 2;
    bool result = canFinish(courseNum, test, (sizeof(tmp) / sizeof(tmp[0])), &prerequisitesColSize);
    printf("\r\nthe result = %u\r\n", result);
    return 0;
}

/* 上面的思路会超时，下面有一种正确的解法 */
bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize){
    int inDegree[numCourses];
    for(int i = 0; i < numCourses; i++) {
        inDegree[i] = 0;
    }
    int result = numCourses;
    int continueFlg = 0;

    /* 统计每个课程依赖的课程数，即节点入度 */
    for(int i = 0; i < prerequisitesSize; i++) {
        inDegree[prerequisites[i][0]]++;
    }
    
    int *queue = (int *)malloc(numCourses * sizeof(int));
    int head = 0;
    int tail = 0;
    // 首先入队入度为 0 的结点
    for (int i = 0; i < numCourses; i++) {
        if (inDegree[i] == 0) {
            queue[tail] = i;
            tail++;
        }
    }
    
    while (head != tail) {
        for (int j = 0; j < prerequisitesSize; j++) {
            if (prerequisites[j][1] == queue[head]) {
                inDegree[prerequisites[j][0]]--;
                
                // 入队入度为 0 的结点
                if (inDegree[prerequisites[j][0]] == 0 ) {
                    queue[tail] = prerequisites[j][0];
                    tail++;
                }  
            }            
        }
        head++;
        result--;
    }

    return result == 0;
}

作者：fengup
链接：https://leetcode-cn.com/problems/course-schedule/solution/bao-li-bfs-by-fengup/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
