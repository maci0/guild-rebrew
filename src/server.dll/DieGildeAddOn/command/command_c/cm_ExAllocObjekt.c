
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 123B
 *    CFlags: 
 *    Symbol: _ExCreateObject
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExAllocObjekt(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   char *pcVar2;
 *   undefined4 *puVar3;
 *   
 *   *(undefined4 *)(param_1 + 0x35) = g_timestamp_0b6c;
 *   iVar1 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(param_1 + 0x10) = iVar1;
 *   pcVar2 = gm_AllocObjekt(iVar1,(uint)*(ushort *)(param_1 + 0x14),1);
 *   if (pcVar2 == (char *)0x0) {
 *     return 1;
 *   }
 *   *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x264200) =
 *        *(undefined4 *)(pcVar2 + 2);
 *   puVar3 = (undefined4 *)(param_1 + 0x16);
 *   pcVar2 = pcVar2 + 0x1c;
 *   for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
 *     *(undefined4 *)pcVar2 = *puVar3;
 *     puVar3 = puVar3 + 1;
 *     pcVar2 = pcVar2 + 4;
 *   }
 *   *(undefined2 *)pcVar2 = *(undefined2 *)puVar3;
 *   pcVar2[2] = *(char *)((int)puVar3 + 2);
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
 */

#include "../command_internal.h"

void* __cdecl memcpy(void*, const void*, unsigned int);
extern char g_player_slot_0[];
char* __cdecl gm_AllocObjekt(int, int, int);

/* Execution handler: allocates a new object in an entity's
 * inventory via gm_AllocObjekt. Takes entity ID from cmd+0x10
 * and object parameters from the command payload. */

// FUNCTION: SERVER 0x1000e750
int __cdecl cm_ExAllocObjekt(int param_1, char* param_2)
{
	int field_id;
	char* game_obj;
	char* entity;
	unsigned int slot_idx;

	*(int*) (param_1 + 0x35) = g_timestamp_0b6c;
	field_id = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (param_1 + 0x10) = field_id;
	game_obj = gm_AllocObjekt(field_id, (unsigned int) *(unsigned short*) (param_1 + 0x14), 1);
	if (game_obj == (char*) 0) {
		return 1;
	}
	slot_idx = (unsigned int) *(unsigned char*) (param_1 + 3);
	*(int*) (g_player_slot_0 + slot_idx * 0x264264 + 0x264208) = *(int*) (game_obj + 2);
	entity = game_obj + 0x1c;
	memcpy(entity, (char*) param_1 + 0x16, 0x1f);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
	}
	return 0;
}
