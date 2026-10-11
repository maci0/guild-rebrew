#include "../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gm_RandomMod(unsigned short range);
unsigned int __cdecl gm_AllocSpieler(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
void __cdecl plt_TableLookup(unsigned int a, unsigned short* b);
unsigned short __cdecl sim_FindAndMatchParents(unsigned int param);
extern unsigned char g_entity_type_bytes[1];

// FUNCTION: GOLD 0x0047cec0
// fcn_0047cec0 — store 3 globals (masked).

void __cdecl fcn_0047cec0(int u1, int u2, int u3, int c, int d, char e)
{
	(void) u1; (void) u2; (void) u3;
	*(int*) 0xf8a63c = d & 0xffff;
	*(int*) 0xf8a634 = c & 0xffff;
	*(char*) 0xf8a648 = e;
}

// FUNCTION: GOLDTL 0x500c50
// sim_SetSyncParams

void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10)
{
	*(unsigned int*) (target + 10) = field_10 & 0xff;
	*(unsigned short*) (target + 4) = (unsigned short) type_id;
	*(unsigned int*) (target + 6) = field_6 & 0xff;
}
