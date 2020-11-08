### leetcode 470 
题目的意思
通过rand7 生成 Rand10（），即已知均匀分布的【1，7】的随机数，产生一个均匀分布的【1，10】的随机数

### 学习资料
https://leetcode-cn.com/problems/implement-rand10-using-rand7/solution/cong-zui-ji-chu-de-jiang-qi-ru-he-zuo-dao-jun-yun-/

### 实现代码
```
int rand10() {
    int num;
    do {
        num = (rand7() - 1) * 7 + rand7();
    } while (num > 40);
    return (num - 1) % 10 + 1;
}
```

### 思路简单分析：
1. 通过rand7 可以得到【1，7】均匀的随机数。
2. 通过(rand7 - 1) * 7 + rand7 就能够得到均匀的【1，49】的随机数，这个是有相关定理，也可以通过上面的分析得到。
3. 题目要求得到【1，10】的均匀随机数，我们可以在2的基础上去掉【41，49】这几个数子，只求【1，40】之间的随机数，然后对其减1 对10取余，再 加 1 即可。
