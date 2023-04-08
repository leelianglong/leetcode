1. leetcode平台上 sizeof(int) 和 sizeof(int*) 大小是不一样的。前者是4 后者是 8；所以在进行二级指针分配内存时，第一次，要使用sizeof(int*)
```
int** res = (int**)malloc(sizeof(int*) * num); // 这里一定是 sizeof(int*)
一般*returnSize 就是要返回的二维数组的行数；
**returnColSize 表示要返回的二维数组的每一行的元素个数。
对此，一般首先会把*returnSize = 0;
*returnColSize = (int*)malloc(sizeof(int) * num);  // 这里分配内存的时候，只要使用sizeof(int) 即可
```
2. 要使用UT_hash，只要确定下key之后，关于data，如果有多个，可以直接写到hash结构里面，也可以搞个结构体，先写在一起，再放到hash结构里。
```
struct HashObj {
    int key;
    int a1;
    int a2;
    ...
    UT_hash_handle hh;
}; 以及下面这种写法

typedef struct {
    int a1;
    int a2;
} VAL;
struct HashObj {
    int key;
    VAL val;
    UT_hash_handle hh;
};
```


4. 对于入参是二维指针时，对入参的判断使用下面的几个条件就够
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

4. 在LeetCode中要使用全局变量的话，可以先定义，但是不要初始化，在使用的主函数中初始化成0, 这样就能避免多次用例执行时的相互影响。另外，全局变量的命名不要和函数参数命名一样。

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

16. 计算数组上连续k个数的和的最大值的最佳实践。 注意这里两个指针都是从0开始的。
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

18. 一维重叠判断和二维重叠的判断
```
剑指 Offer II 058. 日程表 关键代码如下：
bool valid(int tarS, int tarE, int srcS, int srcE)
{
    if (srcS <= tarS && srcE > tarS) {
        return false;
    }
    if (tarE > srcS && tarE < srcE) {
        return false;
    }
    if (tarS <= srcS && tarE >= srcE) {
        return false;
    }
    return true;
}
二维重叠区域的去重，考试中遇到，要注意画图来判断

```
19. dfs和回溯的差异，什么时候用回溯，什么时候用dfs？
```
回溯是要遍历所有情况，在所有情况的基础上，选择结果。例如题目1102，得分最高的路径，要使用深度优先搜索，找到1条路上最小的值。然后在回溯回来，遍历所有的路径，找到所有路径上的最大值。
```


21. 一般自定义变量用来计算字符串的长度，不能在for循环中计算字符串长度
```
#define CNT 26
int minSteps(char * s, char * t){
    int map1[CNT] = {0};
    int st1 = strlen(s); // 这里计算一次
    for (int i = 0; i < st1; i++) {
        map1[s[i] - 'a']++;
    }
    int st2 = strlen(t);// 这里计算一次
    for (int i = 0; i < st2; i++) {
        map1[t[i] - 'a']--;
    }
    
    int steps = 0;
    for (int i = 0; i < CNT; i++) {
        steps += abs(map1[i]);
    }
    return steps;
}
这种写法就超时了
#define CNT 26
int minSteps(char * s, char * t){
    int map1[CNT] = {0};
    for (int i = 0; i < strlen(s); i++) { // 这里每次循环都会计算一次strlen.
        map1[s[i] - 'a']++;
    }
    
    for (int i = 0; i < strlen(t); i++) {
        map1[t[i] - 'a']--;
    }
    
    int steps = 0;
    for (int i = 0; i < CNT; i++) {
        steps += abs(map1[i]);
    }
    return steps;
}
```

22. 安全函数与非安全函数对别
```
sprintf_s(buff, length, "格式", "内容"）     ----> sprintf(buff, "格式"， "内容")
```

23. 内存分配注意事项

```
对于 int** res = (int**)calloc(cnt, sizeof(int*)); 这个表示已分配cnt个存储int* 指针的内存空间给res.
在对于二级指针分配内存时，如果 res[i] = (int*)calloc(len, sizeof(int)); 中的i > cnt,那么就是内存访问错误问题了。
```

24. UT_hash 当作链表使用,在于一些需要动态插入，删除，查询的题目，存储数据的数据结构应该考虑使用链表。参考题目 731 ，732的解答

25. 对于兑零钱的题目，可以这样来设计数据结构，最佳实际如下
---
```
int notes[4] = {10,20,50,100}; //这个数组设置面值
int count[4] = {0,1,2,0}; // 这个设置面值对应的张数
int total = 660; // 要换的前 （优先使用最大面值的）
for (int i = 3; i >= 0; i--) {
    if (total > notes[i] && count[i] >0 ) {
        int tmpCnt = total / notes[i] > count[i] ? count[i] : total / notes[i];
        res[i] = tmpCnt; // 存储张数
        total -= tmpCnt * notes[i];
    }
}
if (total == 0) {
    // 判断是否兑换成功
}
```

