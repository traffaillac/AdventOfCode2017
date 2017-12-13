#include <stdio.h>

static int ranges[100];

int main() {
	int depth, range;
	while (scanf("%d: %d", &depth, &range) == 2)
		ranges[depth] = range;
	int delay = 0, severity;
	do {
		delay++;
		severity = 0;
		for (int pos = 0; pos < 100; pos++) {
			if (ranges[pos] == 0)
				continue;
			int scanner = (pos + delay) % ((ranges[pos] - 1) * 2);
			if (scanner == 0)
				severity += pos * ranges[pos];
		}
	} while (severity > 0 || delay % 4 == 0);
	printf("%d\n", delay);
}
