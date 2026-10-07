// FUNCTION: GOLD 0x0046bdf0

#include "gold_gui.h"

typedef struct
{
	char pad00[0x52];
	short f52;
} fcn_0046bdf0_Def;
// SIZE 0x54

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */
extern fcn_0046bdf0_Def* g_006ed918; /* 0x006ed918 */
extern short g_00fb9070; /* 0x00fb9070 */
extern short g_00fb9072; /* 0x00fb9072 */
extern short g_005fe73c; /* 0x005fe73c */

int __cdecl fcn_0046c9e0(void);
int __cdecl fcn_004690a0(int);
void __cdecl fcn_00473530(int, int);
void __cdecl fcn_00469900(int);

int __cdecl fcn_0046bdf0(int a1, int a2, int a3, int a4)
{
	int idx;

	idx = fcn_0046c9e0();
	g_00f8f080[idx].kind = 9;
	g_00f8f080[idx].f4c = 1;
	g_00f8f080[idx].flags = 3;
	g_00f8f080[idx].x = a1;
	g_00f8f080[idx].f16 = g_006ed918[a3].f52;
	g_00f8f080[idx].y = a2;
	g_00f8f080[idx].f08 = a3;
	g_00f8f080[idx].f22 = 0;
	g_00f8f080[idx].f24 = g_00fb9070;
	g_00f8f080[idx].f1e = 0;
	g_00f8f080[idx].f20 = g_00fb9072;
	g_00f8f080[idx].font = g_005fe73c;
	g_00f8f080[idx].data = (char*) fcn_004690a0(a3);
	fcn_00473530(idx, a4);
	fcn_00469900(a3);
	return idx;
}
