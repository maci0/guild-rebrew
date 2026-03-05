// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 37

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 37B
 *    CFlags: 
 *    Symbol: _AssignEntityId
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl AssignEntityId(int param_1,char *param_2)
 * 
 * {
 *   DWORD DVar1;
 *   
 *   *(int *)(param_1 + 0x10) = g_entity_id_start;
 *   DVar1 = timeGetTime();
 *   *(DWORD *)(param_1 + 0x14) = DVar1;
 *   g_entity_id_start = g_entity_id_start + 1;
 *   return 0;
 * }
 */

typedef unsigned long DWORD;

extern int g_entity_id_start;
extern __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// FUNCTION: SERVER 0x1000f0a0
int __cdecl AssignEntityId(int param_1, char* param_2)
{
	DWORD DVar1;

	*(int*) (param_1 + 0x10) = g_entity_id_start;
	DVar1 = timeGetTime();
	*(DWORD*) (param_1 + 0x14) = DVar1;
	g_entity_id_start = g_entity_id_start + 1;
	return 0;
}
