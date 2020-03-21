#include <stdio.h>
#include <stdlib.h>


/* 
数组就地删除指定元素的算法：
1、使用2个指针，第一个用于遍历原来的数组；第二个用于遍历新生成的数组
2、首先从原数组开始，如果原数组中的值不是指定要删除的元素，则将原数组中的值拷贝到新的数组中
3、如果原数组中的值是要删除的值，则遍历原数组的指针增加，而遍历新生成数组的指针不变。
4、这样下一次遇到原数组中的值不是要删除的元素时，将该值拷贝到新的数组中。这样新的数组中就没有那个指定的元素值。
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


// 数组原地去除相同的元素
int RemoveReeatElement(int* data, int dataSize)
{
    int i;
    int j = 0;

    for (i = 1; i < dataSize; i++) {
        if (data[i] != data[j]) { //注意这里是双指针的比较，即 i he j的比较
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