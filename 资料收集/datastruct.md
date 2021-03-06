# 2	常用数据结构
## 2.1 线性表
```
一个线性表是n个具有相同特性的数据元素的有限序列。线性表中数据元素之间的关系是一对一的关系，即除了第一个和最后一个数据元素之外，其它数据元素都是首尾相接的（部分链表除外）。
线性表主要由顺序表示或链式表示。在实际应用中，常以栈、队列、字符串、链表等特殊形式使用。

```
### 2.1.1 数组
```
顺序表是在计算机内存中以数组的形式保存的线性表，是指用一组地址连续的存储单元依次存储数据元素的线性结构
a) 二分搜索算法
二分搜索是一种在有序数组中查找某一特定元素的搜索算法。搜索过程从数组的中间元素开始，如果中间元素正好是要查找的元素，则搜索过程结束；如果某一特定元素大于或者小于中间元素，则在数组大于或小于中间元素的那一半中查找，而且跟开始一样从中间元素开始比较。如果在某一步骤数组为空，则代表找不到。这种搜索算法每一次比较都使搜索范围缩小一半。二分搜索在情况下的复杂度是对数时间，进行O(log n)次比较操作。
二分搜索有许多中变种。比如分散层叠可以提升在多个数组中对同一个数值的搜索。分散层叠有效的解决了计算几何学和其他领域的许多搜索问题。指数搜索将二分搜索拓宽到无边界的列表。二分搜索树和B树数据结构就是基于二分搜索的。
```
```
int Method(int[] nums, int low, int high, int target) {
            while (low <= high) {
                int middle = low + (high – low) / 2;	// 这里不用(high+low)/2是为了防止溢出
                if (target == nums[middle]) {
                    return middle;
                }
                else if (target > nums[middle]) {
                    low = middle + 1;
                }
                else if (target < nums[middle]) {
                    high = middle - 1;
                }
            }
            return -1;
        }

```
### 2.1.2 数组的使用
a、二级指针的内存分配
```
    int** test1 = (int**) malloc(4 * sizeof(int));
    for (int i = 0; i < 4; i++) {
        *(test1 + i) = (int*)malloc(2 * sizeof(int));
    }
    for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 2; k++) {
            *(*(test1 + j) + k) = j * k;
        }
    }
```
这里注意，在分配内存时，要写成这种指针形式*(test1 + i) = (int*)malloc(2 * sizeof(int));如果写成*test1[i] 就是错误了 
b、在作为函数参数时，二维数组可以用二级指针来表示
```
void printf_my(int testArr1[4][2])
{
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            printf("%4d", *(*(testArr1 + i) + j));
        }
    }
}
```
但是该函数在倍调用是还是需要传递数组进来。

c、数组和指针的等价关系（仅限二维）
int a[5][3]    ------->    int(*p)[5]
int *a[5]      ------->    int** p

# 3、典型算法举例
## 3.1、滑动窗口
```
滑动窗口就是在少数问题中将嵌套for循环变成单层for循环，降低时间复杂度。
```
```
经典问题：给定长度为n的数组，计算长度为k的子数组的最大和。
* 我们使用线性循环计算n个项中前k个元素的总和，并将总和存储在变量window_sum中
* 然后，我们将在阵列上线性滑动直至达到最终并同时追踪最大和
* 要获得k个元素块的当前总和，只需从前一个块中减去第一个元素并添加当前块的最后一个元素即可。 下面的表示将清楚说明窗口如何在阵列上滑动
```
```
int maxSum(int arr[], int n, int k)
{
    if (n < k)
    {
        printf("Invaild");
        return -1;
    }
    int max_sum = 0;
    for (int i=0; i<k; i++)
    {
        max_sum += arr[i];
    }
    int windows_sum = max_sum;
    for (int i=k; i<n; i++)
    {
        windows_sum += arr[i] - arr[i - k];
        max_sum = max(max_sum, windows_sum);
    }
    return max_sum;
}
```
```
经典问题：求一个字符串不重复的子串的最大的长度：
例如:  abcabcbb, the answer is "abc", which the length is 3
```
```

```

# 常识
1） 如果要使用递归，那么首先要写递归的结束条件
