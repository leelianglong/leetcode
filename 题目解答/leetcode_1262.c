
/*
本题采用数学方法，一个数被3整除有3中结果：1、即能够被整除；2、余数是1； 3、余数是2；
1、本题中如果能够整除，则直接返回数列总和就是最大整除数列和
2、如果总和余数是1，则分2种情况来处理，使其能够被整除：
   2.1、即从原来数据中找到最小的能够被3整除余1的数据，总和减去该数据
   2.2、如果原来数据中有超过2个的数据（如果没有这样的2个数，则可以直接返回2.1结果），能够本3整除余2的，则可以使其总和 减去 这2个数的和
   2.3、选择2.1 和 2.2 中的较大值作为结果返回
3、如果总和余数是2，则分2种情况来处理，使其能够被整除：
   3.1、即从原来数据中找到最小的能够被3整除余2的数据，总和减去该数据
   3.2、如果原来数据中有超过2个的数据（如果没有这样的2个数，则可以直接返回3.1结果），能够本3整除余1的，则可以使其总和 减去 这2个数的和
   3.3、选择3.1 和 3.2 中的较大值作为结果返回
*/
int cmp(const void* a, const void* b)
{
    int aa = *(int*)a;
    int bb = *(int*)b;
    return aa - bb;
}

int maxSumDivThree(int* nums, int numsSize){
    if (numsSize == 0) {
        return 0;
    }
    int sum = 0;
    int* mod2 = (int*)malloc(sizeof(int) * numsSize);
    memset(mod2, 0, sizeof(int) * numsSize);
    int* mod1 = (int*)malloc(sizeof(int) * numsSize);
    memset(mod1, 0, sizeof(int) * numsSize);
    int counter1 = 0;
    int counter2 = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        if (nums[i] % 3 == 1) {
            mod1[counter1++] = nums[i];
        } else if (nums[i] % 3 == 2) {
            mod2[counter2++] = nums[i];
        }
    }
    qsort(mod1, counter1, sizeof(int), cmp);
    qsort(mod2, counter2, sizeof(int), cmp);

    int result = -1;
    int tmpSum1 = sum;
    int tmpSum2 = sum;
    if (sum % 3 == 0) {
        return sum;
    } else if (sum % 3 == 1) {
        tmpSum1 -= mod1[0];
        result = tmpSum1 > result ? tmpSum1 : result;
        if (counter2 > 1) {
            tmpSum2 = tmpSum2 - mod2[0] - mod2[1];
            result = tmpSum2 > result ? tmpSum2 : result;
        }
    } else if (sum % 3 == 2) {
        tmpSum1 -= mod2[0];
        result = tmpSum1 > result ? tmpSum1 : result;
        if (counter1 > 1) {
            tmpSum2 = tmpSum2 - mod1[0] - mod1[1];
            result = tmpSum2 > result ? tmpSum2 : result;
        }
    }
    return result;
}
