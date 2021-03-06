/*
给你一个整数 n 。请你先求出从 1 到 n 的每个整数 10 进制表示下的数位和（每一位上的数字相加），然后把数位和相等的数字放到同一个组中。

请你统计每个组中的数字数目，并返回数字数目并列最多的组有多少个.
例如1：
输入：n = 13
输出：4
解释：总共有 9 个组，将 1 到 13 按数位求和后这些组分别是：
[1,10]，[2,11]，[3,12]，[4,13]，[5]，[6]，[7]，[8]，[9]。总共有 4 个组拥有的数字并列最多。

例如2：
输入：n = 2
输出：2
解释：总共有 2 个大小为 1 的组 [1]，[2]
*/

/*
思路：
本题一开始我列举了100以内的数据，试图找到规律，但是没有找到。
换一种思路，通过hash来解决，1-----10000的数，他们的数位和只有 36 种，最大的数字和是36（由9999得到），最小的是1。
所以定义一个hashtable， 把n个数通过它们的数位和，映射到这个table上。
然后遍历这个table，找到某个位数和并列最大值，方法是：
1、先认为数位和是1的并列个数最多，设为max，并计数counter=1
2、如果下面的数位和是max的，就把counter加1
3、如果遇到的数位和比max还大的话，就把counter置位 1，重新开始。之所以能这样的原因是，越到后面数位和越大，能和它相等的数会更少，所以最多的并列和
一定出现在中间的某个数位和上。
*/


int bitSum(int n)
{
    int res = 0;
    
    while (n) {
        res += n % 10;
        n /= 10;
    }
    return res;
}

int countLargestGroup(int n){
    int hashSum[37] = {0}; //最大的位数和是36
    int i;
    for (i = 1; i <= n; i++) {
        hashSum[bitSum(i)]++;
    }
    
    int max = 0;
    int counter = 1;
    for (i = 1; i < 37; i++) {
        if (hashSum[i] == max) {
            counter++;
        } 
        
        if (hashSum[i] > max){
            counter = 1;
            max = hashSum[i];
        }
    }
    return counter;
}
