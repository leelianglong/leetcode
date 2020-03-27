1、leetcode平台上 sizeof(int) 和 sizeof(int*) 大小是不一样的。前者是4 后者是 8；所以在进行二级指针分配内存时，第一次，要使用sizeof(int*)
```
int** res = (int**)malloc(sizeof(int*) * num); // 这里一定是 sizeof(int*)
```

2、对于入参是二维指针时，对入参的判断使用下面的几个条件就够
```
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int i;
    int **result = NULL;
    
    if (intervals == NULL || intervalsSize == 0 || intervalsColSize == NULL) {
        *returnSize = 0;
        return intervals;
    }
}
```
不要使用*intervalsColSize，有可能报越界
在后续计算的过程中，要使用*returnSize = 0;要先对其初始化。
返回二维指针时，一定要制定要返回的行数，以及每行的列数。

3、有时候会发现，单独执行用例可以通过，但是提交后不能通过的情况发生，这里主要是使用了全局变量。系统在执行多个用例时，这个全局变量中的值相互影响了。

