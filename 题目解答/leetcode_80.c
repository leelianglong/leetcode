
#include <stdio.h>
#include <stdlib.h>


//这里是删除重复的数字
int removeDuplicates1(int* nums, int numsSize){
    int i;
    int j = 0;
    if (nums == NULL || numsSize == 0) {
        return 0;
    }
    for (i = 1; i < numsSize; i++) {
        if (nums[i] != nums[j]) { //当不等的时候，i 和 j 都在增加；相等的时候i再增加 j则停止，当下次不等的时候，刚好把i对应的值赋值给j对应的值，巧妙的删除重复的。
            j++;
            nums[j] = nums[i];
        }
    }
    return j+1;
}

//这里是删除重复超过2次的数字。
/*
下面算法关键点：
1、这里设置 counter 和 i 分成2条线索遍历；
2、一开始 如果counter和i对应的数字相等的化，就是把自己赋值给自己，并置一个标志位。并把counter 和 i 自增。
3、接下来，如果还是相等的，按照要求，就是要删除的。本算法中，就不去赋值，而是把i 自增了。counter保持不变
4、接下来，如果遇到不相等的，则把i 对应的数字 赋值给 ++counter 对应的数字，达到删除 3）中重复数字的目的。
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