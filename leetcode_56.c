/*
下面的解法存在问题只有部分用例能过
关注一下qsort排序写法
*/

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
    if (intervals == NULL || intervalsSize == 0 || intervalsColSize == NULL) {
        *returnSize = 0;
        return intervals;
    }

    int i;
    int pos = 0;
    CmbStruct* tmpSave;
    int** res;
    
    *returnSize = 0;
    tmpSave = (CmbStruct*)malloc(sizeof(CmbStruct) * intervalsSize);
    memset(tmpSave, 0, sizeof(CmbStruct) * intervalsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * intervalsSize);
    printf("\r\nbefore sort\r\n");
    for(i = 0; i < intervalsSize; i++) {
		tmpSave[i].start = intervals[i][0];
		tmpSave[i].end   = intervals[i][1];
        printf("%2d %2d\r\n", tmpSave[i].start, tmpSave[i].end);
    }

    if (intervalsSize == 1) {
        *returnSize = 1;
        (*returnColumnSizes)[0] = 2;
        return intervals;
    }

    qsort(tmpSave, intervalsSize, sizeof(CmbStruct), cmp);

    printf("\r\nafter sort\r\n");
    for(i = 0; i < intervalsSize; i++) {
		printf("%2d %2d\r\n", tmpSave[i].start, tmpSave[i].end);
    }

    for (i = 1; i < intervalsSize; i++) {
        (*returnColumnSizes)[pos] = 2;
		if (tmpSave[pos].end >= tmpSave[i].start) {
            //(*returnColumnSizes)[pos] = 2;
			tmpSave[pos].end = MAX_ELEMENT(tmpSave[pos].end, tmpSave[i].end);
		} else {
			tmpSave[++pos] = tmpSave[i];
            //(*returnColumnSizes)[pos] = 2;
		}
    }
    (*returnColumnSizes)[pos] = 2;
    printf("%d %d", pos, intervalsSize);
    if (pos == 0) {
       *returnSize = 1; 
    } else {
        *returnSize = (intervalsSize - pos + 1);
    }
    for (i = pos + 1; i < intervalsSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    
	res = (int**)malloc(sizeof(int*) * (*returnSize));
	for (i = 0; i < (*returnSize); i++) {
		res[i] = (int*)malloc(sizeof(int) * 2);
	}
	for (i = 0; i < (*returnSize); i++) {
		res[i][0] = tmpSave[i].start;
		res[i][1] = tmpSave[i].end;
	}
    return res;
}
