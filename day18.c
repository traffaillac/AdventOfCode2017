#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static struct { int inst, X, Y; short rX, rY; } prog[42];
static long regs[2][16];
static long queues[2][65536];
static int rpos[2];
static int wpos[2];
static int lock;

static int execute(int id, int p) {
	int inst = prog[p].inst;
	int rX = prog[p].rX;
	int rY = prog[p].rY;
	long X = rX < 0 ? prog[p].X : regs[id][rX];
	long Y = rY < 0 ? prog[p].Y : regs[id][rY];
	printf("p%d(%d): %s %ld %ld\n", id, p, (char *)&inst, X, Y);
	if (inst == *(int *)"snd") {
		queues[id ^ 1][wpos[id ^ 1]++] = X;
		assert(wpos[id^1]<65536);
	} else if (inst == *(int *)"set") {
		regs[id][rX] = Y;
	} else if (inst == *(int *)"add") {
		regs[id][rX] = X + Y;
	} else if (inst == *(int *)"mul") {
		regs[id][rX] = X * Y;
	} else if (inst == *(int *)"mod") {
		regs[id][rX] = X % Y;
	} else if (inst == *(int *)"rcv") {
		lock |= 1 << id;
		if (rpos[id] == wpos[id])
			return p;
		lock ^= 1 << id;
		regs[id][rX] = queues[id][rpos[id]++];
	} else if (inst == *(int *)"jgz") {
		if (X > 0)
			return p + Y;
	}
	return p + 1;
}

int main() {
	int N = 0;
	int i;
	while ((i = scanf(" %s %d", (char *)&prog[N].inst, &prog[N].X)) > 0) {
		prog[N].rX = (i == 1) ? getchar() - 'a' : -1;
		if (prog[N].inst != *(int *)"snd" && prog[N].inst != *(int *)"rcv")
			prog[N].rY = (scanf(" %d", &prog[N].Y) == 0) ? getchar() - 'a' : -1;
		N++;
	}
	regs[0]['p' - 'a'] = 0;
	regs[1]['p' - 'a'] = 1;
	int p0 = 0, p1 = 0;
	while ((unsigned)p0 < N && (unsigned)p1 < N && lock < 3) {
		p0 = execute(0, p0);
		p1 = execute(1, p1);
	}
	printf("%d\n", rpos[0]);
}
