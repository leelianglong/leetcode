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

该函数的使用需要先执行快速排序

```
void* bsearch (const void* key, const void* base,
               size_t num, size_t size,
               int (*compar)(const void*,const void*));
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
