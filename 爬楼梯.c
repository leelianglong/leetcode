/*
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
*/
int climbStairs(int n){
	int a = 1; //这是只有1层楼梯时
	int b = 2; //这是只有2层楼梯时 以上2种是边界值。
	int steps = 0;
	int i = 0;
	if (n < 1) {
		return 0;
	}
	if (n == 1 || n == 2) {
		steps = n; 
	}
	for (i = 3; i <= n; i++) {
		steps = a + b;//递推公式  f(n) = f(n-1) + f(n-2)
		a = b; 
		b = steps;
	}
	return steps;
}
