#include "../command_internal.h"
#include "../../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"

#ifdef __clang__
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

uint __cdecl gm_AllocSpieler(uint, int, int, ushort, int, uint, uint, uint);

// GLOBAL: SERVER 0x1002cb50
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_S[];

// GLOBAL: SERVER 0x1002cb8c
extern char s_cm_ExAllocSpieler___gm_AllocSpie[];
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: allocates a new player entity (Spieler).
 * Initializes player structure with defaults, links entity
 * records, and assigns the initial player state. */
// FUNCTION: GOLDTL 0x404ca0
// SIZE: 283
// FUNCTION: SERVER 0x1000d460

int __cdecl cm_ExAllocSpieler(int cmd, char* result)
{
	int seed;
	uint entity_index;
	int field_id;
	char* entity_ptr;

	*(int*) (cmd + 0x10) = g_next_object_id;
	seed = rand();
	*(int*) (cmd + 0x26) = seed;
	srv_SeedRandom(seed);
	seed = *(int*) (cmd + 0x1f);
	if (seed == -1) {
		seed = 0;
	}
	else {
		field_id = gm_GetFieldByType((char*) cmd, seed);
		*(int*) (cmd + 0x1f) = field_id;
		seed = (int) gm_StartFilteredEntitySearch(1, 1, field_id);
		if (seed == 0) {
			LogMessageInternal(
				"D:\\Develop\\DieGildeAddOn\\command\\command.c",
				0x2889,
				"Invalid 'GI_Id' for cmdt_ALLOC_SPIELER in cm_ExecCommand()",
				1
			);
			return 1;
		}
	}
	entity_index = gm_AllocSpieler(
		*(uchar*) (cmd + 0x14),
		*(int*) (cmd + 0x15),
		*(int*) (cmd + 0x19),
		*(ushort*) (cmd + 0x1d),
		seed,
		*(uchar*) (cmd + 0x23),
		*(uchar*) (cmd + 0x24),
		*(uchar*) (cmd + 0x25)
	);
	entity_index = entity_index & 0xffff;
	if (entity_index == 0xffff) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x2897,
			"cm_ExAllocSpieler():gm_AllocSpieler() failed",
			1
		);
		return 1;
	}
	*(int*) (g_connections + (uint) *(uchar*) (cmd + 3) * 0x264264 + 0x264200) =
		*(int*) (g_slot_table + entity_index * 0x21c + 4);
	if (result != (char*) 0) {
		entity_ptr = g_slot_table + entity_index * 0x21c;
		*result = '\x01';
		result[1] = '\x01';
		*(char**) (result + 6) = entity_ptr;
	}
	return 0;
}
