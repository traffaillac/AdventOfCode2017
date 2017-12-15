#include <stdio.h>
#include <string.h>

static const unsigned char *knot_hash(const unsigned char *lengths) {
	static unsigned char list[256], old[256], hash[16];
	for (int i = 0; i < sizeof(list); i++)
		list[i] = i;
	int pos = 0;
	int skip = 0;
	for (int round = 0; round < 64; round++) {
		for (int l = 0; lengths[l] != 0; l++) {
			memcpy(old, list, sizeof(list));
			for (int i = 0; i < lengths[l]; i++)
				list[(pos + i) % sizeof(list)] = old[(pos + lengths[l] - 1 - i) % sizeof(list)];
			pos = (pos + lengths[l] + skip++) % sizeof(list);
		}
	}
	for (int i = 0; i < 16; i++) {
		int xor = 0;
		for (int j = 0; j < 16; j++)
			xor ^= list[i * 16 + j];
		hash[i] = xor;
	}
	return hash;
}

static char disk[128][128];
static int erase(int i, int j, int group) {
	if (i < 0 || j < 0 || i >= 128 || j >= 128 || disk[i][j] == 0)
		return 0;
	disk[i][j] = 0;
	erase(i, j - 1, group);
	erase(i - 1, j, group);
	erase(i, j + 1, group);
	erase(i + 1, j, group);
	return 1;
}

int main() {
	char str[32];
	for (int i = 0; i < 128; i++) {
		sprintf(str, "ffayrhll-%d\x11\x1F\x49\x2F\x17", i);
		const unsigned char *hash = knot_hash((unsigned char *)str);
		for (int j = 0; j < 16; j++) {
			for (int k = 0; k < 8; k++)
				disk[i][j * 8 + k] = hash[j] >> (7 - k) & 1;
		}
	}
	int sum = 0;
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++)
			sum += erase(i, j, sum + 1);
	}
	printf("%d\n", sum);
}
