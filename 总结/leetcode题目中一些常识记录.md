sleetcode平台上 sizeof(int) 和 sizeof(int) 大小是不一样的。前者是4 后者是 8；所以在进行二级指针分配内存时，第一次，要使用sizeof(int)

    int** res = (int**)malloc(sizeof(int*) * num); // 这里一定是 sizeof(int*)
    一般*returnSize 就是要返回的二维数组的行数；
    **returnColSize 表示要返回的二维数组的每一行的元素个数。
    对此，一般首先会把*returnSize = 0;
    *returnColSize = (int*)malloc(sizeof(int) * num);  // 这里分配内存的时候，只要使用sizeof(int) 即可

1. 要使用UT_hash，只要确定下key之后，关于data，如果有多个，可以直接写到hash结构里面，也可以搞个结构体，先写在一起，再放到hash结构里。

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

1. 对于入参是二维指针时，对入参的判断使用下面的几个条件就够

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

1. 有时候会发现，单独执行用例可以通过，但是提交后不能通过的情况发生，这里主要是使用了全局变量。系统在执行多个用例时，这个全局变量中的值相互影响了。
   在DFS相关的题目中，把需要记录的数据都使用指针的形式放在函数参数中，不要定义成全局变量，否则会导致有些用例不过.
2. 在LeetCode中要使用全局变量的话，可以先定义，但是不要初始化，在使用的主函数中初始化成0, 这样就能避免多次用例执行时的相互影响。另外，全局变量的命名不要和函数参数命名一样。
3. 返回空字符串的方法：
   ```
    char* result = (char*)malloc(sizeof(char) * 100);
    result[0] = '\0';
    return result; // 这样就返回空字符串
    对于返回字符串时，一定要在结尾处赋值'\0'
   ```

1. 二分查找类以及2数之和的移动过程，应该把相等的条件放在前面，然后每个else if 分支里面明确做一件事。把所有的情况都用elseif分支确定下来。

1. malloc返回的是一段内存的地址，这段内存，你准备存储什么类型，那么在分配时，就要使用 type* buf = (type*)malloc(sizeof(type) * size); 例如你打算存储的是 结构体指针，那么就要使用 type* buf = (type**)malloc(sizeof(type) * size); malloc分配的内存可以存储任意类型的数据

1. 1e9 类似这种类型的值不能作为数组下标。例如 int buf[1e7] 会报错
2. 参数宏，define(a,b)  直接这样写即可，不要写成 define((a), (b))  这种形式。 在它要替代的表达式中需要使用括号来把参数括起来。
3. 变量一定要按需初始化，例如在双指针或者二分查找题目中，要把left  和 right 初始化成确定的值，不能不初始化，否则在跑多个用例时会失败。
4. sprintf(buf, format, content) 这个函数默认会在结束的地方添加字符串的结尾符。
5. 数组元素去重的一般算法

    把数组元素排序 qsort()  
    for (int i = 0; i < size; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
    }

1. 三维指针

    对于需要返回3级指针的函数，在最初先分配一个3级指针，例如
       int*** res = (int***)malloc(sizeof(int**) * 10000);
    接口中的*returnSize表示该3维指针中二维部分有多少个。
    对于二维部分，先临时申请一个二维指针，用来存储在计算的过程中的临时的数据。 int* save = (int**)malloc(sizeof(int) * COUNT);
    在最终返回的结果的地方，再把这个临时的二维指针赋给res, 如下：
    res[returnSize] = (int**)malloc(sizeof(int) * COUNT); res本身是3级指针，res[*returnSize] 就变成二维的了，根据二维指针的个数，这里可以直接把临时的二维指针赋值给res, 完整的代码如下：
    
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
    三级指针的应用：
    int ***res = (int ***)malloc(sizeof(int**) * CNT);
    这里 res是三级指针，那么res[i] 就是二级指针。
    res[i] = (int**)malloc(sizeof(int*) * CNT);
    res[i][j] 就是一维指针。
    res[i][j] = (int*)malloc(sizeof(int) * CNT);
    

