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

// FUNCTION: GOLDTL 0x479a20
int __cdecl fcn_00479a20(Bank* b, int idx)
{
	unsigned int* po;
	unsigned int* q;
	char* sh;
	unsigned int len;
	int i;

	if (!b) {
		return 0;
	}
	if (b->count < idx) {
		return 0;
	}
	po = (unsigned int*) ((char*) b + 0x45 + idx * 4);
	sh = (char*) b + *po;
	len = *(unsigned int*) sh;
	if (idx != b->count) {
		memmove(sh, sh + len, b->size - (sh - (char*) b));
	} else {
		memset(sh, 0, len);
	}
	for (i = 0; i < b->count; i++) {
		q = (unsigned int*) ((char*) b + 0x45 + i * 4);
		if (*q > *po) {
			*q -= len;
		}
	}
	memmove(po, (char*) b + 0x49 + idx * 4, (b->count - idx) * 4);
	*(unsigned int*) ((char*) b + 0x45 + b->count * 4) = 0;
	b->count--;
	b->size -= len;
	return 1;
}
