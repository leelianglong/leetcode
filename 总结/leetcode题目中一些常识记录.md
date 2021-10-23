1. leetcode平台上 sizeof(int) 和 sizeof(int*) 大小是不一样的。前者是4 后者是 8；所以在进行二级指针分配内存时，第一次，要使用sizeof(int*)
```
int** res = (int**)malloc(sizeof(int*) * num); // 这里一定是 sizeof(int*)
一般*returnSize 就是要返回的二维数组的行数；
**returnColSize 表示要返回的二维数组的每一行的元素个数。
对此，一般首先会把*returnSize = 0;
*returnColSize = (int*)malloc(sizeof(int) * num);  // 这里分配内存的时候，只要使用sizeof(int) 即可
```

2. 对于入参是二维指针时，对入参的判断使用下面的几个条件就够
```
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
    int i;
    int **result = NULL;
    *returnSize = 0; // 这个一定要放在前面。
    if (intervals == NULL || intervalsSize == 0 || intervalsColSize[0] == 0) {
        return intervals;
    }
}
不要使用*intervalsColSize，有可能报越界
在后续计算的过程中，要使用*returnSize = 0;要先对其初始化。
返回二维指针时，一定要制定要返回的行数，以及每行的列数。
```

3. 有时候会发现，单独执行用例可以通过，但是提交后不能通过的情况发生，这里主要是使用了全局变量。系统在执行多个用例时，这个全局变量中的值相互影响了。
在DFS相关的题目中，把需要记录的数据都使用指针的形式放在函数参数中，不要定义成全局变量，否则会导致有些用例不过.

4. 在LeetCode中要使用全局变量的话，可以先定义，但是不要初始化，在使用的主函数中初始化成0, 这样就能避免多次用例执行时的相互影响。

另外，全局变量的命名不要和函数参数命名一样。


5. 返回空字符串的方法：
```
char* result = (char*)malloc(sizeof(char) * 100);

result[0] = '\0';

return result; // 这样就返回空字符串

对于返回字符串时，一定要在结尾处赋值'\0'
```
6.  二分查找类以及2数之和的移动过程，应该把相等的条件放在前面，然后每个else if 分支里面明确做一件事。把所有的情况都用elseif分支确定下来。


7. malloc返回的是一段内存的地址，这段内存，你准备存储什么类型，那么在分配时，就要使用 type* buf = (type*)malloc(sizeof(type) * size); 例如你打算存储的是 结构体指针，那么就要使用 type** buf = (type**)malloc(sizeof(type*) * size); malloc分配的内存可以存储任意类型的数据


8. 1e9 类似这种类型的值不能作为数组下标。例如 int buf[1e7] 会报错

9. 参数宏，define(a,b)  直接这样写即可，不要写成 define((a), (b))  这种形式。 在它要替代的表达式中需要使用括号来把参数括起来。

10. 变量一定要按需初始化，例如在双指针或者二分查找题目中，要把left  和 right 初始化成确定的值，不能不初始化，否则在跑多个用例时会失败。
 
11. sprintf(buf, format, content) 这个函数默认会在结束的地方添加字符串的结尾符。

12. 数组元素去重的一般算法
```
把数组元素排序 qsort()  
for (int i = 0; i < size; i++) {
    if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
    }
}
```
13. 三维指针的用
对于需要返回3级指针的函数，在最初先分配一个3级指针，例如
int*** res = (int***)malloc(sizeof(int**) * 10000);

接口中的*returnSize表示该3维指针中二维部分有多少个。

对于二维部分，先临时申请一个二维指针，用来存储在计算的过程中的临时的数据。 int** save = (int**)malloc(sizeof(int*) * COUNT);

在最终返回的结果的地方，再把这个临时的二维指针赋给res, 如下：

res[*returnSize] = (int**)malloc(sizeof(int*) * COUNT); res本身是3级指针，res[*returnSize] 就变成二维的了，

根据二维指针的个数，这里可以直接把临时的二维指针赋值给res, 完整的代码如下：

