#include <stdio.h>
#include <string.h>

/* Manage elements in sets (begin with a -1 initialised array). */
static int  Set_find(short* set, int i) { return (set[i] < 0) ? i : (set[i] = Set_find(set, set[i])); }
static int  Set_test(short* set, int i, int j) { return (Set_find(set, i) == Set_find(set, j)); }
static int  Set_card(short* set, int i) { return -set[Set_find(set, i)]; }
static void Set_union(short* set, int i, int j) {
	int a = Set_find(set, i), b = Set_find(set, j), c;
	if (a != b) {
		if (set[a] > set[b])
			c = a, a = b, b = c;
		set[a] += set[b], set[b] = a;
	}
}

int main() {
	short set[2000];
	memset(set, -1, sizeof(set));
	int i, j;
	while (scanf("%d <-> %d", &i, &j) == 2)
		do Set_union(set, i, j); while (scanf(", %d", &j) == 1);
	int sum = 0;
	for (int i = 0; i < 2000; i++)
		sum += set[i] < 0;
	printf("%d\n", sum);
}