1. 关于变量的定义需要注意，像下面的2段代码对应定义的变量含义是不一样的。
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
    // 和下面的代码片段
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
    /*
    第一种，maxRight,maxLeft这2个变量定义在for循环的里面，每次执行for循环的时候，这2个值都是重新被定义的，相当于是局部变量了。后面这种，在for循环的外面定义一次，后面for循环中改变了这2个值后，
    下次执行for循环的时候，就是基于变化后的值。
    */
```
1. 如果暂存的类型是 long* 的，但是返回的值需要的是int, 那么一定要把这个long类型的转换成 int 之后，再返回，否则有问题。例如，暂存的数据存储在 res， 但是它是long 的，返回的值需要int，所以下面需要类型转换一下。
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
1. 计算数组上连续k个数的和的最大值的最佳实践。 注意这里两个指针都是从0开始的。
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
1. 数组上固定窗口最小值的最佳实践
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

注意这里的 >= 和上面的最大值是不一样的。
```
1. 一维重叠判断和二维重叠的判断
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

1. dfs和回溯的差异，什么时候用回溯，什么时候用dfs？

    回溯是要遍历所有情况，在所有情况的基础上，选择结果。例如题目1102，得分最高的路径，要使用深度优先搜索，找到1条路上最小的值。然后在回溯回来，遍历所有的路径，找到所有路径上的最大值。

1. 一般自定义变量用来计算字符串的长度，不能在for循环中计算字符串长度
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
1. 安全函数与非安全函数对别
```
    sprintf_s(buff, length, "格式", "内容"）     ----> sprintf(buff, "格式"， "内容")
```
1. 内存分配注意事项
```
    对于 int** res = (int**)calloc(cnt, sizeof(int*)); 这个表示已分配cnt个存储int* 指针的内存空间给res.
    在对于二级指针分配内存时，如果 res[i] = (int*)calloc(len, sizeof(int)); 中的i > cnt,那么就是内存访问错误问题了。
```
1. UT_hash 当作链表使用,在于一些需要动态插入，删除，查询的题目，存储数据的数据结构应该考虑使用链表。参考题目 731 ，732的解答
2. 对于兑零钱的题目，可以这样来设计数据结构，最佳实际如下
---
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
1. 找数据之间的关系，巧妙应用UT_hash 解决 leetcode 1396 地铁设计系统。
---
    1. 设计一个hash表存储进站数据，key=ID, val(站名，进站时间)，再设计一个hash表存储出站数据，key=(进站名-出站名的字符串)， val(总人数， 总时间)。
    2. 进站时保存相关信息，出站时，先在基于ID，找到进站名，然后在把出站名组装成 第二个hash表的key, 在hash表中添加或查找
    3. 最终出站hash表中存储的信息，就能够帮忙我们计算 从 A - B站的平均时间。 用总时间/总人数
```
1. 简单的两两交换不要写错了
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
1. 要注意大量的内存分配和初始化也是比较耗时的。对于要存储很多返回结果的题目，最好按需分配内存，不能一次在开始全部分配完成。
```
        res = (int*)calloc(CNT, sizeof(int*));
        for (int i = 0; i < CNT; i++) {
            res[i] = (int*)calloc(HIGH, sizeof(int));
        }
应该像下面，在需要的时候分配

        if (curSum == g_target && root->left == NULL && root->right == NULL) {
            res[g_returnSize] = (int*)calloc(cnt, sizeof(int));
            memcpy(res[g_returnSize], tmpSave, sizeof(int) * cnt);
            columnSizes[g_returnSize] = cnt;
            g_returnSize++;
            return;
        }
