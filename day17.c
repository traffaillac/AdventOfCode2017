#include <stdio.h>
#include <string.h>

static int next[50000001];
static int N = 1;

int main() {
	int pos = 0;
	for (int i = 1; i <= 50000000; i++) {
		if (i % 1000000 == 0)
			printf("i=%d\n", i);
		for (int j = 0; j <= 304; j++)
			pos = next[pos];
		next[i] = next[pos];
		next[pos] = i;
	}
	printf("%d\n", next[0]);
}
