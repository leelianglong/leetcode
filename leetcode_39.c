#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* ��������˼·:
* 1������һ����ѭ������Ϊ���ֿ����ظ������Դ�0��ʼ����ѭ����������������:
* 2�����������е�ÿ�����֣�ÿ����һ�����Ͱ�������ַŵ���ջ�У����Ҵ�target�а�������ּ�ȥ
* 3��Ȼ��ͻ��ݣ����´�0��ʼ�������У�ִ��2�Ķ���
* 4�����target����0�ˣ������Ǹ����ˣ����˳����ݣ���ջ��Ԫ��POP�������ӵ�target�У�Ȼ����д�ѭ������һ��ѭ����
*
*/
void rec(int *arr, int len, int index, int *stack, int *stack_index,
         int target, int **ret, int *ret_index, int *ret_size)
{
    if (index >= len || target < 0)
        return;

    /* ������������ӵ����� */
    if (target == 0)
    {
        ret[(*ret_index)] = (int *)malloc(sizeof(int) * (*stack_index));
        ret_size[(*ret_index)] = *stack_index;
		printf("*ret_index = %d %d\r\n", *ret_index, ret_size[(*ret_index)]);
        memcpy(ret[(*ret_index)], stack, (*stack_index) * sizeof(int));
        (*ret_index)++;
        return;
    }

    /* ����ѭ����ע���index��ʼ����Ϊ�����ظ�ʹ����ͬ��Ԫ�� */
    for (; index < len; index++)
    {
        target -= arr[index];
        stack[(*stack_index)++] = arr[index];

        rec(arr, len, index, stack, stack_index, target, ret, ret_index, ret_size);

        (*stack_index)--; // Ҫִ�е����һ���Ǵ�target�˳��Ż���������һֱ�ٵ���rec.
        target += arr[index]; // �����ǰ��ϴ���ӵ���ջ�У���������֮�Ͳ�����target���Ǹ����������㵽target�ϡ�����������ѭ����index����1��
    }
}

#define LEN 0xffff

int **combinationSum(int *arr, int len, int target, int *returnSize, int **returnColumnSizes)
{
    int *stack = (int *)malloc(sizeof(int) * LEN); // ���ջ�����þ��Ǳ��������ķ���target��Ԫ�ء�
    int stack_index = 0;
    int **ret = (int **)malloc(sizeof(int *) * LEN);
    int ret_index = 0;
    int *ret_size = (int *)malloc(sizeof(int) * LEN);
	memset(ret_size, 0, sizeof(int) * LEN);
    *returnColumnSizes = ret_size; // ��ָ��һ���ڴ档

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