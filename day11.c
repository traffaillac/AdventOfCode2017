#include <assert.h>
#include <stdio.h>

static int max(int a, int b) { return a > b ? a : b; }
static int dist(int x, int y) {
	if (x >= 0 && y >= 0)
		return max(x, y);
	if (x <= 0 && y >= 0)
		return y - x;
	if (x <= 0 && y <= 0)
		return max(-x, -y);
	return x - y;
}

int main() {
	int x = 0, y = 0, furthest = 0, c1, c2;
	do {
		c1 = getchar();
		c2 = getchar();
		if (c1 == 's' && c2 == 'w') {
			x--;
			y--;
			c2 = getchar();
		} else if (c1 == 's' && c2 == 'e') {
			x++;
			c2 = getchar();
		} else if (c1 == 'n' && c2 == 'w') {
			x--;
			c2 = getchar();
		} else if (c1 == 'n' && c2 == 'e') {
			x++;
			y++;
			c2 = getchar();
		} else if (c1 == 's') {
			y--;
		} else {
			assert(c1=='n');
			y++;
		}
		furthest = max(furthest, dist(x, y));
	} while (c2 == ',');
	printf("%d\n", furthest);
}
