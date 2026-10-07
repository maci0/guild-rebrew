#include <stdio.h>

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

extern char s_67da68[];

void __cdecl fcn_00478fc0(int a1, int a2, int a3, char* sh);

// FUNCTION: GOLDTL 0x479af0
int __cdecl fcn_00479af0(int a1, int a2, int a3, Bank* b, int idx)
{
	char msg[0x80];

	if (!b) {
		return 0;
	}
	if (idx > b->count) {
		sprintf(msg, s_67da68, b->name);
		return 0;
	}
	fcn_00478fc0(a1, a2, a3, (char*) b + *(unsigned int*) ((char*) b + 0x45 + idx * 4));
	return 1;
}
