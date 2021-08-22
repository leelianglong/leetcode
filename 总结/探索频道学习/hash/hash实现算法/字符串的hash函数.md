### 字符串的常见hash函数
1. 加法hash
```
static int additiveHash(String key, int prime)
 {
  int hash, i;
  for (hash = key.length(), i = 0; i < key.length(); i++)
   hash += key.charAt(i);
  return (hash % prime);
 }
```
2. 位运算hash
```
static int rotatingHash(String key, int prime)
 {
   int hash, i;
   for (hash=key.length(), i=0; i<key.length(); ++i)
     hash = (hash<<4)^(hash>>28)^key.charAt(i);
   return (hash % prime);
 }
```
3. 乘法hash
```
static int bernstein(String key)
 {
   int hash = 0;
   int i;
   for (i=0; i<key.length(); ++i) hash = 33*hash + key.charAt(i);
   return hash;
 }
// 上面的乘法可以使用的数字有31,131,1313等

static int RSHash(String str)
{
        int b    = 378551;
        int a    = 63689;
        int hash = 0;

       for(int i = 0; i < str.length(); i++)
       {
          hash = hash * a + str.charAt(i);
          a    = a * b;
       }
       return (hash & 0x7FFFFFFF);
}
```
