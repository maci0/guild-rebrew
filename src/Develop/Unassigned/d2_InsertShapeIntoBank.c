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

/* ADDRESS: GOLDTL 0x004799a0 */
void __cdecl d2_InsertShapeIntoBank(Shape* shape, Bank* bank, int idx)
{
	unsigned int* p;

	p = (unsigned int*) ((char*) bank + 0x45 + idx * 4);
	memmove((char*) bank + 0x49 + idx * 4, p, (bank->count - idx) * 4);
	*p = bank->size;
	memcpy((char*) bank + bank->size, shape, shape->len);
	bank->size += shape->len;
	bank->count++;
	if (shape->w > bank->maxw) {
		bank->maxw = shape->w;
	}
	if (shape->h > bank->maxh) {
		bank->maxh = shape->h;
	}
}
