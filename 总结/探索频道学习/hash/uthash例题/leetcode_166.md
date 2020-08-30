### 题目 leetcode 166

题目要求将分数转换成小数。如果出现循环小数，则使用括号将循环节扩起来

思路： 

1、先处理整数部分的除法，在处理余数部分的除法。

2、余数部分除法的处理：商 = 余数 * 10 / 10，下一次的被除数，则是刚才计算的余数 * 10 % 10. 直到这个被除数为 0.

3、这里有循环，那么我们要记录小数部分每一位在最终字符串的位置，当出现重复时，则表示遇到循环了。

4、把小数部分向后移动以为，在"."后面添加一个"(" 在小数部分最后添加")"。

注意：

对于int求绝对值，可以使用abs(a), 对于long long 类型的数据，求绝对值可以使用 llabs().

### 代码
```
struct HashMap {
    int key;
    int pos;
    UT_hash_handle hh;
};

struct HashMap* users;

int AddValToHash(int key, int pos) {
    struct HashMap* find;
    int hashKey = key;
    HASH_FIND_INT(users, &hashKey, find);
    if (find != NULL) {
        return find->pos;
    }
    struct HashMap* add;
    add = (struct HashMap*)malloc(sizeof(struct HashMap));
    add->key = key;
    add->pos = pos;
    HASH_ADD_INT(users, key, add);
    return -1;
}

#define RETURN_SIZE 1024

char * fractionToDecimal(int numerator, int denominator){
    if (numerator == 0) {
        return "0";
    } 
    if (denominator == 0) {
        return "";
    }
    users = NULL;
    char* result = (char*)malloc(sizeof(char) * RETURN_SIZE);
    memset(result, 0, sizeof(char) * RETURN_SIZE);
    long long num = numerator;
    long long den = denominator; // 注意转换成 long long 
    num = llabs(num);
    den = llabs(den);
    if (numerator > 0 && denominator < 0  || numerator < 0 && denominator > 0) {
        sprintf(result, "-%ld", num / den);
    } else {
        sprintf(result, "%ld", num / den);
    }
    int pos = strlen(result); 
    long long fator = num % den; // 注意转换成 long long。
    int start = 0;
    if (fator) {
        result[pos++] = '.';
        while (fator && (start = AddValToHash(fator, pos)) == -1 ) {
            result[pos++] = fator * 10 / den + '0';
            fator = fator * 10 % den;
        }
        printf("\n%d", start);
        if (start != -1) {
            // 说明是除完了
            for (int j = pos++; j > start; j--) {
                result[j] = result[j-1];
            }
            result[start] = '(';
            result[pos] = ')';
        }
    }
    result[++pos] = '\0';
    return result;
}
```
