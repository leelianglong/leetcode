bool canJump(int* nums, int numsSize){
    int k = numsSize - 1;
    for (int i = numsSize - 1; i >= 0; i--) { // 从后往前遍历，逐渐更新左边边界，如果能够走的0处，则说明能够成功。
        if (nums[i] + i >= k) {
            k = i;
        }
    }
    return k == 0;
}
