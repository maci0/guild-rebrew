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

void __cdecl d3_SetFog(float, float, Col);


/* ADDRESS: GOLDTL 0x004463f0 */
char __cdecl d3_InterpolateSceneFog(unsigned int slotA, unsigned int slotB, float t)
{
	Col col;

	if (slotA >= 6 || slotB >= 6 || !(t >= 0.0f) || !(t <= 1.0f)) {
		return 0;
	}
	col.c2 = (unsigned char) (int) ((((Pal*)g_1041d20)[slotB].c2 - ((Pal*)g_1041d20)[slotA].c2) * t + ((Pal*)g_1041d20)[slotA].c2);
	col.c1 = (unsigned char) (int) ((((Pal*)g_1041d20)[slotB].c1 - ((Pal*)g_1041d20)[slotA].c1) * t + ((Pal*)g_1041d20)[slotA].c1);
	col.c0 = (unsigned char) (int) ((((Pal*)g_1041d20)[slotB].c0 - ((Pal*)g_1041d20)[slotA].c0) * t + ((Pal*)g_1041d20)[slotA].c0);
	d3_SetFog(((((Pal*)g_1041d20)[slotB].f4 - ((Pal*)g_1041d20)[slotA].f4) * t + ((Pal*)g_1041d20)[slotA].f4) * g_67a964,
	    ((((Pal*)g_1041d20)[slotB].f8 - ((Pal*)g_1041d20)[slotA].f8) * t + ((Pal*)g_1041d20)[slotA].f8) * g_67a964, col);
	g_67a960 = slotA;
	return 1;
}
