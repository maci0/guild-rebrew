
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

#ifdef __clang__
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 267B
 *    CFlags: 
 *    Symbol: _CmdAllocPlayer
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExAllocSpieler(int cmd,char *result)
 * 
 * {
 *   int iVar1;
 *   ushort *puVar2;
 *   uint uVar3;
 *   
 *   *(undefined4 *)(cmd + 0x10) = g_timestamp_0b6c;
 *   iVar1 = rand();
 *   *(int *)(cmd + 0x26) = iVar1;
 *   srand(iVar1);
 *   if (*(int *)(cmd + 0x1f) == -1) {
 *     puVar2 = (ushort *)0x0;
 *   }
 *   else {
 *     iVar1 = gm_GetFieldByType((char *)cmd,*(int *)(cmd + 0x1f));
 *     *(int *)(cmd + 0x1f) = iVar1;
 *     puVar2 = gm_StartFilteredEntitySearch(1,1,iVar1);
 *     if (puVar2 == (ushort *)0x0) {
 *       LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2889,
 *                          s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50,1);
 *       return 1;
 *     }
 *   }
 *   uVar3 = gm_CreateEntityFromParents
 *                     ((uint)*(byte *)(cmd + 0x14),*(int *)(cmd + 0x15),
 *                      *(int *)(cmd + 0x19),(uint)*(ushort *)(cmd + 0x1d),(int)puVar2);
 *   uVar3 = uVar3 & 0xffff;
 *   if (uVar3 == 0xffff) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2897,
 *                        s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c,1);
 *     return 1;
 *   }
 *   *(undefined4 *)(g_player_slot_0[*(byte *)(cmd + 3)].data + 0x2641f8) =
 *        (&g_static_entity0_entity_id)[uVar3 * 0x87];
 *   if (result != (char *)0x0) {
 *     *result = '\x01';
 *     result[1] = '\x01';
 *     *(undefined2 **)(result + 6) = &g_static_entity_table_358a0 + uVar3 * 0x10e;
 *   }
 *   return 0;
 * }
 */

extern char g_player_slot_0[];
uint __cdecl gm_CreateEntityFromParents(uint, int, int, ushort, int, uint, uint, uint);

extern char s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50[];
extern char s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c[];
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: allocates a new player entity (Spieler).
 * Initializes player structure with defaults, links entity
 * records, and assigns the initial player state. */

// FUNCTION: SERVER 0x1000d460
int __cdecl cm_ExAllocSpieler(int cmd, char* result)
{
	int seed;
	uint entity_index;
	int field_id;
	char* entity_ptr;

	*(int*) (cmd + 0x10) = g_timestamp_0b6c;
	seed = rand();
	*(int*) (cmd + 0x26) = seed;
	srand(seed);
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
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x2889,
				s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50,
				1
			);
			return 1;
		}
	}
	entity_index = gm_CreateEntityFromParents(
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
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2897,
			s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c,
			1
		);
		return 1;
	}
	*(int*) (g_player_slot_0 + (uint) *(uchar*) (cmd + 3) * 0x264264 + 0x2641f8) =
		*(int*) (g_static_entity_table_358a0 + entity_index * 0x21c + 4);
	if (result != (char*) 0) {
		entity_ptr = g_static_entity_table_358a0 + entity_index * 0x21c;
		*result = '\x01';
		result[1] = '\x01';
		*(char**) (result + 6) = entity_ptr;
	}
	return 0;
}
