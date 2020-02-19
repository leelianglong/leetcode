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
 ����Ľⷨ���߽�ֵû�д���á���������һ�ֱ߽�ֵ�Ĵ���˼·����һ��������ͳһʹ�üӷ���������
 ����ⷨ�����ڱ���ʱֱ��ȡ�������� �� ż���������������α�����������������ż�����������������������⡣
 ����Ҳ�ͱ����˹���߽�ֵ�Ĵ���
 ����ʹ��2��forѭ������ԭ����ÿ��forѭ������һ�ֹ���
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
            if (tmp[i] < tmp[i + 1]) { //��ǰż������С�����ڵĲ�����
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
            if (tmp[i] > tmp[i + 1]) { //��ǰż�������������ڵĲ�����
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