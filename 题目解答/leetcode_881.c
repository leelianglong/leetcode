int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int numRescueBoats(int* people, int peopleSize, int limit){
    qsort(people, peopleSize,sizeof(int), cmp);
    int res = 0;
    int left = 0;
    int right = peopleSize - 1;
    while (left <= right) {
        if ((people[left] + people[right] > limit ) && (left != right)) {  // 注意双指针的移动时，也也考虑是移动左边还是右边，还是双边同时移动
            right--;
        } else {
            left++;
            right--;
        }
        res += 1;
    }
    return res;
}
