#include <stdio.h>

static int A() {
	static unsigned long long value = 703;
	do value = value * 16807 % 2147483647; while (value % 4 != 0);
	return value;
}

static int B() {
	static unsigned long long value = 516;
	do value = value * 48271 % 2147483647; while (value % 8 != 0);
	return value;
}

int main() {
	unsigned sum = 0;
	for (int i = 0; i < 5000000; i++)
		sum += (unsigned short)A() == (unsigned short)B();
	printf("%d\n", sum);
}
