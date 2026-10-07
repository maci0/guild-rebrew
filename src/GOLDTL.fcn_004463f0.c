extern int g_67a960;

// SIZE 0x4
typedef struct {
	unsigned char c0;
	unsigned char c1;
	unsigned char c2;
	unsigned char c3;
} Col;

// SIZE 0xc
typedef struct {
	unsigned char c0;
	unsigned char c1;
	unsigned char c2;
	unsigned char c3;
	float f4;
	float f8;
} Pal;

#include "client_types.h"
extern Pal_1041d20 g_1041d20[6];
extern float g_67a964;

void __cdecl fcn_00438920(float, float, Col);

// FUNCTION: GOLD 0x44a170
// FUNCTION: GOLDTL 0x004463f0

char __cdecl fcn_004463f0(unsigned int a, unsigned int b, float t)
{
	Col col;

	if (a >= 6 || b >= 6 || !(t >= 0.0f) || !(t <= 1.0f)) {
		return 0;
	}
	col.c2 = (unsigned char) (int) ((((Pal*)g_1041d20)[b].c2 - ((Pal*)g_1041d20)[a].c2) * t + ((Pal*)g_1041d20)[a].c2);
	col.c1 = (unsigned char) (int) ((((Pal*)g_1041d20)[b].c1 - ((Pal*)g_1041d20)[a].c1) * t + ((Pal*)g_1041d20)[a].c1);
	col.c0 = (unsigned char) (int) ((((Pal*)g_1041d20)[b].c0 - ((Pal*)g_1041d20)[a].c0) * t + ((Pal*)g_1041d20)[a].c0);
	fcn_00438920(((((Pal*)g_1041d20)[b].f4 - ((Pal*)g_1041d20)[a].f4) * t + ((Pal*)g_1041d20)[a].f4) * g_67a964,
	    ((((Pal*)g_1041d20)[b].f8 - ((Pal*)g_1041d20)[a].f8) * t + ((Pal*)g_1041d20)[a].f8) * g_67a964, col);
	g_67a960 = a;
	return 1;
}
