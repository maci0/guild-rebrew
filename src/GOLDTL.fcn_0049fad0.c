// FUNCTION: GOLD 0x4a0090
// FUNCTION: GOLDTL 0x49fad0

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct F8 {
	int mask;
	int b;
} F8;
// SIZE 0x8

typedef struct Ent {
	char pad0[0x16c];
	char* home;
	char pad170[0x21c - 0x170];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];
extern unsigned char g_773d75;

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004eb260(char* e);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050d320(char* e, char k);
int __cdecl fcn_004a5e60(char* p, int kind, F8 f, int c, float r, int* out);
int __cdecl fcn_005015e0(char**, char**, char**, int);

int __cdecl fcn_0049fad0(int a1, char* e, int a3, char* out)
{
	int v;
	int found;
	char* q;
	int n;
	int i;
	F8 f;

	if (a3 != 0) {
		return 0;
	}
	if (a1 != 0) {
		return 0;
	}
	if (fcn_004eb260(e) != 1) {
		return 0;
	}
	v = (int) max(gm_WalkEntityChain(*(unsigned short*) e) * 0.01f, 160.0f);
	if (v > (int) (fcn_0050d320(e, (*(char*)&g_773d75)) * 0.22f)) {
		return 0;
	}
	f.mask = 0x807d4190;
	f.b = 1;
	if (fcn_004a5e60(e, 6, f, 0, (float) (gm_RandomMod(0x20) + 0x20), &found) == 0) {
		return 0;
	}
	fcn_005015e0(&q, 0, 0, found);
	if (q == 0) {
		return 0;
	}
	n = 0;
	for (i = 0; i < 768; i++) {
		if (((Ent*)g_7f4ca0)[i].home == q) {
			n++;
		}
	}
	if (n == 0) {
		return 0;
	}
	*(int*) (out + 0x10) = v;
	out[0] = 4;
	*(int*) (out + 4) = found;
	return 0x37;
}
