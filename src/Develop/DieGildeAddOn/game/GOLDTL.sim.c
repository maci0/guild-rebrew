#include "../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gm_RandomMod(unsigned short range);
unsigned int __cdecl gm_AllocSpieler(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
void __cdecl plt_TableLookup(unsigned int a, unsigned short* b);
unsigned short __cdecl sim_FindAndMatchParents(unsigned int param);
extern unsigned char g_entity_type_bytes[1];

// FUNCTION: GOLD 0x00424370
// FUNCTION: GOLDTL 0x420700
void __cdecl fcn_0042b040(int, void*);

void __cdecl fcn_00420700(char* entity, char* data)
{
	if (entity == 0) {
		return;
	}
	if (entity[0x104] == 0) {
		return;
	}
	if (data == 0) {
		return;
	}
	fcn_0042b040(*(int*) (entity + 0x100), entity + 0x10c);
	*(int*) (entity + 0x110) = *(int*) (entity + 0x10c);
	*(int*) (entity + 0x120) = *(int*) (entity + 0x11c);
	*(char**) (entity + 0x114) = data;
}

