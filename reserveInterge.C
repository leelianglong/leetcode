#include<stdio.h>
#include<stdlib.h>

/*
int 型数据范围：2^31 = 2147483648
*/

void ReserveArray( char* const src,  char* dst, char buffLength)
{
	int i;
	for (i = 0; i < buffLength; i++) {
		dst[i] = src[buffLength - i - 1];
	}
}

// sprintf_s 格式化后带了字符串结束符，所以buff要多一个字节。
void FormatInterge(char* const dst, int num, int size)
{
	sprintf_s(dst, size, "%d", num);
}

int CalculateNumberBit(int x)
{
	int i = 0;
	do  {
		x = x / 10;
		++i;
	}while (x);
	return i;
}

int CalculateNumber(char* const buff, int size)
{
	int i = 0;
	char tmp = buff[0] - 0x30;
	long long sum = tmp;
	for (i = 1; i < size; i++) {
		sum = 10 * sum + (buff[i] - 0x30);
	}
	if (sum > 2147483647)
		return 0;
	return (int)tmp;
}

// 1234---->4321
int ReserveIntNumber(const int* buff, int size)
{
	int i = 0;
	int tmp = buff[0];
	int factor = 1;
	for (i = 1; i < size; i++) {
		factor *= 10;
		tmp = tmp + buff[i] * factor;
	}
	return tmp;
}


int ReserveProcess(int x)
{
	char src[11] = { 0 };
	char dst[11] = { 0 };
	int flg = 0; // 0，表示正数； 1 表示负数
	flg = x >= 0 ? 0 : 1;

	if (flg == 1) {
		x = -x;
	}
	int bitNum = CalculateNumberBit(x);
	FormatInterge(src, x, bitNum + 1);
	ReserveArray(src, dst, bitNum);
	int result = CalculateNumber(dst, bitNum);
	return flg > 0 ? -result : result;
}

int main(void)
{
	char a1[6] = { 1,2,3,4,5,6 };
	char a2[6] = { 0 };
	int a3[5] = { 1,2,3,4,5 };
	int test = -2147483647;
	ReserveArray(a1, a2, 6);
	for (int i = 0; i < 6; i++) {
		printf_s("%4d", a2[i]);
	}
	FormatInterge(a2, 12345, 6);
	printf_s("\r\n%s", a2);
	printf_s("\r\n bit=%d", CalculateNumberBit(1234));
	printf_s("\r\n number = %d", ReserveIntNumber(a3, 5));
	printf_s("\r\nfinal = %d", ReserveProcess(test));
}

