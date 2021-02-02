### 1、 ctype.h   头文件中有数字、字符的判断。
```
isalnum
Check if character is alphanumeric (function )
isalpha
Check if character is alphabetic (function )
isblank 
Check if character is blank (function )
iscntrl
Check if character is a control character (function )
isdigit
Check if character is decimal digit (function )
isgraph
Check if character has graphical representation (function )
islower
Check if character is lowercase letter (function )
isprint
Check if character is printable (function )
ispunct
Check if character is a punctuation character (function )
isspace
Check if character is a white-space (function )
isupper
Check if character is uppercase letter (function )
isxdigit
Check if character is hexadecimal digit (function )
```
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
                break;
            }
        }
```
