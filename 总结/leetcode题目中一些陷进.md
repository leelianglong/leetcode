# 1、leetcode平台上 sizeof(int) 和 sizeof(int*) 大小是不一样的。前者是4 后者是 8；所以在进行二级指针分配内存时，第一次，要使用
```
int** res = (int**)malloc(sizeof(int*) * num); // 这里一定是 sizeof(int*)
```
