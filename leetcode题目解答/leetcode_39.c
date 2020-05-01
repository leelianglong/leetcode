#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* 整个解题思路:
* 1、设置一个大循环，因为数字可以重复，所以从0开始。大循环中做的事情如下:
* 2、遍历序列中的每个数字，每遍历一个，就把这个数字放到堆栈中，并且从target中把这个数字减去
* 3、然后就回溯，重新从0开始遍历序列，执行2的动作
* 4、如果target等于0了，或者是负数了，就退出回溯，把栈顶元素POP出来，加到target中，然后进行大循环的下一次循环。
*
*/
void rec(int *arr, int len, int index, int *stack, int *stack_index,
         int target, int **ret, int *ret_index, int *ret_size)
{
    if (index >= len || target < 0)
        return;

    /* 符合条件，添加到答案中 */
    if (target == 0)
    {
        ret[(*ret_index)] = (int *)malloc(sizeof(int) * (*stack_index));
        ret_size[(*ret_index)] = *stack_index;
		printf("*ret_index = %d %d\r\n", *ret_index, ret_size[(*ret_index)]);
        memcpy(ret[(*ret_index)], stack, (*stack_index) * sizeof(int));
        (*ret_index)++;
        return;
    }

    /* 回溯循环，注意从index开始，因为可以重复使用相同的元素 */
    for (; index < len; index++)
    {
        target -= arr[index];
        stack[(*stack_index)++] = arr[index];

        rec(arr, len, index, stack, stack_index, target, ret, ret_index, ret_size);

        (*stack_index)--; // 要执行到这里，一定是从target退出才会来。否则一直再调用rec.
        target += arr[index]; // 这里是把上次添加到堆栈中，但是最终之和不满足target的那个数据重新算到target上。接下来进行循环，index增加1。
    }
}

#define LEN 0xffff

int **combinationSum(int *arr, int len, int target, int *returnSize, int **returnColumnSizes)
{
    int *stack = (int *)malloc(sizeof(int) * LEN); // 这个栈的作用就是保留遍历的符合target的元素。
    int stack_index = 0;
    int **ret = (int **)malloc(sizeof(int *) * LEN);
    int ret_index = 0;
    int *ret_size = (int *)malloc(sizeof(int) * LEN);
	memset(ret_size, 0, sizeof(int) * LEN);
    *returnColumnSizes = ret_size; // 它指向一段内存。

    rec(arr, len, 0, stack, &stack_index, target, ret, &ret_index, ret_size);

    printf("ret_index = %d %d %d %d\n", ret_index, *ret_size, *(ret_size + 1), *(ret_size + 2));
	printf("returnColumnSizes = %d %d %d\n", *(*returnColumnSizes), *(*returnColumnSizes + 1), *(*returnColumnSizes + 2));

    *returnSize = ret_index;
    free(stack);
    return ret;
}

int main(void)
{
    int** ret = NULL;
    int returnSize = 0;
    int* returnColumSize = NULL;
    int arr[] = {2,3,6,7};
    int target = 7;
	int i;
	int j;

    ret = (int** )malloc(sizeof(int*) * LEN);
    if (ret == NULL) {
        return -1;
    } 
    *ret = (int*)malloc(sizeof(int) * LEN);
    if (*ret == NULL) {
        return -1;
    }
    memset(*ret, 0, sizeof(int) * LEN);
	returnColumSize = (int*)malloc(sizeof(int) * LEN);
    ret = combinationSum(arr, sizeof(arr) / sizeof(arr[0]), target, &returnSize, &returnColumSize);
	printf("\r\nreturnsize=%4d\r\n", returnSize);
	printf(" \r\n%4d %4d %4d\r\n", returnColumSize[0], returnColumSize[1], returnColumSize[2]);
#if 1
    for (i = 0; i < returnSize; i++) {
        for (j = 0; j < returnColumSize[i]; j++) {
            printf("%4d", *(*(ret + i) + j));
        }
        printf("\r\n");
    }
#endif
    system("pause");
}


//另一种解法
/**
 * 回溯法经典解题
 */
int calcuSum(int* data, int counter)
{
    int sum = 0;
    for (int i = 0; i < counter; i++) {
        sum += data[i];
    }
    return sum;
}

void backtrace(int* candidates, int candidatesSize, int pos, int target, int curSum, int* tmpSaveAns, int* tmpCounter,       int**res, int* returnSize, int* returnColumnSizes) 
{
    if (curSum > target) {
        return; // 异常退出。
    }
    if (curSum == target) {
        res[(*returnSize)] = (int*)malloc(sizeof(int) * (*tmpCounter));
        memset(res[*returnSize], 0, sizeof(int) * (*tmpCounter));
        returnColumnSizes[*returnSize] = *tmpCounter;
        memcpy(res[*returnSize], tmpSaveAns, sizeof(int) * (*tmpCounter));
        (*returnSize)++;
        return;
    }
    for (; pos < candidatesSize; pos++) {// 这里的循环有技巧，如果每次都是从i = 0 开始，也能够得到排列，但是会有重复的排列，即一个排列中元素一样，只是顺序不一样。
        tmpSaveAns[(*tmpCounter)++] = candidates[pos];
        curSum = calcuSum(tmpSaveAns, (*tmpCounter));
        backtrace(candidates, candidatesSize, pos, target, curSum, tmpSaveAns, tmpCounter, res, returnSize, returnColumnSizes);
        (*tmpCounter)--;
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes){
    int** result = NULL;
    result = (int**)malloc(sizeof(int*) * 10000);
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * 10000);
    int* tmpSaveAns = (int*)malloc(sizeof(int) * 10000);
    int tmpCounter = 0;
    *returnSize = 0;
    backtrace(candidates, candidatesSize, 0, target, 0, tmpSaveAns, &tmpCounter, result, returnSize, (*returnColumnSizes));
    return result;
}
