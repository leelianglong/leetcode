/* 该题目要求给定一个数组 和 一个 K，使得数组刚好能够分成k个子数组，并且k个子数组的和是相等的。
*  基于这种搜索的题目，一般都是要使用dfs.这里先粗略的排除一些不可行的方案，例如，数组成员总和不能被k整除，明显不符合；
*  总和被K整除后得到的值就是每个集合的目标值。
*  我们要明确一点，这里有多个值相加后等于target，所以对访问过的数据是要记录的，例如 A+B+C 小于 target， 我们要记录A，B,C都被访问过了。
*  接下来要搜索另一个数，例如D，要记录D被访问了，A+B+C+D大于了target，说明D并不合适，那么要把D的访问标记清除了。因为，在 A+B+C 的组合中D不合适
*  可能在其他组合中合适。
*  dfs函数需要那些参数：搜索的数据， 数据的个数， 目标值， 需要找的组合个数（题目要求k个），搜索开始值，当前已访问数据的和，访问标记。
*  然后，是明确终结条件： 找到的组合数是0（我们从K递减的）； 搜索的起始范围大于数据个数；
*  搜索过程： 在数据区域中以搜索起始值开始搜索，判断当前值是否访问或，当前值和已访问数据和相加是否等于target。
*  如果等于，则把需要找的组合数 减1，另外起始搜索值也设置成0，已访问数据和设置成0， 开始下一轮搜索；
*  如果不等于，则更新搜索开始值，已访问数据和进行下一次搜索，并把当前访问标志清除。
*  搜索结束即可。
*/


bool dfs(int* nums, int numsSize, int start, int k, int target, int curSum, int* visited)
{
    if (k == 0) {
        //printf("\n 1");
        return true;
    }
    if (start >= numsSize) {
        //printf("\n 2");
        return false;
    }
    bool ret = false;
    for (int i = start; i < numsSize; i++) {
        if (visited[i]) {
            continue;
        }
        visited[i] = true;
        if (curSum + nums[i] == target) {
            ret = dfs(nums, numsSize, 0, k - 1, target, 0, visited);
        } else if (curSum + nums[i] < target){
            ret = dfs(nums, numsSize, i + 1, k, target,curSum + nums[i],visited);
        }
        if (!ret) {
            visited[i] = false;
        } else {
            //printf("\n 3");
            return true;
        }
    }
    //printf("\n 4");
    return false;
}

bool canPartitionKSubsets(int* nums, int numsSize, int k){
    if (k > numsSize || k <= 0) {
        return false;
    }
    int total = 0;
    for (int i = 0; i < numsSize; i++) {
        total += nums[i];    
    }
    int target = total % k;
    if (target != 0) {
        return false;
    }

    target = total / k;

    int* visited = (int*)malloc(sizeof(int) * numsSize);
    memset(visited, 0, sizeof(int) * numsSize);
    //printf("\n target=%d %d", target, k);
    return dfs(nums, numsSize, 0, k, target, 0, visited);
}
