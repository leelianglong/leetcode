#include <stdio.h>
#include <stdlib.h>
/*
* ��Ŀ˼·��
* 1��dp[i][j] ��ʾ�ַ�����i��j���Ӵ����ĳ��ȡ�
* 2����2�����������ַ�������β�ַ�һ������ô�Ӵ����ĳ��Ⱦ�Ӧ�ü� 2; �����һ������ѡ��dp[i+1][j] ���� dp[i][j - 1]
*    �нϴ��,���������ַ����Ӵ����ĳ��Ȼ���β�ַ����Ӵ����ĳ����еĽϴ��ߡ�
* 3������2��ѭ������һ��������ң��ڶ���ѭ�����Ǵ���ʼ����һ��ѭ�������ĵط�����ǰ�벿���Ӵ��Ļ��ĳ���
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