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

typedef struct Tex {
	char pad0[0x10];
	int pw;
} Tex;
// SIZE 0x14

extern char s_67da68[];
extern int g_100ef80;
extern int g_67d96c;

void __cdecl fcn_00478d50(int x, int y, Tex* t, char* sh);

// FUNCTION: GOLDTL 0x479b70
// SIZE: 186
int __cdecl fcn_00479b70(int x, int y, Tex* t, Bank* b, int idx)
{
	char msg[0x80];
	char* sh;
	int saved;

	if (!b) {
		return 0;
	}
	if (idx > b->count) {
		sprintf(msg, s_67da68, b->name);
		return 0;
	}
	sh = (char*) b + *(unsigned int*) ((char*) b + 0x45 + idx * 4);
	if (g_100ef80 == 0) {
		saved = g_67d96c;
		g_67d96c = t->pw;
		switch (((Shape*) sh)->type) {
		case 0:
			return 0;
		case 1:
			fcn_00478d50(x, y, t, sh);
			break;
		case 2:
			break;
		default:
			g_67d96c = saved;
			break;
		}
	}
	return 1;
}
