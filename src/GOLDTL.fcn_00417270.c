

#include <stdlib.h>

// SIZE 0x54
typedef struct {
	char pad0[0x4c];
	unsigned char r;
	unsigned char g;
	unsigned char b;
	char pad4f[2];
	unsigned char flags;
	char pad52[2];
} Particle;

// SIZE 0xdc
typedef struct {
	float a;
	float b;
	float c;
	char padc[0x28 - 0xc];
	Particle* parts;
	char pad2c[0xd8 - 0x2c];
	int count;
} System;

void __cdecl fcn_00417270(System* s, float a, float b, float c)
{
	int i;
	Particle* p;

	s->a = a;
	s->b = b;
	s->c = c;
	p = s->parts;
	for (i = 0; i < s->count; i++) {
		p->flags &= 0xfe;
		p->b = (rand() & 0x3f) - 0x42;
		p->g = (rand() & 0x3f) + 0x64;
		p->r = (rand() & 0x3f) + 0x32;
		p++;
	}
}
