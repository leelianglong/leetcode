### leetcode 66
1. 给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一,最高位数字存放在数组的首位， 数组中每个元素只存储单个数字

### 思路：
* 思路1：
* 该问题起初我采用数值的形式，即把数组元素转出整形数字， sum = sum * 10 + digits[i]; 然后在把sum转换成字符，然后在返回。
* 这里存储sum的数据类型不够用，long long 类型的都会溢出。
* 思路2：
* 直接找到最后的元素digits[digitsSize - 1] + 1, 注意进位。一边计算一边放在返回的数组中。最后把返回数组逆序一下
---

### 代码
```
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
```

### 代码2

* 大数相加的优秀实践

### 代码
```
int* plusOne(int* digits, int digitsSize, int* returnSize){
    int* res = (int*)calloc(digitsSize + 1, sizeof(int));
    *returnSize = 0;

    int inc = 1;  // 加1提前执行
    int cnt = 0;
    for (int i = digitsSize; i > 0; i--) { // 注意倒序计算
        res[i] = (digits[i - 1] + inc) % 10; // res[i]真实存储的数据，inc是低位加1的进位数据。
        inc = (digits[i - 1] + inc) / 10; // inc 只存储进位的。
    } 
    res[0] = inc;// 存储最终的进位。如果没有进位的时候，这里是0.
    if (res[0] == 0) {
        *returnSize = digitsSize;
        return &res[1];
    } 
    *returnSize = digitsSize + 1;
    return res;
}
```