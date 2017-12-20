#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct { int pX, pY, pZ, vX, vY, vZ, aX, aY, aZ; } Particle;
static Particle particles[999];

int main() {
	Particle *P = particles;
	while (scanf(" p=<%d,%d,%d>, v=<%d,%d,%d>, a=<%d,%d,%d>", &P->pX, &P->pY, &P->pZ, &P->vX, &P->vY, &P->vZ, &P->aX, &P->aY, &P->aZ) == 9)
		P++;
	for (int tick = 0; tick < 1000; tick++) {
		for (Particle *p = particles; p < P; p++) {
			p->pX += p->vX += p->aX;
			p->pY += p->vY += p->aY;
			p->pZ += p->vZ += p->aZ;
		}
		for (Particle *p = particles; p < P; p++) {
			int collide = 0;
			for (Particle *q = p + 1; q < P; q++) {
				if (q->pX == p->pX && q->pY == p->pY && q->pZ == p->pZ)
					*q = *P, P--, collide = 1;
			}
			if (collide)
				*p = *P, P--;
		}
	}
	printf("%ld\n", P - particles);
}
