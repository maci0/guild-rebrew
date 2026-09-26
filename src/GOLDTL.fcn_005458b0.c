extern int g_77e8a0;
extern int g_772514;
extern int g_1040490;
extern int g_1040494;

// SIZE 0xc

#include "client_types.h"
extern s_77e8c0 g_77e8c0[16];

// SIZE 0x3cc

#include "client_types.h"
extern s_1015f4c g_1015f4c[];

// FUNCTION: GOLDTL 0x5458b0
// SIZE: 115

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_00471af0(int, int);

void __cdecl fcn_005458b0(void)
{
	int i;

	g_77e8a0 = fcn_00470820(0, 0, "Panel\\Event_Leiste");
	fcn_004727a0(g_77e8a0, 0);
	fcn_00469c40(g_1040494 - 0x7d, g_1040490 - 0x21, g_1015f4c[g_772514].f270);
	for (i = 0; i < 16; i++) {
		g_77e8c0[i].h = -1;
	}
	fcn_00471af0(g_77e8a0, 0);
}
