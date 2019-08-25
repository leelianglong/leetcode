#include <stdio.h>
#include <stdlib.h>

int RomanToInt(char* data) {
	int sum = 0;
	if (data == NULL) {
		return 0;
	}
	while (*data != NULL) {
		if (*data == 'M') {
			sum += 1000;
		}
		if (*data == 'D') {
			sum += 500;
		}
		if (*data == 'C') {
			if (*(data + 1) == 'M') {
				sum += 900;
				data++;
			}
			else if (*(data + 1) == 'D') {
				sum += 400;
				data++;
			}
			else {
				sum += 100;
			}
		}
		if (*data == 'L') {
			sum += 50;
		}
		if (*data == 'X') {
			if (*(data + 1) == 'C') {
				sum += 90;
				data++;
			}
			else if (*(data + 1) == 'L') {
				sum += 40;
				data++;
			}else{
				sum += 10;
			}
		}
		if (*data == 'V') {
			sum += 5;
		}
		if (*data == 'I') {
			if (*(data + 1) == 'X') {
				sum += 9;
				data++;
			}
			else if (*(data + 1) == 'V') {
				sum += 4;
				data++;
			}
			else {
				sum += 1;
			}
		}
		data++;
	}
	return sum;
}

int main(void)
{
	char* input = "MCMXCIV";
	printf("result=%4d", RomanToInt(input));
}