```
1. 二叉树的序列化：要求二叉树上重复的子树 652

    如何在二叉树上找重复的子树，关键要把二叉树序列化后，即把二叉树转成字符串，这样根据hash就能够找到是否有重复的字符，进而判断是否有重复的子树。参考题解652

1. 图的序列化： 不同岛屿的数量694

    如何求不同岛屿的数量？ 我们把遍历岛屿的顺序使用数字1,2，3,4来代替，如果是相同的岛屿，那么他们遍历的顺序是一样的，如果把1,2,3,4 转成字符串，那么就可以使用hash来判断是否重复，进而可以
    计算不同的岛屿数量。
    

1. 思路转变的例子

    1. 题目1151. 有个序列只有0,1，要求把所有的1连接在一起，使用的最小交换次数。这个题目要想到滑动窗口上来。大概的思路就是先计算出所有的1的个数，以这个长度为滑窗，
    然后计算这个滑窗中1的最大数量，然后使用总共的1的数量减去这个最大值就是结果。暴力容易超时，在计算1的时候，直接把所有数加起来即可，因为只有0,1.还有在滑窗上计算1
    的个数时，也是吧右边的数据加进来，把左边的数据减去，即可。

1. ascii码中可显示的第一个字符是空格' ', 在字符串题目中使用map时注意。
     
2. sprintf 这种函数的打印格式 "%02d" 表示右对齐，打印位宽是2位，如果不够2位，则左边补0.  注意一些特殊打印场合的使用，另外在十六进制场景时 "%08x" 和"%08X"显示出来的数据格式不一样，后者是大写。
     
3. 在题目中使用全局变量后，切记不能在函数参数中，再使用同名的参数。 这样会导致这个全局变量不其作用，它里面根本不能保存你在函数中对这个形参的任何操作。
4. 对于换行符\n 制表符 \t 这种是一个字符， 不要当成2个字符。
5. 对于二维数组的插入操作，我们可以之间转换成1维数组的赋值。实例代码如下
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
1. 注意memset用来初始化内存时只能用来初始化成0，如果需要初始化成其他值，则需要通过for循环来逐个遍历数组成员来初始化。例如代码：
 int rate[10]; memset(rate, 1, sizeof(rate)); 这个与预期的rate[0] = 1,是不一样的。
 memset或者memcpy这些都是按照字节来初始化和拷贝的，对于int型变量占据4个字节。这里相当于是吧4个byte的位置上都初始化成1了。
2. 在C语言格式化话的时候，%[xxx] 这种形式就是按照正则表达式来解析，其中[xx]就是正则表达式的内容。例如
```
           if (scanf_s("%d %[^)]) %[^)])", &processes->id, occupied, sizeof(occupied), requested, sizeof(requested)) != 3) {
               return false;
           }
