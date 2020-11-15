/*
* 题目要求删除最少的字符，使其平衡，平衡的意思是要求最终的字符串是 aaaabbbb这种形式。
* 思路：
* 1、从左向右遍历字符串，当遇到b时，就需要删除一次（变成完全的aaaa字符串）
* 2、从右向左遍历字符串，当遇到a时，删除一次（变成完全的bbbb）
* 3、使用2个数组来记录1和2中删除的次数，然后把0到strlen(s)（要包括这个长度）的长度范围内，把1、和 2中的数字加起来，求出最小的和。
*/

int minimumDeletions(char * s){
    int pre[100001] = {0};
    for (int i = 0; i < strlen(s); i++) {
        pre[i + 1] = pre[i];
        if (s[i] == 'b') {
            pre[i + 1]++;
        }
    }
    int suf[100001] = {0};
    for (int j = strlen(s) - 1; j >= 0; j--) {
        suf[j] = suf[j + 1];
        if (s[j] == 'a') {
            suf[j]++;
        }
    }
    int res = 1e9;
    for (int i = 0; i <= strlen(s); i++) {
        res = res > (pre[i] + suf[i]) ? (pre[i] + suf[i]) : res;
    }
    return res;
}
