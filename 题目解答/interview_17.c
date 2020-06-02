#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* shortestSeq(int* big, int bigSize, int* small, int smallSize, int* returnSize){
    if (big == NULL || small == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int* res = (int*)malloc(sizeof(int) * 2);
    memset(res, 0, sizeof(int) * 2);
    int hash[100001] = {0};
    for (int i = 0; i < smallSize; i++) {
        hash[small[i]]++;
    }

    int left = 0;
    int right = 0;
    int match = 0;
    int minLength = INT_MAX;
    while (right < bigSize) {
        if (hash[big[right]] == 1) {
            match++;
        }
        while (match == smallSize) {
            // 首次找全了。
            minLength = (right - left + 1) < minLength ? (right - left + 1) : minLength;
            printf("right=%d, left=%d\n", right, left);
            while (left < right) {
                if (hash[big[left]] == 1) {
                    match--;
                    left++;
                    break;
                }
                left++;
            }
        }
        right++;
    }
    printf("\nmin=%d\n", minLength);
    *returnSize = 2;
    return res;
}



int main(void)
{
    int big[] = {7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7};
    int small[] = {1,5,9};
    int returnSize = 0;
    shortestSeq(big, sizeof(big) / sizeof(big[0]), small, sizeof(small) / sizeof(small[0]), &returnSize);
    system("pause");
}