```
3. 在使用strtok分割字符串时，一定要对字符串数组进行分割，不能对字符串指针进行分割，否则会报错。
4. ilearning平台考试注意事项
```
       1. 使用strlen()库函数时，要强制转换成int类型，strlen()本身是unsigned long 类型的。例如int len = (int)strlen("hello world");
       2. 使用移位运算符时 << >> 它们的右操作符要求是无符号数，因此需要强转一下。
       3. for循环中的局部变量的命名不同的for循环要使用不同的。
       4. while(表达式)；// 这个表达式一定要搞成bool类型，不要直接填个数字，非0认为是true,0认为false
       5、涉及到类型自动转换的也会扣分，所有的类型转换都要强制显示的写出来。
       6、不能自己定义数据类型，例如typedef unsigned int uint32_t;
       7、在使用strncpy_s(buff, buffSize,xx,xx)时，buffSize不能够搞成魔鬼数字
       8、使用calloc(xx, sizeof(bb))  注意当前函数原型是void* calloc（unsigned int num，unsigned int size）. sizeof()这个变量的符号类型是unsigned long的。因此要注意函数参数类型必须一样。
       9、另外char类型的数据不能做为数组的下标。
       10、void qsort(void*base,size_t num,size_t width,int(__cdecl*compare)(const void*,const void*)) 可见第二个，第三参数都是size_t类型的实际上是unsigned long 类型的,如果在使用的过程中给第2个第3个参数传递的值的类型不是无符号数的话，就会扣分。
       11、宏不加括号，也是要扣分的 #define MIN_VAL (-10000)
       12、不能使用非安全函数 比如 sprintf 这个是会被扣分的。要使用sprintf_s(out, outBufSize, "%s", str);
       13、memcpy_s(dst, size, src, size) 这里的size参数是无符号类型的，在实际使用过程中要注意，如果是int型的，则需要强转转换一下
       14、G.FUU.12 正确设置安全函数中的destMax参数
       15、G.FUU.21 禁止使用内存操作类不安全函数
       16、G.INT.10 确保整数转换不会造成数据截断或符号错误（主要是函数入参问题，使用wecode时，注意看一下函数入参类型）
       17、G.CTL.01 判断条件中的表达式的结果必须是布尔值。
       18、https://openx.huawei.com/communityWikiDetails?communityId=41&ibid=SPE1000000103&navid=NVI1000001148&token=eyJhbGciOiJIUzUxMiJ9.eyJzdWIiOiJsMDA0NjY0MzkiLCJjcmVhdGVkIjoxNzAwMjI5OTIxMDYxLCJJUCI6IjEwLjY5LjEzOC4zIiwiZXhwIjoxNzAwMzE2MzIxfQ.dMLWCO8PJoj_zPtFqtoPJNutw4g_DJYHJq9EmZ5Tc9ST7ZWwsWkPFrMfmEFfda5DpIXYkKg0GAPsSGKjR4vcaQ C语言规范，常见扣分项要在这里查一下。
       19. ilearnning平台上面fmax, calloc()这些函数也是可以使用的，如果执行提示使用了非标准库这种错误，一定是访问空指针了。
       20. 可以使用strstr(src, dst) == src 来精确匹配前导字符串dst
       21. 打印参数的格式不正确的也是要扣分的
       22. 滑动窗口最终计算结果应该在增加left导致条件不满足的while循环的外面，不能在里面进行结果更新，否则会出现数据尾部调通也满足的，未统计进来
       23. 对于字符串指针的栈结构，需要知道字符串的申请和释放空间的函数
       VosStack* CreateStrStack()
       {
           vosDupFreeFuncPair keyFunc;
           keyFunc.dupFunc = StrkeyDupFunc;
           keyFunc.freeFunc = free;
           VosStack* sys = VOS_StackCreate(&keyFunc);
           return sys;
       }
       StrkeyDupFunc()这个函数的具体实现如下：
       static inline void* StrKeyDupFunc(void* ptr)
       {
           char* origkey = (char*)ptr;
           size_t len = strlen(origkey);
           char* key = (char*)malloc(len + 1);
           if (key == NULL) {
               return NULL;
           }
           if (strcpy_s(key, len + 1, origkey) != 0) {
               free(key);
               return NULL;
           }
           key[len] = '\0';
           return key;
       }
       24. 如何判断在哪种场景下使用二分法：一方面要求使数据有序，其二就是要求一个达到目标值的最大/最小值, 这个最小/最大值跟目标值有一定的单调关系。
```
5. 对于合并区间的题目，判断区间有没有重叠采用的方式是preNode->endAddr + 1 > curNode->startAddr,如果这个成立的话，就是没有重叠，不需要合并。
6. 对于数据量不大的场景，需要使用双端队列或者双向链表的情况，可以直接使用数组（空间是所需要的2倍），再配合双指针来实现数据的添加/删除或者访问
7. 对于上下左右遍历的场景，如果需要在计算次数，而不是收集可能的结果的话，就不要是有for 循环来遍历，就直接把函数显示调用4次，在进来的时候，对各种需要退出的场景进行罗列。
8. 把2层for循环改成1层for循环的技巧
```
       for (int k = 0; k < rows * cols; k++) {
            backtrace(rows, cols, charMatrix, k / cols, k % cols, i, 0, words[i]);
       }
```
9. 在遍历二维矩阵时，分别计算行或列的写法
```
           for (int i = 0; i < n; i++) {
               int rowRights = 0;
               int colRights = 0;
               for (int j = 0; j < n; j++) {
                   rowRights += hasRight[board[i][j]]; // 计算第i行的情况
                   colRights += hasRight[board[j][i]]; // 计算第i类的情况
               }
               if (rowRights >= n - 1 || colRights >= n - 1) {
                   return true;
               }
           }
```
10. 对于类似树形结构的题目，在定义结构时，参考二叉树的定义，其成员部分，要定义成结构体指针
```
        struct treeNode {
            int val;
            struct treeNode* left;
            struct treeNode* right; // 这里定义成指针。
        };
