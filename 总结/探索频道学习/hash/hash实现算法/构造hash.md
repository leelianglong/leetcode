1、通过2次qsort 来实现hash的特性。

问题现象： 对于一组无序的数字，要对它们的出现的频率做相关处理时，可以首先使用qsort,把相同的数字先放在一起，然后再计算所有相同的数字的出现次数，接下来

对出现的频率再做qsort. 最后在根据题目要求，做一些处理。


### leetcode 1481

### 代码
```
int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int findLeastNumOfUniqueInts(int* arr, int arrSize, int k){
    qsort(arr, arrSize, sizeof(int), cmp);
    int counter = 0;
    int freq[100001] = {0};
    int number = arr[0];
    for (int i = 0; i < arrSize; i++) {
        if (number == arr[i]) {
            freq[counter]++;
            continue;
        }
        counter++;
        freq[counter]++;
        number = arr[i];
    }
    counter++; // 这里还要加1的原因，下面基于counter 循环，或者排序，counter最初从0开始计算。
    
    
    qsort(freq, counter, sizeof(int), cmp);
    int result;
    if (k == 0) {
        return counter;
    } else if (k == arrSize) {
        return 0;
    } else {
        int sum = k;
        result = counter;
        int m;
        for (m = 0; m < counter; m++) {
            if (freq[m] < sum) {
                sum -= freq[m];
                result--;
            } else if (freq[m] == sum) { // 下面相减的技巧性
                result--;
                break;
            } else {
                break;
            }
        }
    }
    return result;
}
```
