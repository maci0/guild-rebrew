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

void __cdecl d2_BlitShape(int a1, int a2, int a3, char* sh);

/* ADDRESS: GOLDTL 0x00479af0 */
int __cdecl fcn_00479af0(int a1, int a2, int a3, Bank* bank, int idx)
{
	char msg[0x80];

	if (!bank) {
		return 0;
	}
	if (idx > bank->count) {
		sprintf(msg, s_67da68, bank->name);
		return 0;
	}
	d2_BlitShape(a1, a2, a3, (char*) bank + *(unsigned int*) ((char*) bank + 0x45 + idx * 4));
	return 1;
}