26. 找数据之间的关系，巧妙应用UT_hash 解决 leetcode 1396 地铁设计系统。
---
```
1. 设计一个hash表存储进站数据，key=ID, val(站名，进站时间)，再设计一个hash表存储出站数据，key=(进站名-出站名的字符串)， val(总人数， 总时间)。
2. 进站时保存相关信息，出站时，先在基于ID，找到进站名，然后在把出站名组装成 第二个hash表的key, 在hash表中添加或查找
3. 最终出站hash表中存储的信息，就能够帮忙我们计算 从 A - B站的平均时间。 用总时间/总人数
```
27. 简单的两两交换不要写错了
```
void swap(int a, int b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

28. 要注意大量的内存分配和初始化也是比较耗时的。对于要存储很多返回结果的题目，最好按需分配内存，不能一次在开始全部分配完成。
```
    res = (int*)calloc(CNT, sizeof(int*));
    for (int i = 0; i < CNT; i++) {
        res[i] = (int*)calloc(HIGH, sizeof(int));
    }
```
应该像下面，在需要的时候分配
```
    if (curSum == g_target && root->left == NULL && root->right == NULL) {
        res[g_returnSize] = (int*)calloc(cnt, sizeof(int));
        memcpy(res[g_returnSize], tmpSave, sizeof(int) * cnt);
        columnSizes[g_returnSize] = cnt;
        g_returnSize++;
        return;
    }
```

29. 二叉树的序列化：要求二叉树上重复的子树 652
```
如何在二叉树上找重复的子树，关键要把二叉树序列化后，即把二叉树转成字符串，这样根据hash就能够找到是否有重复的字符，进而判断是否有重复的子树。参考题解652
```

30. 图的序列化： 不同岛屿的数量694
```
如何求不同岛屿的数量？ 我们把遍历岛屿的顺序使用数字1,2，3,4来代替，如果是相同的岛屿，那么他们遍历的顺序是一样的，如果把1,2,3,4 转成字符串，那么就可以使用hash来判断是否重复，进而可以
计算不同的岛屿数量。

```
32. 思路转变的例子
```
1. 题目1151. 有个序列只有0,1，要求把所有的1连接在一起，使用的最小交换次数。这个题目要想到滑动窗口上来。大概的思路就是先计算出所有的1的个数，以这个长度为滑窗，
然后计算这个滑窗中1的最大数量，然后使用总共的1的数量减去这个最大值就是结果。暴力容易超时，在计算1的时候，直接把所有数加起来即可，因为只有0,1.还有在滑窗上计算1
的个数时，也是吧右边的数据加进来，把左边的数据减去，即可。
```

31. ascii码中可显示的第一个字符是空格' ', 在字符串题目中使用map时注意。

32. sprintf 这种函数的打印格式 "%02d" 表示右对齐，打印位宽是2位，如果不够2位，则左边补0.  注意一些特殊打印场合的使用
33. 在题目中使用全局变量后，切记不能在函数参数中，再使用同名的参数。 这样会导致这个全局变量不其作用，它里面根本不能保存你在函数中对这个形参的任何操作。
34. 对于换行符\n 制表符 \t 这种是一个字符， 不要当成2个字符。
35. 对于二维数组的插入操作，我们可以之间转换成1维数组的赋值。实例代码如下
```
void MoveBack(int** people, int start, int end)
{
    for (int i = end; i > start; i--) {
        people[i] = people[i-1]; // 这里就是一维数组的直接赋值操作
    }
}
```
当我们需要在一个二维数组中插入一个元素时，可以先找到要插入的位置pos，使用一个临时变量保存下要插入的数值，然后把二维数组中，从POS到结束位置都向后移动一个位置，然后把要插入的数值放进来，实例代码如下
```
for (int i = 0; i < peopleSize; i++) {
    int pos = people[i][1];
    int* tmp = people[i];// 这里不能是people[pos]....
    MoveBack(people, pos, i);
    people[pos] = tmp;
}
```
36. 注意memset用来初始化内存时只能用来初始化成0，如果需要初始化成其他值，则需要通过for循环来逐个遍历数组成员来初始化。例如代码：int rate[10]; memset(rate, 1, sizeof(rate)); 这个与预期的rate[0] = 1,是不一样的。 memset或者memcpy这些都是按照字节来初始化和拷贝的，对于int型变量占据4个字节。这里相当于是吧4个byte的位置上都初始化成1了。
