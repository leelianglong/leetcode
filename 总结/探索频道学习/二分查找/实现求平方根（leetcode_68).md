### 题目 leetcode 69

题目要求实现 sqrt()的求解。对于求出来的小数部分全部舍弃，例如 sqrt(8) = 2.

对于本题，可以转换成 求 满足 K^2 <= X 的最大K值。 对于k我们可以在范围0 到 x 之间查找，找到合适的返回。

什么是合适的？在K*K == x 时，就是结果，对于 K*K大于 或者 小于 X时，在多判断一步，如果结果能够出现翻转，则说明已经找到了，进行退出。

### 代码
```
int mySqrt(int x){
    long long left = 0;
    long long right = x - 1;
    if (x == 0 || x == 1) {
        return x;
    }
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (mid * mid == x) {
            return mid;
        } else if (mid * mid < x) {
            left = mid + 1;
            if ((mid + 1) * (mid + 1) > x) {
                return mid;
            }
        } else if (mid * mid > x) {
            right = mid - 1;
            if ((mid - 1) * (mid - 1) < x) {
                return mid - 1;
            }
        }
    }
    return -1;
}
```
