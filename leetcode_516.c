#include <stdio.h>
#include <stdlib.h>
/*
* 题目思路：
* 1、dp[i][j] 表示字符串从i到j的子串回文长度。
* 2、分2种情况，如果字符串的首尾字符一样，那么子串回文长度就应该加 2; 如果不一样，则选择dp[i+1][j] 或者 dp[i][j - 1]
*    中较大的,即包含首字符的子串回文长度或者尾字符的子串回文长度中的较大者。
* 3、这里2层循环，第一层从左往右，第二层循环则是从起始到第一层循环遍历的地方。找前半部分子串的回文长度
*/

#define MAX_ELEMENT(a,b) (a > b ? a : b)
int dp[1001][1001] = {0};
int longestPalindromeSubseq(char * s){
    if (s == NULL) {
        return 0;
    }
    if (strlen(s) == 1) {
        return 1;
    }
    int i;
    int j;
    for (j = 1; j < strlen(s); j++) {
        dp[j][j] = 1;
        for (i = j - 1; i >= 0; i--) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = MAX_ELEMENT(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][strlen(s) - 1];
}