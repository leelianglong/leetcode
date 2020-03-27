/*
 * m=1, n=3
 * 135,138 (漫游限制前缀)
 * 189000 （区域列表）
 * 188000
 * 178000
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "securec.h"

#define MAXM 1000
#define MAXN 1000
#define BUF_LEN 16

int cmp(const void* a, const void* b)
{
    const char*aa = (char*)a;
    const char*bb = (char*)b;
    int length = strlen(aa);
    int i;
    for (i = 0; i < length; i++) {
        if (aa[i] == bb[i]) {
            continue;
        }
        return bb[i] - aa[i];
    }
}

typedef struct {
    char start[BUF_LEN];
    char end[BUFSIZ];
} LimitedStruct;

int GetRoamArea(char *limited[][2], int m, 
                char *area[], int n, 
                char outBuf[MAXN][BUF_LEN])
{
    int i;
    LimitedStruct* saveLimited = (LimitedStruct*) malloc(sizeof(LimitedStruct) * m);
    memset_s(saveLimited, sizeof(LimitedStruct) * m, 0, sizeof(LimitedStruct) * m);

    for (i = 0; i < m; i++) { // 限制列表
        (void)printf("limited: %s %s\n", limited[i][0], limited[i][1]);
        (void)memcpy_s(saveLimited[i].start, BUF_LEN, limited[i][0], strlen(limited[i][0]));
        (void)memcpy_s(saveLimited[i].end, BUF_LEN, limited[i][1], strlen(limited[i][0]));
    }

    int j;
    int counter = 0;
    for (i = 0; i < n; i++) { // 区域列表
        (void)printf("area: %s\n", area[i]);
        for (j = 0; j < m; j++) {
            if (memcmp(area[i], saveLimited[j].start, strlen(saveLimited[j].start)) < 0) {
                (void)memcpy_s(outBuf[counter++], BUF_LEN, area[i], strlen(area[i]));
            }
            if (memcmp(area[i], saveLimited[j].end, strlen(saveLimited[j].end)) > 0) {
                (void)memcpy_s(outBuf[counter++], BUF_LEN, area[i], strlen(area[i]));
            }
        }
    }
    
    qsort(area, counter, sizeof(char*), cmp);

    return counter;
}



int main(void)
{
    char* test[3] = {"18800","18700", "18900"};
    qsort(test, 3, sizeof(char*), cmp);
    int rt;
    for (rt = 0; rt < 3; rt++) {
        printf("%s\r\n", test[rt]);
    }
    return 1;

    int m, n;
    if (scanf_s("%d %d", &m, &n) != 2) { return -1; }

    static char limitedBuf[MAXM][2][BUF_LEN];
    static char *limited[MAXN][2];
    int i;
    for (i = 0; i < m; i++) {
        if (scanf_s("%s %s", 
                    limitedBuf[i][0], BUF_LEN, 
                    limitedBuf[i][1], BUF_LEN) != 2) {
            return -1;
        }
        limited[i][0] = limitedBuf[i][0]; // 第 i 个限制区域的start
        limited[i][1] = limitedBuf[i][1]; // 第 i 个限制区域的end
    }
    static char areaBuf[MAXN][BUF_LEN];
    static char *area[MAXN];   // 下面是区域列表
    for (i = 0; i < n; i++) {
        if (scanf_s("%s", areaBuf[i], BUF_LEN) != 1) {
            return -1;
        }
        area[i] = areaBuf[i];
    }

    static char outBuf[MAXN][BUF_LEN];
    int ret = GetRoamArea(limited, m, area, n, outBuf);
    for (i = 0; i < ret; i++) {
        (void)printf("%s\n", outBuf[i]);
    }

    return 0;
}

