#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char perms[32][16] = {"abcdefghijklmnop"};

static void dance(char *perm) {
	char old[16];
	int c, i, j;
	rewind(stdin);
	do {
		c = getchar();
		memcpy(old, perm, sizeof(old));
		if (c == 's') {
			scanf("%d", &i);
			memcpy(perm, old + sizeof(old) - i, i);
			memcpy(perm + i, old, sizeof(old) - i);
		} else {
			if (c == 'x') {
				scanf("%d/%d", &i, &j);
			} else {
				assert(c=='p');
				int A = getchar();
				for (i = 0; perm[i] != A; i++);
				getchar();
				int B = getchar();
				for (j = 0; perm[j] != B; j++);
			}
			perm[i] = old[j];
			perm[j] = old[i];
		}
	} while (getchar() == ',');
}

int main() {
	for (int P = 1; P <= 30; P++) {
		memcpy(perms[P], perms[P - 1], 16);
		dance(perms[P]);
		/*for (int p = 0; p < P; p++) {
			if (memcmp(perms[p], perms[P], 16) == 0)
				printf("perms[%d] == perms[%d]\n", p, P), exit(0);
		}*/
	}
	for (int i = 0; i < 16; i++)
		putchar(perms[10][i]);
	putchar('\n');
}
