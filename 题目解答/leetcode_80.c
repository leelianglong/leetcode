
#include <stdio.h>
#include <stdlib.h>


//������ɾ���ظ�������
int removeDuplicates1(int* nums, int numsSize){
    int i;
    int j = 0;
    if (nums == NULL || numsSize == 0) {
        return 0;
    }
    for (i = 1; i < numsSize; i++) {
        if (nums[i] != nums[j]) { //�����ȵ�ʱ��i �� j �������ӣ���ȵ�ʱ��i������ j��ֹͣ�����´β��ȵ�ʱ�򣬸պð�i��Ӧ��ֵ��ֵ��j��Ӧ��ֵ�������ɾ���ظ��ġ�
            j++;
            nums[j] = nums[i];
        }
    }
    return j+1;
}

//������ɾ���ظ�����2�ε����֡�
/*
�����㷨�ؼ��㣺
1���������� counter �� i �ֳ�2������������
2��һ��ʼ ���counter��i��Ӧ��������ȵĻ������ǰ��Լ���ֵ���Լ�������һ����־λ������counter �� i ������
3�������������������ȵģ�����Ҫ�󣬾���Ҫɾ���ġ����㷨�У��Ͳ�ȥ��ֵ�����ǰ�i �����ˡ�counter���ֲ���
4���������������������ȵģ����i ��Ӧ������ ��ֵ�� ++counter ��Ӧ�����֣��ﵽɾ�� 3�����ظ����ֵ�Ŀ�ġ�
*/
int removeDuplicates(int* nums, int numsSize){
    int i;
    int flag = 0;
    int counter = 0;
    if (nums == NULL || numsSize == 0) {
        return 0;
    }
    
    for (i = 1; i < numsSize; i++) {
        if (nums[counter] != nums[i]) {
            nums[++counter] = nums[i];
            flag = 0;
        } else if (nums[counter] == nums[i] && !flag) {
            nums[++counter] = nums[i];
            flag = 1;
        } 
    }

    return ++counter;
}

int main(void)
{
    int test[] = {0,0,1,1,1,1,2,3,3};
    int result = removeDuplicates(test, sizeof(test) / sizeof(test[0]));
    printf("\r\nresult=%u\r\n", result);
    system("pause");
}