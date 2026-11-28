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

/* ADDRESS: GOLDTL 0x00479d70 */
int __cdecl shp_ShowShapeFromBankMode2(int x, int y, int surface, Bank* bank, int idx)
{
	char msg[0x80];
	char* sh;
	char saved_mode;

	if (!bank) {
		return 0;
	}
	if (idx > bank->count) {
		sprintf(msg, s_67da68, bank->name);
		return 0;
	}
	sh = (char*) bank + *(unsigned int*) ((char*) bank + 0x45 + idx * 4);
	saved_mode = sh[0xd];
	sh[0xd] = 2;
	d2_BlitShape(x, y, surface, (char*) bank + *(unsigned int*) ((char*) bank + 0x45 + idx * 4));
	sh[0xd] = saved_mode;
	return 1;
}