```
void dfs(char* s, char*** res, int* returnSize, char** save, int count, int** returnColumnSizes, int startIdx)
{
    if (startIdx == strlen(s)) {
        res[*returnSize] = (char**)malloc(sizeof(char*) * count);
        (*returnColumnSizes)[*returnSize] = count;
        for (int i = 0; i < count; i++) {
            res[*returnSize][i] = (char*)malloc(sizeof(char) * (strlen(save[i]) + 1));
            memset(res[*returnSize][i], 0, sizeof(char) * (strlen(save[i]) + 1));
            strncpy(res[*returnSize][i], save[i], strlen(save[i]));
        }
        (*returnSize)++;
        return;
    }
    for (int i = startIdx; i < strlen(s); i++) {
        if (!IsValid(s, startIdx, i)) {
            continue;
        }
        strncpy(save[count], &s[startIdx], i - startIdx + 1);
        count++;
        printf("\n enter");
        dfs(s, res, returnSize, save, count, returnColumnSizes, i + 1);
        memset(save[count], 0, strlen(save[count]));
        printf("\n back i=%d, count=%d", i,count);
        count--;
    }
}
#define COUNT 150000
char *** partition(char * s, int* returnSize, int** returnColumnSizes){
    char*** res = (char***)malloc(sizeof(char**) * COUNT);
    *returnSize = 0;
    *returnColumnSizes = (int*)malloc(sizeof(int) * COUNT);
    memset(*returnColumnSizes, 0, sizeof(int) * COUNT);

    char** save = (char**)malloc(sizeof(char*) * COUNT);
    for (int i = 0; i < COUNT; i++) {
        save[i] = (char*)malloc(sizeof(char) * strlen(s) + 1);
        memset(save[i], 0, sizeof(char) * strlen(s) + 1);
    }
    int count = 0;
    dfs(s, res, returnSize, save, count, returnColumnSizes, 0);
    return res;
}
```

```
三级指针的应用：
int ***res = (int ***)malloc(sizeof(int**) * CNT);
这里 res是三级指针，那么res[i] 就是二级指针。
res[i] = (int**)malloc(sizeof(int*) * CNT);
res[i][j] 就是一维指针。
res[i][j] = (int*)malloc(sizeof(int) * CNT);

```

13. 关于变量的定义需要注意，像下面的2段代码对应定义的变量含义是不一样的。
```
for (int i = 1; i < heightSize - 1; i++) {
    int maxLeft = 0;
    int maxRight = 0;
    for (int j = i; j >= 0; j--) {
        maxLeft = MAX(maxLeft, height[j]);
    }
    for (int k = i; k < heightSize; k++) {
        maxRight = MAX(maxRight, height[k]);
    }
    printf("%d,", MIN(maxRight, maxLeft) - height[i]);
    res += MIN(maxRight, maxLeft) - height[i];
}
```

和下面的代码片段
```
int maxLeft = 0;
int maxRight = 0;
for (int i = 1; i < heightSize - 1; i++) {
    for (int j = i; j >= 0; j--) {
        maxLeft = MAX(maxLeft, height[j]);
    }
    for (int k = i; k < heightSize; k++) {
        maxRight = MAX(maxRight, height[k]);
    }
    printf("%d,", MIN(maxRight, maxLeft) - height[i]);
    res += MIN(maxRight, maxLeft) - height[i];
}
```
第一种，maxRight,maxLeft这2个变量定义在for循环的里面，每次执行for循环的时候，这2个值都是重新被定义的，相当于是局部变量了。后面这种，在for循环的外面定义一次，后面for循环中改变了这2个值后，
下次执行for循环的时候，就是基于变化后的值。

15. 如果暂存的类型是 long* 的，但是返回的值需要的是int, 那么一定要把这个long类型的转换成 int 之后，再返回，否则有问题。例如，暂存的数据存储在 res， 但是它是long 的，返回的值需要int，所以下面需要类型转换一下。
```
int* splitIntoFibonacci(char * S, int* returnSize){
    long* res = (long*)malloc(sizeof(long) * RET_COUNT);
    memset(res, 0, sizeof(long) * RET_COUNT);
    gLength = strlen(S);
    *returnSize = 0;
    bool result = dfs(S, res, returnSize, 0);
    *returnSize = result ? *returnSize : 0;
    
    int* resultBuf = (int*)malloc(sizeof(int) * *returnSize);
    for (int i = 0; i < *returnSize; i++) {
        resultBuf[i] = res[i];
    }
    return resultBuf;
}
```

16. 计算数组上连续k个数的和的最大值的最佳实践
```
    int extra = 0;
    int cur = 0;
    for (left = 0, right = 0; right < customersSize; right++) {
        cur += customers[right];
        if (right - left + 1 > k) {
            cur -= customers[left];
            left++;
        }
        extra = MAX(extra, cur);
    }
```

17. 数组上固定窗口最小值的最佳实践
```
    int min = INT_MAX;
    int cur = 0;
    for (int i = 0, j = 0; j < cardPointsSize; j++) {
        cur += cardPoints[j];
        if (j - i + 1 >= cardPointsSize - k) {
            min = MIN(min, cur);
            cur -= cardPoints[i++];
        }
    }
```
注意这里的 >= 和上面的最大值是不一样的。



