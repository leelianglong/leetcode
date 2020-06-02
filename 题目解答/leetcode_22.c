/*
* 大致思路就是，从左向右一次放左右括号。
* 回溯法，主要是再一次调用之后，要恢复在调用自身之前设置的数据
* 合法的括号一定是1、左括号数和右括号数相等， 2任意时刻左括号的数量都要大于右括号
*/

char** result = NULL;
void step(int left, int right, char* res, int* top, int* returnSize, int n)
{
    if (left < 0 || right < 0 || left > right) { 
        return; // 异常情况要结束 left > right 表示，左括号剩的比右括号还多，不合法
    }
    if (left == 0 && right == 0) { // 找到完整的括号要结束
        result[(*returnSize)] = (char*)malloc(sizeof(char) * (2 * n + 1));
        memset(result[(*returnSize)], 0, sizeof(char) * (2 * n + 1));
        strncpy(result[(*returnSize)], res, *top);
        (*returnSize)++;
        return; 
    }
    res[(*top)++] = '('; // 把左括号放进去
    step(left - 1, right, res, top, returnSize, n);
    (*top)--; //递归完了要返回上一层，这里把上一层取消,这里也就是出栈

    res[(*top)++] = ')';
    step(left, right - 1, res, top, returnSize, n);
    (*top)--;
}


char ** generateParenthesis(int n, int* returnSize){
    result = (char**)malloc(sizeof(char*) * 20000);
    char* res = (char*)malloc(sizeof(char) * (2 * n + 1));
    int top = 0;
    *returnSize = 0;
    step(n, n, res, &top, returnSize, n);

    return result;
}
