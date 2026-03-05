// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 52

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 52B
 *    CFlags: 
 *    Symbol: _CmdAllocGraveyardWorker
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExAllocGraveyardWorker(int param_1,char *param_2)
 * 
 * {
 *   int val;
 *   uint uVar1;
 *   
 *   *(undefined4 *)(param_1 + 0x14) = g_timestamp_0b6c;
 *   val = rand();
 *   *(int *)(param_1 + 0x10) = val;
 *   srand(val);
 *   uVar1 = gv_ExAllocGraveyardWorker(param_1 + 0x10);
 *   return (uVar1 != 0xffff) - 1;
 * }
 */

#include "../command_internal.h"

uint __cdecl gv_ExAllocGraveyardWorker(void*);

// FUNCTION: SERVER 0x10010310
int __cdecl cm_ExAllocGraveyardWorker(int param_1, char* param_2)
{
	int val;
	uint alloc_id;

	*(int*) (param_1 + 0x14) = g_timestamp_0b6c;
	val = rand();
	*(int*) (param_1 + 0x10) = val;
	srand(val);
	alloc_id = gv_ExAllocGraveyardWorker((void*) (param_1 + 0x10));
	alloc_id = alloc_id - 0xffff;
	return (alloc_id != 0) - 1;
}
