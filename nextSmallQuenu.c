/*
实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须原地修改，只允许使用额外常数空间。

以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/



#include <stdio.h>
#include <stdlib.h>

/*
插入排序：当遍历到i时前面的a[0],a[1]...a[i-1]都是排好序的，现在取出a[i],
插入到前面0---i-1个位置中的合适位置。
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
冒泡排序，两两比较，把最大的放到后面。
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