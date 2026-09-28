#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#endif

#include "../command_internal.h"
#include "../player_slot.h"
#include "../../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"

// SIZE 0x30
typedef struct copy_12_dwords {
	uint data[12];
} copy_12_dwords;

char* __cdecl gm_AllocGebaeude(uchar, uint);

// GLOBAL: SERVER 0x1002caf0
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_B[];

/* Execution handler: allocates a new room/space (Raum) entity.
 * Resolves entity by ID, calls gm_AllocBuildingDefaults to set
 * up building defaults, and returns via result. */

// GLOBAL: SERVER 0x1002cb34
extern char s_gm_AllocGebaeude___failed[];
// FUNCTION: GOLDTL 0x43bf60
// SIZE: 268
// FUNCTION: SERVER 0x1000d350

int __cdecl cm_ExAllocRaum(int cmd, char* result)
{
	char* building;
	int field_id;
	int i;

	*(int*) (cmd + 0x10) = g_next_object_id;
	if (*(int*) (cmd + 0x16) == -1) {
		i = 0xffff;
	}
	else {
		field_id = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x16));
		*(int*) (cmd + 0x16) = field_id;
		i = 0;
		while ((ushort) i < 0x300) {
			if (*(ushort*) (g_slot_table + (uint)(ushort) i * 0x21c) != (ushort) 0xffff &&
				*(int*) (g_slot_table + (uint)(ushort) i * 0x21c + 4) == field_id) {
				break;
			}
			i = i + 1;
		}
		if ((ushort) i >= 0x300) {
			LogMessageInternal(
				"D:\\Develop\\DieGildeAddOn\\command\\command.c",
				0x280b,
				"Invalid 'eigentuemer_id' for cmdt_ALLOC_OBJEKT in cm_ExecCommand()",
				1
			);
			return 1;
		}
	}
	building = gm_AllocGebaeude(*(uchar*) (cmd + 0x14), i);
	if (building == (char*) 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x2817,
			"gm_AllocGebaeude() failed",
			1
		);
		return 1;
	}
	((player_slot*) g_connections)[(uint) *(uchar*) (cmd + 3)].data = *(int*) (building + 1);
	*(ushort*) (building + 0x5a) = *(ushort*) (cmd + 0x1a);
	if (*(int*) (cmd + 0x1c) != 0) {
		*(copy_12_dwords*) (building + 0x65) = *(copy_12_dwords*) (cmd + 0x20);
	}
	if (result != (char*) 0) {
		*result = '\x01';
		result[1] = '\x02';
		*(char**) (result + 6) = building;
	}
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
