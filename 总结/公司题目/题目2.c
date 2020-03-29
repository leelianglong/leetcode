题目描述
某公司推出了一种保险箱，支持 4 位数字密码，开锁时每次操作改变密码盘上其中任意 1 位数字。（注意，是改变，数字可以跳变；比如1111 操作1次后，可以直接变成 5111）
与普通的保险箱不同的是，该保险箱显示的数字，必须始终是素数。

现给定保险箱初始显示的数字与目的解锁密码（都是素数，包含前导 0，即小于 10000 的素数），请找出最快的开锁方式（改变密码盘次数最少），输出密码盘改变次数，如果无法解锁，输出 -1。

解答要求
时间限制：1000ms, 内存限制：256MB
输入
只有1行，分别是密码锁初始状态及最终目的状态，均为4位数字组成，单个空格分隔

输出
输出最少操作次数；无法解锁则输出-1

样例
输入样例 1 复制

0023 0059
输出样例 1

2

输入样例 2 复制

1373 8017
输出样例 2

5

提示
样例1解释：
0023->0059，存在两种开锁方式：0023->0029->0059，或 0023->0053->0059，操作次数都是2

样例2解释：
1373->8017，存在一种开锁方式：1373->0373->0313->0317->8317->8017，需要5次操作

质数，又称素数，指在大于1的自然数中，除了1和该数自身外，无法被其他自然数整除的数。
