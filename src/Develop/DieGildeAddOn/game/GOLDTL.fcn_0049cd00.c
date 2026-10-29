#include <string.h>

typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
/* SIZE 0x18 */

unsigned short __cdecl gm_RandomMod(int n);
unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
int __cdecl fcn_004aa920(short* a1, int a2, char* a3);
int __cdecl fcn_00495400(int kind, int id, int n, Blk24* b1, Blk24* b2);

/* ADDRESS: GOLDTL 0x0049cd00 */
int __cdecl fcn_0049cd00(int a1, char* ent, int a3, Blk24* o1, Blk24* o2)
{
	Blk24 b1;
	Blk24 b2;
	int r;

	(void) a1;
	if (a3 != 0) {
		return 0;
	}
	if (*(int*) (ent + 0x1e8) & 0x200) {
		if (gm_RandomMod(8) != 0) {
			return 0;
		}
	}
	if (*(char**) (ent + 0x170) == 0) {
		if (*(unsigned char*) (ent + 2) == 3) {
			if ((*(int*) (ent + 0x1e8) & 4) == 0) {
				return 0;
			}
			goto fill;
		}
		b1.kind = 5;
		b1.a = 4;
		b1.b = 1;
		b2.kind = 0;
		b2.a = 0;
		b2.b = 0;
		r = fcn_00495400(0x28, *(unsigned short*) ent, 1, &b1, &b2);
		if (r == 0) {
			return 0;
		}
		*o1 = b1;
		*o2 = b2;
		return r;
	} else {
		if (*(unsigned char*) (ent + 2) == 3) {
			if ((*(int*) (ent + 0x1e8) & 4) == 0) {
				return 0;
			}
			goto fill;
		}
		if (fcn_00502cd0(*(int*) (*(char**) (ent + 0x170) + 0x5d), 2, 6, 0, 0x15) != 0) {
			goto fill;
		}
		b1.kind = 2;
		b1.a = 0x15;
		b1.b = 1;
		b1.f = 0.44f;
		b2.kind = 4;
		b2.a = *(int*) (*(char**) (ent + 0x170) + 1);
		b2.b = 1;
		r = fcn_00495400(0x28, *(unsigned short*) ent, 1, &b1, &b2);
		if (r == 0) {
			return 0;
		}
		*o1 = b1;
		*o2 = b2;
		return r;
	}
fill:
	memset(&b1, 0, sizeof(b1));
	memset(&b2, 0, sizeof(b2));
	if (fcn_004aa920((short*) ent, (int) &b1, (char*) &b2) == 0) {
		return 0;
	}
	*o1 = b1;
	*o2 = b2;
	return 0x2a;
}
