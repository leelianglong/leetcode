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
