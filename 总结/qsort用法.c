// qsort 是不稳定的排序

#include <stdio.h>
#include <stdlib.h>

int CmpInt(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

// 对于float型的比较要使用 三元运算符，因为浮点数据相差很近时，相减会被认为是0
int CmpFloat(const void* a, const void* b)
{
	return *(float*)a > *(float*)b ? 1 : -1;
}

// 对字符串数组排序str[][]
int CmpStrArray(const void*a, const void* b)
{
	char* aa = (char*)a;
	char* bb = (char*)b;
	return strcmp(aa, bb);	
}

// 对字符串指针数组排序 *s[]
// 下面要强制转换成char** a 二维指针的原因是，要比较的数据是这个字符串数组中的成员，而不是这个数组本身，如果强转成char*,其实就是数组本身，比较是没有意义的，要强转成char**
// char** 表示指向字符串的指针, 然后再取值，就是字符串了，这个时候再比较就是正确的。
int CmpStrPointArray(const void* a, const void* b)
{
	char*aa = *(char**)a; // 注意如果要排序的是字符串指针数组的话，这里要先转换成*(char**)a
	char*bb = *(char**)b;
	
	return strcmp(aa, bb);
}

// int 型的二维指针排序
int CmpTwoLevelPoint(const void* a, const void* b)
{
	int* aa = *(int**)a; // 要比较的是一个二级指针，对二级指针再取值，就变成1维指针，指向一维数组。这里数组就2个元素。
	int* bb = *(int**)b;
	
	if (aa[0] == bb[0]) {
		return (aa[1] - bb[1]);
	} else {
		return (aa[0] - bb[0]);
	}
}

char 类型的3级指针的排序
tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]

int cmp(const void* a, const void* b)
{
    const char** aa = *(char***)a; // 注意这里的指针转换
    const char** bb = *(char***)b;
    int ret = strcmp(aa[0], bb[0]);
    if (ret == 0) {
        return strcmp(aa[1], bb[1]);
    }
    return ret;
}

char ** findItinerary(char *** tickets, int ticketsSize, int* ticketsColSize, int* returnSize){
    char **ret = (char**)malloc(sizeof(int) * (ticketsSize + 1));
    *returnSize = 0;
    *ticketsColSize = 3;
    qsort(tickets, ticketsSize, sizeof(tickets[0]), cmp);
    for (int i = 0; i < ticketsSize; i++) {
        printf("%s, %s\n", tickets[i][0], tickets[i][1]);
    }
    return ret;
}


/*
	qsort小结：
	该函数需要4个参数。
	参数1：要排序的内存指针
	参数2：需要排序的数据个数
	参数3：每个要排序的数据的大小
	参数4：排序的规则。
	在使用这个函数时，主要是把这4个参数确定好即可
*/

void main()
{
	int i;
	int test1[10] = {8,9,1,2,6,3,4,5,7,0};
	float test2[10] = {3.14, 5.0, 1.1, 0.9, 0.8, 3.15, 5.4, 1.6, 2.9, 3.8};
	char strArray[10][10] = {
		{"hwteg"},
		{"dfh"},
		{"qe"},
		{"hello"},
		{"world"},
		{"zh"},
		{"xfg"},
		{"cb"},
		{"th"},
		{"op"},
	};
	char *strPointArray[10] = { // 这里没有必要指定大小。
		"hwteg",
		"dfh",
		"qe",
		"hello",
		"world",
		"zh",
		"xfg",
		"cb",
		"th",
		"op",
	};
	int arr[5][2] = {
		{15,18},{1,5},{2,3},{2,4},{8,10},
	};
	int j;
	int** change = NULL; 
	int intervalsSize = (sizeof(arr) / sizeof(arr[0]));
	int intervalsColSize = sizeof(arr[0]) / sizeof(int);
	
	printf("\r\nint sort:\r\n");
	qsort(test1, sizeof(test1) / sizeof(test1[0]), sizeof(test1[0]), CmpInt);
	for (i = 0; i < 10; i++) {
		printf("%2d", test1[i]);
	}
	

	printf("\r\nfloat sort:\r\n");
	qsort(test2, sizeof(test2) / sizeof(test2[0]), sizeof(test2[0]), CmpFloat);
	for (i = 0; i < 10; i++) {
		printf("%4.2f ", test2[i]);
	}
	
	printf("\r\nstring array sort:\r\n");
	qsort(strArray, sizeof(strArray) / sizeof(strArray[0]), sizeof(strArray[0]), CmpStrArray);
	for (i = 0; i < 10; i++) {
		printf("%s  ", strArray[i]);
	}
	
	
	printf("\r\nstring point array sort:\r\n"); //  注意 strPointArray数组一定要定义和初始化大小为 sizeof(strPointArray) / sizeof(char*)。
	qsort(strPointArray, sizeof(strPointArray) / sizeof(char*), sizeof(char*), CmpStrPointArray);
	for (i = 0; i < 10; i++) {
		printf("%s  ", strPointArray[i]);
	}	
	
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
	printf("\r\ntwo level point sort:\r\n");
	qsort(change, intervalsSize, sizeof(change[0]), CmpTwoLevelPoint);
	for (i = 0; i < intervalsSize; i++) {
		printf("(%2d %2d), ", change[i][0], change[i][1]);
	}
}