```
11. 公司C语言库函数的使用小结

    对于VoSVector的数据结构的标准API，其实就是一种数组，使用VOS_VectorPushBack()接口把元素添加到数组的结尾，可以基于索引访问，VOS_VectorAt(),能够清除指定节点的数据 VOS_VectorErase(index),还有排序功能VOS_VectorSort（）。

1. 二进制和十进制之间的转换代码
```
       /*二进制字符串转换成十进制*/
       static int BinaryToTen(const char *da, int size)
       {
           for (int i = 0, j = cnt - 1; i < j; i++, j--) {
               int tmp = da[i];
               da[i] = da[j];
               da[j] = tmp;
           }
           int rst = 0;
           for (unsigned int i = 0; i < size; i++) {
               rst += (da[i] == '1') ? (1 << i) : 0;
           }
           return rst;
       }
       
       /*十进制字符串转换成二进制*/
       static int TenToBinary(int* da, int size, int n)
       {
           int cnt = 0;
           while (n) {
               da[cnt++] = n % 2;
               n = n / 2;
               if (cnt >= size) {
                   break;
               }
           }
           for (int i = 0, j = cnt - 1; i < j; i++, j--) {
               int tmp = da[i];
               da[i] = da[j];
               da[j] = tmp;
           }
           return cnt;
       }
       
   如果想把任意进制的的字符串转换成数字，可以使用库函数strtol.
       #include <stdio.h>      /* printf */
       #include <stdlib.h>     /* strtol */
       
       int main ()
       {
         char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
         char * pEnd;
         long int li1, li2, li3, li4;
         li1 = strtol (szNumbers,&pEnd,10);
         li2 = strtol (pEnd,&pEnd,16);
         li3 = strtol (pEnd,&pEnd,2);
         li4 = strtol (pEnd,NULL,0);
         printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
         return 0;
       }
       // 输出信息如下：
       The decimal equivalents are: 2001, 6340800, -3624224 and 7340031
       // 当前接口的原型：long int strtol (const char* str, char** endptr, int base); 它会基于base来获取尽可能多的字符串来转换成数字，
```
2. 二进制和十六进制之间的转换
```
       void BinaryToHex(char* buf, int size, char* outPut, int* resSize)
       {
           int cnt = 0;
           for (int i = 0; i < size; i += 4) {
               int sum = (buf[i] - '0') * 1 + (buf[i + 1] - '0') * 2 + (buf[i + 2] - '0') * 4 + (buf[i + 3] - '0') * 8;
               if (sum > 9) {
                   outPut[cnt++] = 'A' + sum - 0xA;
               } else {
                   outPut[cnt++] = sum + '0';
               }
           }
           *resSize = cnt;
           ReverseStr(outPut, cnt);
       }
```
   
   1. 十六进制字符串转换成十进制数，可以使用库函数sscanf直接转换成数值
```
           unsigned int dataB[arrayASize];
           for (int i = 0; i < arrayBSize; i++) {
               (void)sscanf_s(arrayB[i], "%x", &dataB[i]);
           }
           // 要注意：如果是按照%s来获取字符串的话，需要指定存储字符串的大小空间，如下所示：
           char tokenstring[] = "15 12 14...";
           char s[BUFFER_SIZE];
           memset_s(s, BUFFER_SIZE, 0, BUFFER_SIZE);
           iRet = sscanf_s( tokenstring, "%127s", s, BUFFER_SIZE );
           printf("String  iRet = %d, %s\n", iRet, s);
       
```
   1. 如果想把十六进制数值转换成字符串存储，则可以使用库函数sprintf_s()实例代码如下
```
           for (unsigned int i = 0; i < resCnt; i++) {
               (void)sprintf_s(outBuf[i], STR_LEN, "%08X", res[i]);
           }
