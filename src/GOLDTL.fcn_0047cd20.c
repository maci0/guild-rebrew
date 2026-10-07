#include "rgb.h"

typedef struct {
	char pad0[0x18];
	int* items;
} fcn_0047cd20_set;
// SIZE 0x1c

extern Rgb g_100f1b8;

int __cdecl fcn_0047bdd0(int, int, int, float, unsigned char, unsigned char, unsigned char);

// FUNCTION: GOLDTL 0x47cd20

int __cdecl fcn_0047cd20(int a1, int a2, int a3, fcn_0047cd20_set* s, int idx)
{
	if (s == 0)
		return 0;
	return fcn_0047bdd0(a1, a2, s->items[idx], 1.0f, g_100f1b8.r, g_100f1b8.g, g_100f1b8.b) != 0;
}
