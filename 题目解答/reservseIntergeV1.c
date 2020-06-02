#include<stdio.h>
#include<stdlib.h>

/*
int 型数据范围：2^31 = 2147483648
*/

// sprintf_s 格式化后带了字符串结束符，所以buff要多一个字节。
void FormatInterge(char* const dst, int num, int size)
{
	sprintf_s(dst, size, "%d", num);
}

void ChangefromCharToInt(char* src, int* dst, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		dst[i] = src[i] - 0x30;
	}
}

int CalculateNumberBit(int x)
{
	int i = 0;
	do {
		x = x / 10;
		++i;
	} while (x);
	return i;
}

void reserve(int n, int* dst)
{
	int i = 0;
	do {
		dst[i] = n % 10;
		n /= 10;
		i++;
	} while (n != 0);
}

int ReserveIntNumber(const int* buff, int size)
{
	int i = 0;
	int tmp = buff[0];
	int sum = tmp;
	int factor = 1;
	for (i = 1; i < size; i++) {
		factor *= 10;
		sum = sum + buff[i] * factor;
		if (sum < 0)
			return 0;
	}
	return (int)sum;
}

int CalculateNum(int* buff, int size)
{
	int i;
	long long sum = 0;
	for (i = 0; i < size; i++) {
		sum = sum * 10 + buff[i];
		if (sum > 2147483647) {
			return 0;
		}
	}
	return sum;
}

int ReserveProcess(int x)
{
	char src[12] = { 0 };
	int dst[12] = { 0 };
	int flg = 0; // 0，表示正数； 1 表示负数
	flg = x >= 0 ? 0 : 1;

	if (flg == 1) {
		x = -x;
	}
	int bitNum = CalculateNumberBit(x);
	//FormatInterge(src, x, bitNum + 1);
	reserve(x, dst);
	//ChangefromCharToInt(src, dst, bitNum);
	//int result = ReserveIntNumber(dst, bitNum);
	int result = CalculateNum(dst, bitNum);
	return flg > 0 ? -result : result;
}

int main(void)
{
	char a1[6] = { 1,2,3,4,5,6 };
	char a2[6] = { 0 };
	int a3[5] = { 1,2,3,4,5 };
	int num = 1534236469;

	FormatInterge(a2, 12345, 6);
	printf_s("\r\n%s", a2);
	printf_s("\r\n bit=%d", CalculateNumberBit(1234));
	printf_s("\r\n num =%d", ReserveIntNumber(a3, 5));
	printf_s("\r\nfinal = %d", ReserveProcess(num));
}

