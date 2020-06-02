/*
下面的解法存在问题只有部分用例能过
关注一下qsort排序写法
*/

#include <stdio.h>
#include <stdlib.h>
#if 0
#define MAX_ELEMENT(a, b)  ((a) > (b) ? (a) : (b))
typedef struct {
	int start;
	int end;
} CmbStruct;

int cmp(const void* a, const void* b)
{
	CmbStruct* tmpa = (CmbStruct*)a;
	CmbStruct* tmpb = (CmbStruct*)b;
	return tmpa->start - tmpb->start;	
}


int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int i;
    int pos = 0;
    CmbStruct* tmpSave;
    int** res;
    
    tmpSave = (CmbStruct*)malloc(sizeof(CmbStruct) * intervalsSize);
    memset(tmpSave, 0, sizeof(CmbStruct) * intervalsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * intervalsSize);
    
    printf("\r\nbefore sort\r\n");
    for(i = 0; i < intervalsSize; i++) {
		tmpSave[i].start = intervals[i][0];
		tmpSave[i].end   = intervals[i][1];
		printf("%2d %2d\r\n", tmpSave[i].start, tmpSave[i].end);
    }
  
    qsort(tmpSave, intervalsSize, sizeof(CmbStruct), cmp);
    
    printf("\r\nafter sort\r\n");
    for(i = 0; i < intervalsSize; i++) {
		printf("%2d %2d\r\n", tmpSave[i].start, tmpSave[i].end);
    }
    
    for (i = 1; i < intervalsSize; i++) {
    	(*returnColumnSizes)[pos] = 2;
		if (tmpSave[pos].end >= tmpSave[i].start) {
			tmpSave[pos].end = MAX_ELEMENT(tmpSave[pos].end, tmpSave[i].end);
		} else {
			tmpSave[++pos] = tmpSave[i];
		}
    }
    printf("\r\npos=%d intervalsSize = %d\r\n", pos, intervalsSize);
    *returnSize = (pos + 1);
    (*returnColumnSizes)[pos + 1] = 2;
    
	res = (int**)malloc(sizeof(int*) * (pos + 1));
	for (i = 0; i < (pos + 1); i++) {
		res[i] = (int*)malloc(sizeof(int) * 2);
	}
	for (i = 0; i < (pos + 1); i++) {
		res[i][0] = tmpSave[i].start;
		res[i][1] = tmpSave[i].end;
	}
	
    return res; 
}
#endif 

#define MAX_NUM     1000
static int g_hash[MAX_NUM][2] = {0};
static int g_hashCnt = 0;

static void HashAdd(int a, int b)
{
	int i;
	
	if (g_hashCnt == 0) {
		g_hash[0][0] = a;
		g_hash[0][1] = b;
		g_hashCnt++;
		return;
	}
	
	if (g_hash[g_hashCnt - 1][0] == a) {
		if (b > g_hash[g_hashCnt - 1][1]) { // 如果添加的区间的右区间比现在hash表中的右区间还大，则更新当前hash右区间。
			g_hash[g_hashCnt - 1][1] = b;
		}
		return;
	} else {
		if (a <= g_hash[g_hashCnt - 1][1]) { // 新来的值比hash表最后一个区间的右边界小，说明有可能在目前hash表的范围内。再比较新值得右边界是否大于 hash表的右边界。如果也大的话就更新当前的hash表范围，不用添加一个新的区间到hash表。
			if (g_hash[g_hashCnt - 1][1] < b) {
				g_hash[g_hashCnt - 1][1] = b;
			} 
			return;
		}
	}// 除过上面2种情况，就直接新增到hash表中。
	g_hash[g_hashCnt][0] = a;
	g_hash[g_hashCnt][1] = b;
	g_hashCnt++;
}

static void ResetHash(void)
{
	g_hashCnt = 0;
}

static int cmp(const void* a, const void* b)
{
	int* aa = *(int**)a; // 要比较的是一个二级指针，对二级指针再取值，就变成1维指针，指向一维数组。这里数组就2个元素。
	int* bb = *(int**)b;
	
	if (aa[0] == bb[0]) {
		return (aa[1] - bb[1]);
	} else {
		return (aa[0] - bb[0]);
	}
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes)
{
	int i;
    int **result = NULL;
    
    if (intervals == NULL || intervalsSize == 0 || intervalsColSize == NULL) {
        *returnSize = 0;
        return intervals;
    }
    ResetHash();
    printf("\r\nbefor sort\r\n");
    for (i = 0; i < intervalsSize; i++) {
		printf("\r\n%2d %2d\r\n", intervals[i][0], intervals[i][1]);
    }
    printf("\r\nsizeof=%d\r\n", sizeof(intervals[0]));
    qsort(intervals, intervalsSize, sizeof(intervals[0]), cmp);
    
    printf("\r\nafter sort\r\n");
    for (i = 0; i < intervalsSize; i++) {
		printf("\r\n%2d %2d\r\n", intervals[i][0], intervals[i][1]);
    }
    for (i = 0; i < intervalsSize; i++) {
		HashAdd(intervals[i][0], intervals[i][1]);
    }
    
    for (i = 0; i < g_hashCnt; i++) {
		intervals[i][0] = g_hash[i][0];
		intervals[i][1] = g_hash[i][1];
    }
    
    *returnSize = g_hashCnt;
    *returnColumnSizes = intervalsColSize;
    printf("\r\nhash_cnt=%d\r\n", g_hashCnt);
    return intervals;
}

int main(void)
{
	int arr[4][2] = {
		{15,18},{1,3},{2,3},{8,10},
	};
	int i;
	int j;
	int** change = NULL; 
	int** result = NULL;
	int returnSize = 0;
	int intervalsSize = (sizeof(arr) / sizeof(arr[0]));
	int intervalsColSize = sizeof(arr[0]) / sizeof(int);
	int* returnColumnSizes[100] = {NULL};
	
	change = (int**) malloc(sizeof(int*) * intervalsSize);
	for (i = 0; i < intervalsSize; i++) {
		change[i] = (int*)malloc(sizeof(int) * 2);
		memset(change[i], 0, sizeof(int) * 2);
	}
	for (i = 0; i < intervalsSize; i++) {
		for (j = 0; j < intervalsColSize; j++) {
			change[i][j] = arr[i][j];
		}
	}
	
	result = merge(change, intervalsSize, &intervalsColSize, &returnSize, returnColumnSizes);
	printf("\r\nthe result:\r\n");
	for (i = 0; i < returnSize; i++) {
		printf("%2d %2d", result[i][0], result[i][1]);
	}
	return 0;
}