```
   
   1. 多叉树的构造和遍历
```
       struct Tree {
           int level;
           char name[LINE_BUF_LEN];
           int childrenSize; // 多叉树中孩子个数。
           struct Tree* child; // 在添加节点时，要主动给其申请内存。
       };
       // 构造多叉树
       void BuildTree(struct Tree* root, NAME_POS curNode)
       {
           struct Tree* p = root;
           while (p->level + 1 < curNode.pos) { // 当前节点与父节点之间的层级关系。
               if (p->childrenSize == 0) {
                   break; // 找到当前节点的父节点。
               }
               p = &p->child[p->childrenSize - 1]; // 在孩子节点中找父节点。
           }
           if (p->level + 1 == curNode.pos) { // 确定了当前节点的父节点。
               int j = 0;
               for (; j < p->childrenSize; j++) {
                   if (strcmp(curNode.name, p->child[j].name) == 0) {
                       break;
                   }
               }
               if (j == p->childrenSize) { // 如果当前节点在他父节点下的所有孩子节点中都不存在的话，就需要把这个节点添加到孩子节点内存上。
                   struct Tree* tmpNode = (struct Tree*)calloc(1, sizeof(struct Tree));
                   (void)strcpy_s(tmpNode->name, LINE_BUF_LEN, curNode.name);
                   tmpNode->level = curNode.pos;
                   tmpNode->child = (struct Tree*)calloc(MAX_LINE, sizeof(struct Tree)); // 注意这里的内存需要自己申请,当前是子节点，也可能是后续节点的父节点，所以要放子节点时，要有空间。
                   p->child[p->childrenSize] = *tmpNode; // 将新节点放到孩子节点的内存里面。
                   p->childrenSize++;
               }
           }
       }
       // 多叉树的遍历 后续遍历。
       void Transerve(struct Tree* root, char *outBuf, int maxOutBufLen, int* ressize)
       {
           if (root == NULL) {
               return;
           }
           for (int i = 0; i < root->childrenSize; i++) {
               Transerve(&root->child[i], outBuf, maxOutBufLen, ressize);
           }
           int len = sprintf_s(outBuf + *ressize, maxOutBufLen - (*ressize), "%s ", root->name);
           *ressize += len;
           return;
       }
       // 调用过程，这里先定义一个root空节点，然后逐个节点进来创建树结构。最终使用这个root节点做遍历。
       void main()
       {
           struct Tree* root = NULL;
           for (int i = 0; i < lineNum; i++) {
               if (namePos[i].pos != 0 && root == NULL) {
                   continue;
               } else if (root == NULL) {
                   root = (struct Tree*)calloc(1, sizeof(struct Tree));
                   (void)strcpy_s(root->name, LINE_BUF_LEN, namePos[i].name);
                   root->level = namePos[i].pos;
                   root->childrenSize = 0;
                   root->child = (struct Tree*)calloc(MAX_LINE, sizeof(struct Tree));
               } else {
                   BuildTree(root, namePos[i]);
               }
           }
           int ressize = 0;
           Transerve(root, outBuf, maxOutBufLen, &ressize);
           if (ressize > 0) {
               outBuf[ressize] = '\0';
           }
       }
```  
   
3. 在使用优先级队列时，对于排序函数要注意
```
    int Cmp(uintptr_t data1, uintptr_t data2)
    {
        return data1 > data2; // 采用大顶堆。可以理解成倒序排列。官方文档上是return （data1 - data2)// 是大顶堆。
    }
    VosPriQue* pQ = VOS_PriQueCreate(Cmp, NULL); // 创建优先级队列，Cmp表示比较函数。
    // 对于大顶堆，排序函数采用降序的方式来设置。
    //场景：优先级队列使用于要求队列数据动态有序的场景，比如任务按照优先级调度，TopK问题。
     
    //注意事项： 只有往队列中存储的数据是结构体时，才需要写成员内存分配函数
    static inline void *dupFunc(void *src)
    {
        UserData *tmpSrc = (UserData *)src;
    
        UserData *data = (UserData *)malloc(sizeof(UserData));
        (void)memset_s(data, sizeof(UserData), 0, sizeof(UserData));
    
        (void)memcpy_s(data, sizeof(UserData), tmpSrc, sizeof(UserData));
        return data;
    }
    VosDupFreeFuncPair dupFreeFunc = {
        dupFunc, free
    }
    正确的使用方法：VOS_PriQueCreate（Cmp, &dupFreeFunc);
```
1. 对于二维数组的qsort排序，Cmp函数的写法
```
    int Cmp(const void* a, const void* b)
    {
        return ((int*)a)[0] - ((int*)b)[0]; // 注意这里要转成一维数组。
    }
    int abc1[3][2] = {{10,45}, {1,0},{30,22}};
    qsort(abc1, 3, sizeof(abc1[0]), Cmp);
```

1. hash和map都是以key-value形式来存储数据的，只不过hash的底层是通过hash表来存储，map则是红黑树。他们时间复杂度不一样，前者O(1)后者是O(logN)
