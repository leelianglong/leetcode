/*
* 该题目的核心技巧就是把原数列大小关系转存到一个数组中，遍历这个数组来计数符合要求的个数。
* 大小关系用正负 1来表示，如果交替的话，他们的乘积就小于0，这样来比较比是否小于0，比直接比较大小更方便。
*/

int maxTurbulenceSize(int* A, int ASize){
    if (ASize == 1) {
        return 1;
    }
    char* releationship = (char*)malloc(sizeof(char) * (ASize - 1));
    memset(releationship, 0, sizeof(char) * (ASize - 1));
    for (int i = 0; i < ASize - 1; i++) {
        if (A[i] > A[i + 1]) {
            releationship[i] = 1;
        } else if (A[i] < A[i + 1]) {
            releationship[i] = -1;
        } else {
            releationship[i] = 0;
        }
    }
    int k;
    for (k = 0; k < ASize - 1; k++) {
        if (releationship[k] != 0) {
            break;
        }
    }
    if (k == ASize - 1) {
        return 1;
    }
    int max = 0; //在比较大小max的初值看情况，本题最小的应该是0，没有这样的数，所以没必要设置成INT_MAX。
    int counter = 0;
    for (int j = 0; j < ASize - 2; j++) {
        if (releationship[j] * releationship[j + 1] < 0) {
            counter++;
            max = max > counter ? max : counter;
        } else {
            counter = 0;
        } 
    }
    return max + 2; /* 只有满足一个releationship【j】和 【j + 1】相乘为负数，就表示有3个数字满足条件 */
}
