### 题目 目标和

思路：

1、使用dfs，需要构造的参数有： nums, numssize ,target这3个是必须的，另外，我们要遍历序列，那么需要一个变量来标记遍历到哪里 所以需要curpos. 另外

每执行一步，需要记录当前的和. 还有题目要求有多少种组合方式，所以还需要一个变量来记录找到的组合个数，由于是出参，所以需要设置成指针型

2、我们每一步有2种做法，即在cursum上加上当前的遍历的数值，或者在cursum上减去当前遍历的数值。

注意：在边界条件判断的地方使用 curPos == numssize 而不是 curPos == numssize - 1, 是因为该算法是以 curPos + 1 作为下次比较的curPos的，所以这里应该是前者。


### 代码
```
void dfs(int* nums, int numsSize, int curPos, int curSum, int target, int* counter)
{
    if (curPos == (numsSize)) {
        if (target == curSum) {
            (*counter)++;
        }
    } else {
        dfs(nums, numsSize, curPos + 1, curSum + nums[curPos], target, counter);
        dfs(nums, numsSize, curPos + 1, curSum - nums[curPos], target, counter);
    }
}

int findTargetSumWays(int* nums, int numsSize, int S){
    if (numsSize <= 0) {
        return -1;
    }
    int counter = 0;
    dfs(nums, numsSize, 0, 0, S, &counter);
    return counter;
}
```
