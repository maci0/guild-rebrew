// FUNCTION: GOLD 0x004f4350
// FUNCTION: GOLDTL 0x4f6740

#include "client_types.h"
#pragma pack(push, 1)
typedef Rec2d_9a3800 Rec2d;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

extern int g_773d38;
extern Rec2d_9a3800 g_9a3800[512];
extern Pair_99f800 g_99f800[0x800];

void __cdecl fcn_004f6740(void)
{
	int i;

	g_773d38 = 0;
	for (i = 0; i < 512; i++) {
		g_9a3800[i].x16 = -1;
		g_9a3800[i].x12 = -1;
		g_9a3800[i].id = -1;
		g_9a3800[i].x25 = 0;
	}
	for (i = 0; i < 0x800; i++) {
		((Pair*)g_99f800)[i].a = -1;
		((Pair*)g_99f800)[i].b = -1;
	}
}
