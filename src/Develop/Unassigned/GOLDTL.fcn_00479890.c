


#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl d2_SetShapeBankPalette(char* bank, char* palette)
{
	if (bank == 0) {
		return 0;
	}
	memcpy(bank + 0x445, palette, 0x400);
	return 1;
}

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
	char pad9[0x2a - 9];
	unsigned short count;
	unsigned short maxw;
	unsigned short maxh;
	unsigned int size;
	unsigned char type;
} Bank;
// SIZE 0x35

extern char s_67d8bc[];
extern char g_100eb80[];


/* fcn_00479890 must stay in this file: msvc6's same-TU callee analysis sees
 * that it leaves edx alone, so `b` stays in edx across the call. */
/* ADDRESS: GOLDTL 0x004798c0 */
int __cdecl d2_AppendShapeToBank(Shape* shape, Bank* bank)
{
	char magic[9];

	memcpy(magic, s_67d8bc, 9);
	if (bank->count >= 0xff) {
		return 0;
	}
	if (bank->size == 0 || bank->count == 0) {
		bank->size = 0x845;
		memcpy(bank->magic, magic, 8);
		bank->ver = 1;
		bank->type = shape->type;
		if (!bank->type) {
			d2_SetShapeBankPalette((char*) bank, g_100eb80);
		}
	}
	if (bank->type != shape->type) {
		return 0;
	}
	memcpy((char*) bank + bank->size, shape, shape->len);
	*(unsigned int*) ((char*) bank + 0x45 + bank->count * 4) = bank->size;
	bank->size += shape->len;
	if (shape->w > bank->maxw) {
		bank->maxw = shape->w;
	}
	if (shape->h > bank->maxh) {
		bank->maxh = shape->h;
	}
	bank->count++;
	return 1;
}
