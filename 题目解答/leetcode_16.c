/* 
对当前题意没有完全理解透彻，下面这种前缀和的思路不对
针对用例：
[-1,2,1,7,8,9,0]
1
*/
int cmp(const void* a, const void* b)
{
    int* aa = (int*)a;
    int* bb = (int*)b;
    return aa[0] - bb[0];
}

#define MIN(a, b) ((a) > (b) ? (b) : (a))
int threeSumClosest(int* nums, int numsSize, int target){
    if (numsSize == 3) {
        return nums[0] + nums[1] + nums[2];
    }
    qsort(nums, numsSize, sizeof(nums[0]), cmp);
    int presum[numsSize + 1];
    memset(presum, 0, sizeof(presum));
    for (int i = 0; i < numsSize; i++) {
        presum[i + 1] = presum[i] + nums[i]; // 数组中的数字是可以随意选的，不能使用前缀和这种连续的求解。
    }
    int res = INT_MAX;
    for (int i = 0, k = 3; i < numsSize + 1 - 3 && k < numsSize + 1; i++, k++) {
        res = MIN(res, abs(presum[k] - presum[i] - target)); 
    }    
    return res + target;
}

/*
* 下面题解的思路是
* 1、先排序，固定一个数据，然后在剩下的区间上进行双指针遍历，记录最小差值。
* 2、下面需要注意的是 while (left < right) 这里是没有等号的，
*    原因是要在剩余的区间上找2个数据，而不是1个数据，不要受二分查找的思维定式，不会漏掉某个元素
*/
int cmp(const void* a, const void* b)
{
    int* aa = (int*)a;
    int* bb = (int*)b;
    return aa[0] - bb[0];
}

#define MIN(a, b) ((a) > (b) ? (b) : (a))
int threeSumClosest(int* nums, int numsSize, int target){
    if (numsSize == 3) {
        return nums[0] + nums[1] + nums[2];
    }
    qsort(nums, numsSize, sizeof(nums[0]), cmp);
    int res;
    int gap = INT_MAX;
    for (int i = 0; i < numsSize - 2; i++) {
        int left = i + 1;
        int right = numsSize - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == target) {
                return target;
            } 
            if (abs(sum - target) < gap) {
                gap = abs(sum - target);
                res = sum;
            }
            if (sum > target) {
                right--;
            } else {
                left++;
            }
        }
    }
    return res;
}
