#include <stdio.h>
#include <string.h>

static const unsigned char *knot_hash(const unsigned char *lengths, size_t num) {
	static unsigned char list[256], old[256], hash[16];
	for (int i = 0; i < sizeof(list); i++)
		list[i] = i;
	int pos = 0;
	int skip = 0;
	for (int round = 0; round < 64; round++) {
		for (int l = 0; l < num; l++) {
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

int main() {
	unsigned char str[] = "102,255,99,252,200,24,219,57,103,2,226,254,1,0,69,216\x11\x1F\x49\x2F\x17";
	const unsigned char *hash = knot_hash(str, sizeof(str) - 1);
	for (int i = 0; i < 16; i++)
		printf("%02x", hash[i]);
	putchar('\n');
}
