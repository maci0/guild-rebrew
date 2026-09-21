#include "../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"
extern int __cdecl gm_RandomMod(unsigned short range);
unsigned int __cdecl gm_AllocSpieler(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
void __cdecl plt_TableLookup(unsigned int a, unsigned short* b);
unsigned short __cdecl sim_FindAndMatchParents(unsigned int param);
extern unsigned char g_entity_type_bytes[1];

// FUNCTION: GOLDTL 0x420700
// SIZE: 81
// sim_PriorityUpdate

void __cdecl sim_PriorityUpdate(char* ctx, char* entity)
{
	unsigned short tmp[4];
	char* old;

	plt_TableLookup((unsigned char) entity[0], tmp);
	if ((unsigned short) (unsigned char) entity[0x65] < tmp[0]) {
		old = *(char**) (ctx + 0x170);
		if (old != 0) {
			if ((unsigned char) old[0x65] > 0)
				old[0x65]--;
		}
		*(char**) (ctx + 0x170) = entity;
		entity[0x65]++;
	}
}

/* Starts an entity query filtered by type byte from arg1.
 * Dispatches entity iteration across buildings, citizens, or
 * other entity categories based on the type selector. */
