/*
* 给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一,最高位数字存放在数组的首位， 数组中每个元素只存储单个数字
*/

/*
* 思路1：
* 该问题起初我采用数值的形式，即把数组元素转出整形数字， sum = sum * 10 + digits[i]; 然后在把sum转换成字符，然后在返回。
* 这里存储sum的数据类型不够用，long long 类型的都会溢出。
* 思路2：
* 直接找到最后的元素digits[digitsSize - 1] + 1, 注意进位。一边计算一边放在返回的数组中。最后把返回数组逆序一下。
*/

/* 思路2 代码*/
int* plusOne(int* digits, int digitsSize, int* returnSize){
    *returnSize = 0;
    int* result = (int*)malloc(sizeof(int) * (digitsSize + 1));
    memset(result, 0, sizeof(int) * (digitsSize + 1));
    digits[digitsSize - 1] += 1;
    for (int i = digitsSize - 1; i > 0; i--){
        if (digits[i] > 9) {
            digits[i] = 0;
            digits[i - 1] += 1;
        }
        result[*returnSize] = digits[i];
        (*returnSize)++;
    }
    if (digits[0] > 9) {
        result[(*returnSize)++] = 0;
        result[(*returnSize)++] = 1;
    }
    int left = 0;
    int right = *returnSize - 1;
    while (left <= right) {
        int tmp = result[left];
        result[left] = result[right];
        result[right] = tmp;
        left++;
        right--;
    }
    printf("\nsize=%d\n", *returnSize);
    for (int i = 0; i < *returnSize; i++) {
        printf("%d ", result[i]);
    }
    return result;
}
/*
*上面的优化点： 
* 1、实际上从最后一位开始，只要没有进位时，就可以结束了，没必要遍历所有。
* 2、在存储数据时，也每必要另起一个变量，直接用 i,也是可以的。
*/

/*
* 题解中的优秀算法
*/
int* plusOne(int* digits, int digitsSize, int* returnSize){
    int     i           = 0;
    int     iTmp        = 1;
    int*    pRet        = NULL;

    if ((NULL == digits) || (0 == digitsSize))
    {
        *returnSize = 0;
        return pRet;
    }

    pRet = (int*)malloc(sizeof(int) * (digitsSize + 1));
    memset(pRet, 0x00, sizeof(int) * (digitsSize + 1));

    for (i = digitsSize; i > 0; i--)
    { 
        pRet[i] = (digits[i - 1] + iTmp) % 10;
        iTmp = (digits[i - 1] + iTmp) / 10;
    }
    pRet[0] = iTmp;

    if (pRet[0] == 0)
    {
        *returnSize = digitsSize;
        return &pRet[1];
    }
    else
    {
        *returnSize = digitsSize + 1;
        return &pRet[0];
    }
}

作者：r0vHWU5AdJ
链接：https://leetcode-cn.com/problems/plus-one/solution/chun-cjia-yi-chu-li-si-lu-qing-xi-dai-ma-yi-du-by-/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
