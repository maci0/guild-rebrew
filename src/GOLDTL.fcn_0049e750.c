// FUNCTION: GOLD 0x0049ed10
// FUNCTION: GOLDTL 0x49e750

#include <string.h>

typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int v[5];
} Blk24;
// SIZE 0x18

int __cdecl gm_CheckStatLevel(int, int);
int __cdecl fcn_00507d10(int job);
int __cdecl fcn_004ab010(unsigned short* e, Blk24* o1, Blk24* o2);
int __cdecl fcn_004ab1a0(unsigned short* e, Blk24* o1, Blk24* o2);

int __cdecl fcn_0049e750(int a1, unsigned short* e, int a3, Blk24* o1, Blk24* o2)
{
	Blk24 b1;
	Blk24 b2;
	int r;

	r = gm_CheckStatLevel(*e, 4);
	if ((a1 == 0x32 || a1 == 0x25 || a1 == 0) && a3 == 0) {
		memset(&b1, 0, sizeof(b1));
		memset(&b2, 0, sizeof(b2));
		if (r != 0 && fcn_00507d10(r) > 2) {
			if (o1->kind == 4 && o2->kind == 1) {
				return 0x32;
			}
			if (fcn_004ab010(e, &b1, &b2) != 0) {
				*o1 = b1;
				*o2 = b2;
				return 0x32;
			}
		}
		if (fcn_004ab1a0(e, &b1, &b2) != 0) {
			*o1 = b1;
			*o2 = b2;
			return 0x32;
		}
	}
	return 0;
}
