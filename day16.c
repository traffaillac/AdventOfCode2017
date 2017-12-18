#include <assert.h>
#include <stdio.h>
#include <string.h>

static char str[48405];

int main() {
	static const char init[16] = "abcdefghijklmnop";
	char list[16], old[16];
	memcpy(list, init, 16);
	gets(str);
	do {
		for (int i = 0; str[i] != 0; i++) {
			//fputc(i, stderr);
			memcpy(old, list, 16);
			if (str[i] == 's') {
				scanf("%d", &i);
				memcpy(list, old + 16 - i, i);
				memcpy(list + i, old, 16 - i);
			} else if (i == 'x') {
				scanf("%d/%d", &i, &j);
				list[i] = old[j];
				list[j] = old[i];
			} else {
				assert(i=='p');
				scanf("%c/%c", &c, &d);
				for (i = 0; list[i] != c - 'a'; i++);
				for (j = 0; list[j] != d - 'a'; j++);
				list[i] = old[j];
				list[j] = old[i];
			}
		}
	} while ();
	v16qi shuf = perm;
	for (int i = 0; i < 1; i++)
		perm = __builtin_shuffle(perm, shuf);
	for (int i = 0; i < 16; i++)
		putchar('a' + perm[i]);
	putchar('\n');
}
