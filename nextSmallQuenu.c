/*
ʵ�ֻ�ȡ��һ�����еĺ������㷨��Ҫ���������������������г��ֵ�������һ����������С�

�����������һ����������У��������������г���С�����У����������У���

����ԭ���޸ģ�ֻ����ʹ�ö��ⳣ���ռ䡣

������һЩ���ӣ�����λ������У�����Ӧ���λ���Ҳ��С�
1,2,3 �� 1,3,2
3,2,1 �� 1,2,3
1,1,5 �� 1,5,1

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/next-permutation
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/



#include <stdio.h>
#include <stdlib.h>

/*
�������򣺵�������iʱǰ���a[0],a[1]...a[i-1]�����ź���ģ�����ȡ��a[i],
���뵽ǰ��0---i-1��λ���еĺ���λ�á�
*/
void InsertSort(int* src, int num)
{
    int i, j,tmp;
    for (i = 1; i < num; i++) {
        tmp = src[i];
        for (j = i - 1; j >= 0 && tmp < src[j]; j--) {
            src[j+1] = src[j];
            src[j] = tmp;
        }
    }
}

/*
ð�����������Ƚϣ������ķŵ����档
*/

void BubbleSort(int* src, int num)
{
    int i, j, tmp;
    for (i = 0; i < num; i++) {
        for (j = 0; j < num; j++) {
            if (src[j] < src[j - 1]) {
                tmp = src[j];
                src[j] = src[j - 1];
                src[j - 1] = tmp;
            }
        }
    }
}

int main(void)
{
    int i;
    int arra[6] = { 6,5,4,3,2,1 };
   // InsertSort(arra, 6);
    //BubbleSort(arra, 6);
    for (i = 0; i < 6; i++) {
        printf("%2d", arra[i]);
    }
    return 0;
}