#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int cmpIncr(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}
int cmpDesc(const void* a, const void* b)
{
    return *(int*)b - *(int*)a;
}

int movesToMakeZigzag1(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 2) {
        return 0;
    }
    int i;
    int j;
    bool order = false;
    int exit = 0;
    int* tmp = (int*)malloc(sizeof(int) * numsSize);
    memset(tmp, 0, sizeof(int) * numsSize);
    memcpy(tmp, nums, sizeof(int) * numsSize);

    for (j = 1; j < numsSize; j++) {
        if (nums[0] < nums[j]) {
            qsort(tmp, numsSize, sizeof(int), cmpIncr);
            for (j = 0; j < numsSize; j++) {
                if (tmp[j] != nums[j]) {
                    exit = 1;
                    break;
                }
            }
            if (j == numsSize) {
                order = true;
            }
        } else  if (nums[0] > nums[j]){
            qsort(tmp, numsSize, sizeof(int), cmpDesc);
            for (j = 0; j < numsSize; j++) {
                if (tmp[j] != nums[j]) {
                    exit = 1;
                    break;
                }
            }
            if (j == numsSize) {
                order = true;
            }
        }
        if (exit == 1 || order == true) {
            break;
        }
    }
    int oddCounter = 0;
    memset(tmp, 0, sizeof(int) * numsSize);
    memcpy(tmp, nums, sizeof(int) * numsSize);
    for (i = 2; i < numsSize - 1; i += 2) {
        if (tmp[i] <= tmp[i + 1]) {
            oddCounter += abs(tmp[i + 1] - tmp[i]) + 1;
            tmp[i + 1] = tmp[i] - 1;
        } 
       if (tmp[i] <= tmp[i - 1]) {
            oddCounter += abs(tmp[i - 1] - tmp[i]) + 1;
            tmp[i - 1] = tmp[i] - 1;
        }
    }
    if ((numsSize % 2 == 1) && (order == false)) {
        oddCounter += tmp[numsSize - 1] - tmp[numsSize - 2] + 1;
    }

    int evenCounter = 0;
    memset(tmp, 0, sizeof(int) * numsSize);
    memcpy(tmp, nums, sizeof(int) * numsSize);
    for (i = 1; i < numsSize - 1; i += 2) {
        if (tmp[i] <= tmp[i - 1]) {
            evenCounter += abs(tmp[i] - tmp[i - 1]) + 1;
            tmp[i - 1] = tmp[i] - 1;
        }
        if (tmp[i] <= tmp[i + 1]) {
            evenCounter += abs(tmp[i] - tmp[i + 1]) + 1;
            tmp[i + 1] = tmp[i] - 1;
        }
    }

    if ((numsSize % 2 == 0) && (order == false)) {
        evenCounter += tmp[numsSize - 1] - tmp[numsSize - 2] + 1;
    }
    if (oddCounter != 0 && evenCounter != 0) {
        return oddCounter > evenCounter ? evenCounter : oddCounter; 
    } else if ((oddCounter == 0 || evenCounter == 0) && order){
        return oddCounter == 0 ? evenCounter : oddCounter;
    } 
    return 0;
}

/*
 上面的解法，边界值没有处理好。下面这是一种边界值的处理思路，在一道题里面统一使用加法来遍历。
 下面解法不是在遍历时直接取遍历奇数 和 偶数索引，而是依次遍历，在里面来处理偶数索引或者奇数索引的问题。
 这样也就避免了过多边界值的处理。
 这里使用2个for循环，的原因是每个for循环处理一种规则。
*/
int movesToMakeZigzag(int* nums, int numsSize){
    if (nums == NULL || numsSize <= 2) {
        return 0;
    }   
    int* tmp = (int*)malloc(sizeof(int) * numsSize);
    memset(tmp, 0, sizeof(int) * numsSize);
    memcpy(tmp, nums, sizeof(int) * numsSize);
    int oddCounter = 0; 
    int i;  
    for (i = 0; i < numsSize - 1; i++) {
        if (i % 2 == 0) {
            if (tmp[i] < tmp[i + 1]) { //当前偶数索引小于相邻的不处理
                continue;
            } else {
                oddCounter += (tmp[i] - tmp[i + 1]) + 1;
                tmp[i] = tmp[i + 1] - 1;
            }
        } else {
            if (tmp[i] > tmp[i + 1]) {
                continue;
            } else {
                oddCounter += tmp[i + 1] - tmp[i] + 1;
                tmp[i + 1] = tmp[i] - 1;
            }
        }
    }
    int evenCounter = 0; 
    memset(tmp, 0, sizeof(int) * numsSize);
    memcpy(tmp, nums, sizeof(int) * numsSize);
    for (i = 0; i < numsSize - 1; i++) {
        if (i % 2 == 0) {
            if (tmp[i] > tmp[i + 1]) { //当前偶数索引大于相邻的不处理
                continue;
            } else {
                evenCounter += (tmp[i + 1] - tmp[i]) + 1;
                tmp[i + 1] = tmp[i] - 1;
            }
        } else {
            if (tmp[i] < tmp[i + 1]) {
                continue;
            } else {
                evenCounter += tmp[i] - tmp[i + 1] + 1;
                tmp[i] = tmp[i + 1] - 1;
            }
        }
    }
    return evenCounter > oddCounter ? oddCounter : evenCounter;
}

int main(void)
{
    int test[] = {1,2,3};
    int result = movesToMakeZigzag(test, sizeof(test) / sizeof(test[0]));
    printf("%d\r\n", result);
    system("pause");
}