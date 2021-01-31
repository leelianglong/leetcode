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
    returnSize = 0; // 这个一定要放在前面。
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

4. 在LeetCode中要使用全局变量的话，可以先定义，但是不要初始化，在使用的主函数中初始化成0

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
