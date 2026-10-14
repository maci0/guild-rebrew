


#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_00479890(char* p, char* src)
{
	if (p == 0) {
		return 0;
	}
	memcpy(p + 0x445, src, 0x400);
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

/* ADDRESS: GOLDTL 0x004798c0 */
/* ADDRESS: GOLD 0x0047c600 */

/* fcn_00479890 must stay in this file: msvc6's same-TU callee analysis sees
 * that it leaves edx alone, so `b` stays in edx across the call. */
int __cdecl fcn_004798c0(Shape* s, Bank* b)
{
	char magic[9];

	memcpy(magic, s_67d8bc, 9);
	if (b->count >= 0xff) {
		return 0;
	}
	if (b->size == 0 || b->count == 0) {
		b->size = 0x845;
		memcpy(b->magic, magic, 8);
		b->ver = 1;
		b->type = s->type;
		if (!b->type) {
			fcn_00479890((char*) b, g_100eb80);
		}
	}
	if (b->type != s->type) {
		return 0;
	}
	memcpy((char*) b + b->size, s, s->len);
	*(unsigned int*) ((char*) b + 0x45 + b->count * 4) = b->size;
	b->size += s->len;
	if (s->w > b->maxw) {
		b->maxw = s->w;
	}
	if (s->h > b->maxh) {
		b->maxh = s->h;
	}
	b->count++;
	return 1;
}
