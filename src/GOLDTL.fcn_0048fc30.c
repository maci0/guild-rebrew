#include "Develop/DieGildeAddOn/game/spiel.h"


typedef struct Blk24 {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
// SIZE 0x18

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);

int __cdecl fcn_0048f4f0(char* e, char* q, Blk24* b1, Blk24* b2);
int __cdecl fcn_0048f710(char* e, char* q, Blk24* b1, Blk24* b2);
int __cdecl fcn_0048f8f0(char* e, char* q, Blk24* b1, Blk24* b2);
int __cdecl fcn_0048fb10(char* e, char* q, Blk24* b1, Blk24* b2);

int __cdecl fcn_0048fc30(int a1, char* e, int a3, Blk24* o1, Blk24* o2)
{
	char* q;
	int res[4];
	int found;
	Blk24 b1[4];
	Blk24 b2[4];
	int k;
	int n;
	F8 f;

	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	res[3] = 0;
	f.mask = 0x20000000;
	f.b = 0;
	if (a3 != 0) {
		return 0;
	}
	if (a1 != 0x3d && a1 != 0) {
		return 0;
	}
	if (e[2] == 3) {
		return 0;
	}
	if (gm_CheckStatLevel(*(unsigned short*) e, 0xd) == 0) {
		return 0;
	}
	if (fcn_004a5e60(e, 4, f, 0, 100.0f, &found) == 0) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&q), 0, 0, found);
	if (q == 0) {
		return 0;
	}
	res[0] = fcn_0048f4f0(e, q, &b1[0], &b2[0]);
	res[1] = fcn_0048f710(e, q, &b1[1], &b2[1]);
	res[2] = fcn_0048f8f0(e, q, &b1[2], &b2[2]);
	res[3] = fcn_0048fb10(e, q, &b1[3], &b2[3]);
	k = gm_RandomMod(4);
	for (n = 4; n != 0;) {
		if (res[k] != 0) {
			*o1 = b1[k];
			*o2 = b2[k];
			return 0x3d;
		}
		n--;
		k = (k + 1) % 4;
	}
	return 0;
}
