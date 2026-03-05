/* Ghidra decompilation reference:
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char g_player_slot_0[];

ushort __cdecl gm_CreateEntityFromParents(uint, int, int, ushort, int, uint, uint, uint);
char* __cdecl strncpy(char*, const char*, unsigned int);

extern char s_ClientSpieler_erzeugt_1002cbbc[];
extern char s_gm_AllocSpieler___failed_1002cbd4[];

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 361
// BLOCKER: Register allocation/instruction scheduling difference in gm_CreateEntityFromParents argument setup; target evaluates param_2 boolean first (neg/sbb in eax) then pushes args in different register order. Same-size, semantically equivalent.
/* Execution handler: allocates a client-side player entity.
 * Similar to cm_ExAllocSpieler but for client-connected players,
 * updating player slot flags and setting connection state. */

// FUNCTION: SERVER 0x1000d570
int __cdecl cm_ExAllocClientSpieler(int param_1, char* param_2)
{
	ushort entity_id;
	uint entity_id_uint;
	int entity_offset;
	int record;
	short* table_entry;
	char* entity_base;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	entity_offset = rand();
	*(int*) (param_1 + 0x45) = entity_offset;
	srand(*(int*) (param_1 + 0x22));
	entity_id = (ushort) gm_CreateEntityFromParents(
		param_2 ? 6 : 7,
		*(int*) (param_1 + 0x14),
		*(int*) (param_1 + 0x18),
		*(ushort*) (param_1 + 0x1c),
		0,
		(uint)*(uchar*) (param_1 + 0x1e),
		0,
		(uint)*(uchar*) (param_1 + 0x23)
	);
	entity_id_uint = entity_id;
	if (entity_id_uint == 0xffff) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x290f, s_gm_AllocSpieler___failed_1002cbd4, 1);
		return 1;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x2917, s_ClientSpieler_erzeugt_1002cbbc, 1);
	entity_offset = entity_id_uint * 0x21c;
	*(int*) (g_player_slot_0 + (uint)*(uchar*) (param_1 + 3) * 0x264264 + 0x2641f8) =
		*(int*) (entity_offset + 0x100358a4);
	strncpy((char*) (entity_offset + 0x100358d0), (char*) param_1 + 0x25, 0x10);
	entity_base = (char*) (entity_offset + 0x100358a0);
	table_entry = gm_GetEntityTableEntry(entity_base);
	if (table_entry != (short*) 0) {
		*table_entry = *(short*) (entity_offset + 0x100358f0);
		strncpy((char*) table_entry + 2, (char*) param_1 + 0x35, 0x10);
		strncpy((char*) (entity_offset + 0x100358e0), (char*) param_1 + 0x35, 0x10);
		record = gm_LookupEntityRecordById(*(int*) (entity_offset + 0x10035900));
		if (record != 0) {
			strncpy((char*) (record + 0x40), (char*) param_1 + 0x35, 0x10);
		}
	}
	*(int*) (entity_offset + 0x100358f4) = *(int*) (param_1 + 0x1f);
	*(char*) (entity_offset + 0x100358ac) = *(char*) (param_1 + 0x24);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x01';
		*(char**) (param_2 + 6) = entity_base;
	}
	return 0;
}
