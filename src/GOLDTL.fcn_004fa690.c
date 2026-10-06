// FUNCTION: GOLD 0x004f82a0
// FUNCTION: GOLDTL 0x4fa690

#include <string.h>

#pragma intrinsic(memcpy, memset)

#include "client_types.h"
extern Rec24_99f5a0 g_99f5a0;
extern char g_99f6a0[];
extern char g_99f620[];
extern Cell_99ef80 g_99ef80[9][8];
extern Sample_99ec20 g_99ec20[16];
extern char g_99f5e0[];
extern float g_773d4c;

void __cdecl fcn_004fa690(void)
{
	memset(&g_99f5a0, 0, 36);
	memset(g_99f6a0, 0, 340);
	memset(g_99f620, 0, 104);
	memset(((char*)g_99ef80), 0, 1536);
	memset(((char*)g_99ec20), 0, 320);
	memset(g_99f5e0, 0, 40);
	g_99f5a0.head = -1;
	(*(int*)&g_773d4c) = 0;
}
