/*
* 目前还有问题
*/

int fixColum = 0;
int fixRow = 0;
int* queue = NULL;
int* visited = NULL;
int direct[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};

int bfs(int** grid, int row, int colum)
{
    int front = 0;
    int rear = 0;
    queue[rear++] = row * fixColum + colum;
    visited[row * fixColum + colum] = true;
    int step = 0;
    while (front != rear) {
        int curSize = rear - front;
        printf("\nsize(%d)", curSize);
        for (int i = 0; i < curSize; i++) {
            int curNode = queue[front++];
            int curRow = curNode / fixColum;
            int curColum = curRow % fixColum;
            printf("\nout(%d %d)", curRow, curColum);
            for (int k = 0; k < 4; k++) {
                int dx = curRow + direct[k][0];
                int dy = curColum + direct[k][1];
                if (dx < 0 || dx >fixRow - 1 || dy < 0 || dy > fixColum - 1) {
                    continue;
                }
                if (grid[dx][dy] == 1 && !visited[dx * fixColum + dy]) {
                    printf("\ninput %d %d", dx, dy);
                    grid[dx][dy] = 2;
                    queue[rear++] = dx * fixColum + dy;
                    visited[dx*fixColum + dy] = true;
                }
            }
        }
        step++;
        printf("\nstep=%d", step);
    }
    return step;
}

int orangesRotting(int** grid, int gridSize, int* gridColSize){

    int max = gridSize * (*gridColSize);
    int time;
    fixColum = *gridColSize;
    fixRow = gridSize;

    queue = (int*)malloc(sizeof(int) * (max + 1));
    memset(queue, 0, sizeof(int) * (max + 1));
    visited = (int*)malloc(sizeof(int) * (max + 1));
    memset(visited, 0, sizeof(int) * (max + 1));
    bool flg = false;
    int i;
    int j;

    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < (*gridColSize); j++) {
            if (grid[i][j] == 2) {
                // 有腐烂的橘子了。
                printf("\nenter (%d %d)", i, j);
                flg = true;
                break;
            }
        }
        if (flg) {
            time = bfs(grid, i, j);
            break;
        }
    }

    for (i = 0; i < fixRow; i++) {
        for (j = 0; j < fixColum; j++) {
            printf("(%d %d)=%d", i,j,grid[i][j]);
            if (grid[i][j] == 1) {
               // return -1;
            }
        }
        printf("\n");
    }
    return time;
}
