#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static char diag[256][256];

int main() {
	int R = 0;
	while (gets(diag[R]))
		R++;
	int r = 0, c = 0;
	while (diag[r][c] != '|')
		c++;
	int inc = 1;
	int steps = 0;
	while (1) {
		while (1) {
			r += inc;
			steps++;
			if (diag[r][c] == '+') {
				inc = (diag[r][c + 1] == ' ') ? -1 : 1;
				break;
			} else if (isalpha(diag[r][c])) {
				putchar(diag[r][c]);
			} else if (diag[r][c] != '|' && diag[r][c] != '-') {
				printf("\n%d\n", steps);
				exit(0);
			}
		}
		while (1) {
			c += inc;
			steps++;
			if (diag[r][c] == '+') {
				inc = (diag[r + 1][c] == ' ') ? -1 : 1;
				break;
			} else if (isalpha(diag[r][c])) {
				putchar(diag[r][c]);
			} else if (diag[r][c] != '|' && diag[r][c] != '-') {
				printf("\n%d\n", steps);
				exit(0);
			}
		}
	}
}
