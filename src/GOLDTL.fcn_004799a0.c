#include <string.h>

typedef struct Shape {
	unsigned int len;
	short pad4;
	unsigned short w;
	short pad8;
	unsigned short h;
	unsigned char type;
} Shape;
// SIZE 0xd

typedef struct Bank {
	char magic[8];
	char ver;
	char pad9;
	char name[0x2a - 0xa];
	unsigned short count;
	unsigned short maxw;
	unsigned short maxh;
	unsigned int size;
	unsigned char type;
} Bank;
// SIZE 0x35

// FUNCTION: GOLDTL 0x4799a0
void __cdecl fcn_004799a0(Shape* s, Bank* b, int idx)
{
	unsigned int* p;

	p = (unsigned int*) ((char*) b + 0x45 + idx * 4);
	memmove((char*) b + 0x49 + idx * 4, p, (b->count - idx) * 4);
	*p = b->size;
	memcpy((char*) b + b->size, s, s->len);
	b->size += s->len;
	b->count++;
	if (s->w > b->maxw) {
		b->maxw = s->w;
	}
	if (s->h > b->maxh) {
		b->maxh = s->h;
	}
}
