#include <stdio.h>
#include <stdlib.h>

/*
    ����һ����������A������ĳ��Ԫ����ת�Ժ�õ�������B������һ��Ԫ��target
    ��B�����в��ң��Ƿ�������targetֵ��
    ˼·��
    ����������֮ǰ��������ֻ���õ������������У�������ת��������ֱ��Ӧ�ò������á� 
    ����м����С�����ұߵ��������Ұ��������ģ����м����������ұ�����������������ģ�����ֻҪ������İ��������β�����������ж�Ŀ��ֵ�Ƿ�����һ�����ڡ�
*/
int search(int* nums, int numsSize, int target){
    int start = 0;
    int end = numsSize - 1;
    int mid;

    if (nums == NULL || numsSize <= 0) {
        return -1;
    }

    while (start <= end) {
        mid = start + ((end - start) >> 1);  //���ֲ���ʹ���������mid�������
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] >= nums[end]) { //�м�����������ұߵ�����˵����벿��������ġ�
            if (target >= nums[start] && nums[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        } else if (nums[mid] < nums[end]) { //�м����С�����ұߵ�����˵���Ұ벿���������
            if (target <= nums[end] && nums[mid] < target) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        } 
    }
    return -1;
}


int main(void)
{
    int test[] = {3,1};//{4,5,6,7,0,1,2};
    int result;
    result = search(test, 2, 0);
    printf("\r\nresult=%4d\r\n", result);
    system("pause");
}