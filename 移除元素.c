#include <stdio.h>
#include <stdlib.h>


/* 
����͵�ɾ��ָ��Ԫ�ص��㷨��
1��ʹ��2��ָ�룬��һ�����ڱ���ԭ�������飻�ڶ������ڱ��������ɵ�����
2�����ȴ�ԭ���鿪ʼ�����ԭ�����е�ֵ����ָ��Ҫɾ����Ԫ�أ���ԭ�����е�ֵ�������µ�������
3�����ԭ�����е�ֵ��Ҫɾ����ֵ�������ԭ�����ָ�����ӣ������������������ָ�벻�䡣
4��������һ������ԭ�����е�ֵ����Ҫɾ����Ԫ��ʱ������ֵ�������µ������С������µ������о�û���Ǹ�ָ����Ԫ��ֵ��
*/

int RemoveElement(int* data, int dataSize, int val)
{
    int i;
    int j = 0;;
    for (i = 0; i < dataSize; i++) {
        if (data[i] != val) {
            data[j] = data[i];
            j++;
        }
    }
    return j;
}


// ����ԭ��ȥ����ͬ��Ԫ��
int RemoveReeatElement(int* data, int dataSize)
{
    int i;
    int j = 0;

    for (i = 1; i < dataSize; i++) {
        if (data[i] != data[j]) { //ע��������˫ָ��ıȽϣ��� i he j�ıȽ�
			j++;
            data[j] = data[i];
        }
    }
    return j + 1;
}


int main(void)
{
    int data [10] = { 1,1,2};
    RemoveReeatElement(data, 3);
	printf("\r\nover\r\n");
}