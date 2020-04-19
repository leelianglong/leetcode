int findmax(int* nums, int k)
{   
    int max = INT_MIN;
    for (int i = 0; i < k; i++) {
        max = max > nums[i] ? max : nums[i];
    }
    return max;
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    *returnSize = 0;
    if (k == 1) {
        int* res = (int*)malloc(sizeof(int) * numsSize);
        memcpy(res, nums, sizeof(int) * numsSize);
        *returnSize = numsSize;
        return res;
    }
    int* res = (int*)malloc(sizeof(int) * (numsSize - k + 1));
    memset(res, 0, sizeof(int) * (numsSize - k + 1));
    int max = INT_MIN;
    int r = 0;
    int l = 0;
    int match = 0;
    int* window = (int*)malloc(sizeof(int) * k);
    memset(window, 0, sizeof(int) * k);
    while (r < numsSize) {
        window[match++] = nums[r];
        while (match == k) {
            res[(*returnSize)++] = findmax(window, k);
            for (int j = 0; j < k - 1; j++) {
                window[j] = window[j + 1];
            }
            l++;
            match--;
        }
        r++;
    }
    return res;
}
