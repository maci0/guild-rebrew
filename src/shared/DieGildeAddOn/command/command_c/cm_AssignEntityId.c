
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 37B
 *    CFlags:
 *    Symbol: _AssignEntityId
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_AssignEntityId(int param_1,char *param_2)
 *
 * {
 *   DWORD DVar1;
 *
 *   *(int *)(param_1 + 0x10) = g_entity_id_counter;
 *   DVar1 = timeGetTime();
 *   *(DWORD *)(param_1 + 0x14) = DVar1;
 *   g_entity_id_counter = g_entity_id_counter + 1;
 *   return 0;
 * }
 */

typedef unsigned long DWORD;

// GLOBAL: SERVER 0x10030b70
int g_entity_id_counter = 1;
__declspec(dllimport) unsigned long __stdcall timeGetTime(void);

/* Assigns the next sequential entity ID to the command packet at
 * offset 0x10, records a timestamp at 0x14, then increments the
 * global ID counter. Used when creating new game entities. */

// FUNCTION: SERVER 0x1000f0a0
int __cdecl cm_AssignEntityId(int cmd, char* result)
{
	DWORD timestamp;

	(void) result;

	*(int*) (cmd + 0x10) = g_entity_id_counter;
	timestamp = timeGetTime();
	*(DWORD*) (cmd + 0x14) = timestamp;
	g_entity_id_counter = g_entity_id_counter + 1;
	return 0;
}
