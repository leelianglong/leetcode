char** result = NULL;
void step(int left, int right, char* res, int* top, int* returnSize, int n)
{
    if (left < 0 || right < 0 || left > right) {
        return; // 异常情况要结束
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
