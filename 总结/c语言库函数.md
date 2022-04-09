### 1、 ctype.h   头文件中常见的数字字符的判断函数。
---
int isalnum ( int c );
判断输入参数是不是字母或者数字
```
int main ()
{
    int i;
    char str[]="c3po...";
    i=0;
    while (isalnum(str[i])) i++;
    printf ("The first %d characters are alphanumeric.\n",i);
    return 0;
}
结果是：The first 4 characters are alphanumeric
```
int isalpha ( int c );
判断是不是英文字母，返回值是true 或者false。

int isdigit ( int c );
判断输入参数是不是数字

int islower ( int c );
判断输入参数是不是小写字母

int isupper ( int c );
判断输入参数是不是大写字母
---
### bsearch()

bsearch()函数是基于快速排序的结构，进行搜索的。各个参数的意义如下：

```
void* bsearch (const void* target,  // 要查找的目标
               const void* buf, // 搜索空间
               size_t num, // 搜索空间的大小
               size_t size, //搜索的每个元素的大小
               int (*compar)(const void*,const void*) // 排序的规则
               );
返回值是找到元素的地址。
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort, bsearch, NULL */

int compareints (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int values[] = { 50, 20, 60, 40, 10, 30 };

int main ()
{
  int * pItem;
  int key = 40;
  qsort (values, 6, sizeof (int), compareints);
  pItem = (int*) bsearch (&key, values, 6, sizeof (int), compareints);
  if (pItem!=NULL)
    printf ("%d is in the array.\n",*pItem);
  else
    printf ("%d is not in the array.\n",key);
  return 0;
}
```

### 求绝对值

abs()  和 llabs() 这2个函数都可以求绝对值，前者对int 型的数据求绝对值， 后者对long long 类型的数据求绝对值。


### strtok 函数使用
strtok的参数一定要是字符串数组，不能是字符串常量指针。例如下面这种使用是错误的，有内存问题。
```
    const char* tmp = "a good      example";
    char* res = NULL;
    res = strtok(tmp, " ");
    while (res) {
        printf("%s\n", res);
        res = strtok(NULL, " ");
    }
```
下面这种是正常的。
```
    char tmp[] = "a good      example";
    char* res = NULL;
    res = strtok(tmp, " ");
    while (res) {
        printf("%s\n", res);
        res = strtok(NULL, " ");
    }
```

### strstr()

1. strstr(a,b) 在a中查找是否包含b,如果找到返回找到的位置，返回的是char*.

2. 该函数的作用就是从a[0] 开始遍历查找是否满足b字符串的，所以如果a中包含多个b时，如果使用了for循环，一旦找不到，则立即退出，没必要再继续找。
```
    for (int i = 0; i < smallsSize; i++) {
        char* tmp = big;
        int* save = (int*)malloc(sizeof(int) * 1000);
        memset(save, 0, sizeof(int) * 1000);
        int count = 0;
        for (int j = 0; j < strlen(big) && strlen(smalls[i]) > 0; j++) {
            char* find = strstr(&big[j], smalls[i]);
            if (find) {
                save[count++] = (find - tmp);
                j = find - tmp;
            } else {
                break;  // 很关键，否则会超时
            }
        }
```

### 比较大写的库函数 fmax(a,b)  fmin(a,b)

### 字符串与数字之间转换的库函数
1. int sscanf ( const char * s, const char * format, ...);
具体含义是：将字符串s 按照格式 format的形式写到某个变量中。
```
    char str[] = {"123"};
    int num = 0;
    sscanf(str, "%d",&num);
    printf("num = %d", num);
```
上面的示例就把字符串123 变成了数字 123.
---
2. int sprintf ( char * str, const char * format, ... );
具体含义：可以把数字按照format的格式写到str
```
    char t1[4] = {0};
    sprintf(t1, "%d", 123);
    printf("%s\n", t1);
```
这里打印的字符串是 123.
---

3. long int strtol (const char* str, char** endptr, int base);
具体含义：将字符串str 按照基准base,转换成长整型
```
    char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
    char * pEnd;
    long int li1, li2, li3, li4;
    li1 = strtol (szNumbers,&pEnd,10);
    li2 = strtol (pEnd,&pEnd,16);
    li3 = strtol (pEnd,&pEnd,2);
    li4 = strtol (pEnd,NULL,0);
    printf ("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
```
打印结果：The decimal equivalents are: 8193, 6340800, -3624224 and 7340031。
注意第二个参数，是二级指针。以及后面的base,就是进制的意思。0也表示10进制。
---

4. long int atol ( const char * str );
具体含义：将单个字符串转换成长整型
```
    int res = atol("1234");
    printf("res=%d", res);
```
打印结果：1234.

3和4都可以达到把字符串转换成正数，strtol()功能更强大一些。